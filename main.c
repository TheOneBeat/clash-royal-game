

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonction d'affichage pour le jeu 2048
#include "clashloyal.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define taille 400



/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*40,
        HAUTEURJEU*40,
        SDL_WINDOW_SHOWN
    );

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'écran
    SDL_Surface* pSpriteTour= SDL_LoadBMP("./data/Tour.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp"); //indice 1
    SDL_Surface* pSpriteArcher = SDL_LoadBMP("./data/ArcherRouge.bmp"); //indice 2
    SDL_Surface* pSpriteChevalier = SDL_LoadBMP("./data/ChevalierRouge.bmp"); //indice 3
    SDL_Surface* pSpriteDragon = SDL_LoadBMP("./data/DragonRouge.bmp"); //indice 4
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/GargouilleRouge.bmp"); //indice 5
    SDL_Surface* pSpriteEau = SDL_LoadBMP("./data/Eau.bmp"); //indice 6  Ne figure pas dans l'enum TuniteDuJeu
    SDL_Surface* pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp"); //indice 7 idem
    SDL_Surface* pSpritePont = SDL_LoadBMP("./data/Pont.bmp"); //indice 8 idem
    SDL_Surface* pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp"); //indice 9 idem

    SDL_Surface* pSpriteArcherBleu = SDL_LoadBMP("./data/ArcherBleu.bmp"); //indice 2 idem
    SDL_Surface* pSpriteChevalierBleu = SDL_LoadBMP("./data/ChevalierBleu.bmp"); //indice 3 idem
    SDL_Surface* pSpriteDragonBleu = SDL_LoadBMP("./data/DragonBleu.bmp"); //indice 4 idem
    SDL_Surface* pSpriteGargouilleBleu = SDL_LoadBMP("./data/GargouilleBleu.bmp"); //indice 5 idem
    //indice dans la table TabSpritePlayer2...


    // ASTUCE : on stocke le sprite d'une unité à l'indice de son nom dans le type enum TuniteDuJeu, dans le tableau TabSprite
    // SAUF pour l'Eau, l''herbe et le pont qui apparaitront en l absence d'unité (NULL dans le plateau) et en fonction de certains indices x,y définissant le chemin central


    SDL_Surface* TabSprite[10]={pSpriteTour,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};

    //SDL_Surface* TabSpritePlayer_1[10]={pSpriteTour,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};

    SDL_Surface* TabSpritePlayer_2[10]={pSpriteTour,pSpriteTourRoi,pSpriteArcherBleu,pSpriteChevalierBleu,pSpriteDragonBleu,pSpriteGargouilleBleu,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};

    if ( pSpriteTour )  //si le premier sprite a bien été chargé, on suppose que les autres aussi
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);

        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);
        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);

        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */
        /*

        // FIN de vos variables                                                              */
        /**********************************************************************/
        TListePlayer joueur_1=NULL;
        TListePlayer joueur_2=NULL;

        int elixirPlayer1=3, elixirPlayer2=3;// le nombre d'elixir au debut pour chaque joueur est de 3

        //Les unités du joueur P1
        AjouterUnite(&joueur_1,creeTour(5,3));
        AjouterUnite(&joueur_1,creeTourRoi(5,1));


        //Les unités du joueur P2
        AjouterUnite(&joueur_2,creeTour(5,15));
        AjouterUnite(&joueur_2,creeTourRoi(5,17));

        int randFstPlayer;
        Tunite *unit1,*unit2;


        // boucle principale du jeu
        int cont = 1;

        do
            {
                SDL_PumpEvents();


                //afichage du jeu ...

                prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                prepareSpriteplayer(jeu,TabSpritePlayer_2,pWinSurf,joueur_2);
                maj_fenetre(pWindow);


                /***********************************************************************/
                /*                                                                     */
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU
                /*                                                                     */
                /*                                                                     */
                // FIN DE VOS APPELS
                /***********************************************************************/

                randFstPlayer =rand()%2;/* cette variable prend une valeur entre 0 et 1*/

                //elle nous permettra de gérer les phases de combats et de création d'unité pour qu'il n'y ait pas de joueur avantagé pendant ces phases-là


                //PHASE COMBAT...


                if (randFstPlayer == 0)//
                {
                    combat(joueur_1,joueur_2);
                    combat(joueur_2,joueur_1);
                }
                else
                {
                    combat(joueur_2,joueur_1);
                    combat(joueur_1,joueur_2);
                }

                initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
                PositionnePlayerOnPlateau(joueur_1,jeu);
                PositionnePlayerOnPlateau(joueur_2,jeu);


                system("cls");//cette instruction permet de vider la console

                Affiche_unite(joueur_1,0,&elixirPlayer1);

                Affiche_unite(joueur_2,1,&elixirPlayer2);

                initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
                PositionnePlayerOnPlateau(joueur_1,jeu);
                PositionnePlayerOnPlateau(joueur_2,jeu);


                //FIN DE LA PHASE COMBAT...

                //*******************************************************

                //DEBUT PHASE DEPLACEMENT...

                //deplacement du joueur 1...

                move_player(jeu,&joueur_1,0);

                initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
                PositionnePlayerOnPlateau(joueur_1,jeu);
                PositionnePlayerOnPlateau(joueur_2,jeu);

                //deplacement du joueur 2...

                move_player(jeu,&joueur_2,1);

                initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
                PositionnePlayerOnPlateau(joueur_1,jeu);
                PositionnePlayerOnPlateau(joueur_2,jeu);


                //FIN PHASE DEPLACEMENT

                //*******************************************************

                //DEBUT PHASE CREATION

                 if (randFstPlayer == 0)
                {
                    unit1=AcheteUnite(&elixirPlayer1,jeu,0);
                    unit2=AcheteUnite(&elixirPlayer2,jeu,1);
                }
                else
                {
                    unit2=AcheteUnite(&elixirPlayer2,jeu,1);
                    unit1=AcheteUnite(&elixirPlayer1,jeu,0);
                }

                AjouterUnite(&joueur_1,unit1);
                AjouterUnite(&joueur_2,unit2);


                //FIN PHASE CREATION

                //*******************************************************

                //DEBUT PHASE ELIXIR

                elixir_increase(&elixirPlayer1);
                elixir_increase(&elixirPlayer2);

                //FIN PHASE ELIXIR

                //*******************************************************

                //*******************************************************

                //PHASE permettant d'arrêter le programme si l'un des joueurs a son tour de roi détruite...

                if (tourRoiDetruite(joueur_2))
                {
                    system("cls");
                    printf(" Le joueur ROUGE A GAGNE \n\n");

                    joueur_2=SupprimerValuePvZero(joueur_2);
                    joueur_1=SupprimerValuePvZero(joueur_1);


                    break;
                }

                if (tourRoiDetruite(joueur_1))
                {
                    system("cls");
                    printf(" Le joueur BLEU A GAGNE \n\n");

                    joueur_2=SupprimerValuePvZero(joueur_2);
                    joueur_1=SupprimerValuePvZero(joueur_1);

                    break;
                }
                //*******************************************************

                //*******************************************************

                //Phase suppression des unités dont le pv est inférieur ou égale à 0 pour chacun des joueurs

                joueur_2=SupprimerValuePvZero(joueur_2);
                joueur_1=SupprimerValuePvZero(joueur_1);

                // Fin de la phase SUPPRESSION

                //*******************************************************

                //*******************************************************

                //Remettre la propriété peut_attaquer à 1 pour tous les unités encore vivants...

                can_attack(joueur_1);
                can_attack(joueur_2);

                //*******************************************************


                //AFFICHAGE DU JEU À CHAQUE tour...
                initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
                PositionnePlayerOnPlateau(joueur_1,jeu);
                PositionnePlayerOnPlateau(joueur_2,jeu);
                //affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);

                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                prepareSpriteplayer(jeu,TabSpritePlayer_2,pWinSurf,joueur_2);
                maj_fenetre(pWindow);
                SDL_Delay(taille);  //valeur du délai à modifier éventuellement

                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                if ( pKeyStates[SDL_SCANCODE_V] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur V */

                        //On vide les listes des joueurs 1 et 2 avant de load les unités du fichier de sauvegarde

                        //Debut Phase suppression

                        suppAllUnite(&joueur_1);
                        suppAllUnite(&joueur_2);

                        //Fin Phase suppression

                        //Debut phase Load//

                        load_sequential("partieseq.cls",&joueur_1,&joueur_2);

                        //Fin phase Load//

                        message("chargement","Le chargement du fichier sequentiel 'partieseq.cls' a bien ete effectue !");

                        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        prepareSpriteplayer(jeu,TabSpritePlayer_2,pWinSurf,joueur_2);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){

                        //On vide les listes des joueurs 1 et 2 avant de load les unités du fichier de sauvegarde

                        //Debut phase suppression

                        suppAllUnite(&joueur_1);
                        suppAllUnite(&joueur_2);

                        //Fin phase suppression

                        //Debut phase load

                        load_binary("partiebin.clb",&joueur_1,&joueur_2);

                        //Fin phase load

                        //Affichage du déroulement du jeu lors du load du dichier binaire

                        Affiche_unite(joueur_1,0,&elixirPlayer1);

                        Affiche_unite(joueur_2,3,&elixirPlayer2);

                        //Fin de la phase Affichage

                        message("chargement","Le chargement du fichier binaire 'partiebin.clb' a bien ete effectue !");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        prepareSpriteplayer(jeu,TabSpritePlayer_2,pWinSurf,joueur_2);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){

                        save_sequential("partieseq.cls",joueur_1,joueur_2);

                        message("Sauvegarde sequentiel","sauvegarde sous le fichier 'partieseq.cls' reussi ");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        prepareSpriteplayer(jeu,TabSpritePlayer_2,pWinSurf,joueur_2);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_S] ){

                        save_binary("partiebin.clb",joueur_1,joueur_2);

                        message("Sauvegarde binaire","sauvegarde sous le fichier 'partiebin.clb' reussi ");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        prepareSpriteplayer(jeu,TabSpritePlayer_2,pWinSurf,joueur_2);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){
                        cont = 0;  //sortie de la boucle
                }

        }while (!(tourRoiDetruite(joueur_1)) || !(tourRoiDetruite(joueur_2)));


        //fin boucle du jeu

        SDL_FreeSurface(pSpriteTour); // Libération de la ressource occupée par le sprite
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);

        SDL_FreeSurface(pSpriteArcherBleu);
        SDL_FreeSurface(pSpriteChevalierBleu);
        SDL_FreeSurface(pSpriteDragonBleu);
        SDL_FreeSurface(pSpriteGargouilleBleu);

    }
    else
    {
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
