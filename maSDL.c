#include "SDL.h"
#include "maSDL.h"
#include "clashloyal.h"

void message(char *myTitle, char *myMessage){
        const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "ok" },
 //       { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
 //       { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        myTitle, /* .title */
        myMessage, /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        //return 1;
    }
    if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }

}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void clear_surface(SDL_Surface *psurf){
        Uint32 color = SDL_MapRGB(psurf->format,0,0,0);
        SDL_FillRect(psurf,NULL, color);
}

void prepare_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination ){
    apply_surface( x, y, source, destination );
}

void efface_fenetre(SDL_Surface *psurf){
    clear_surface(psurf);
}

void maj_fenetre(SDL_Window *pWindow){
    SDL_UpdateWindowSurface(pWindow);
}

void prepareAllSpriteDuJeu(TplateauJeu jeu, int largeur, int hauteur, SDL_Surface **TabSprite, SDL_Surface* destination ){
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
            if (jeu[i][j] != NULL){
                prepare_sprite(i*40,j*40,TabSprite[jeu[i][j]->nom],destination);  //remarque les sprites font 40*40 pixels
                //prepare_sprite(i*40,j*40,TabSprite[3],destination);
            }
            else{
                    if (i == 5 && j == 9) prepare_sprite(i*40,j*40,TabSprite[8],destination); // pont
                    else if ( j == 9) prepare_sprite(i*40,j*40,TabSprite[6],destination); //eau
                    else if ( (i==5 && j!=0 && j!=18) ) prepare_sprite(i*40,j*40,TabSprite[9],destination); //terre
                    else prepare_sprite(i*40,j*40,TabSprite[7],destination); //herbe
                }
            }
        }
}

//fonction ajoutée
void prepareSpriteplayer(TplateauJeu jeu,SDL_Surface **tab,SDL_Surface *destination,TListePlayer player)
{
    TListePlayer newP = player;//on crée ici une copie de la liste player

    while(newP!=NULL)//et tant que la copie est différent de NULL
    {
        int gameX = newP->pdata->posX;//on stocke la position en x de l'unité courante
        int gameY = newP->pdata->posY;//on stocke la position en y de l'unité courante
        if (jeu[gameX][gameY] != NULL){//et si cette position en x et y de l'unité est NULL sur le tableau, alors on place le sprite correspondant à 'unité sur le plateau de jeu
            prepare_sprite(gameX*40,gameY*40,tab[jeu[gameX][gameY]->nom],destination);
        }
        newP=newP->suiv;
    }
}


