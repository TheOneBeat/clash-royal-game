#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "clashloyal.h"
#include <math.h>
#include <time.h>

//typedef Tunite* ** TplateauJeu;

TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[6]={"T", "R", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}

Tunite *creeTour(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tour;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 120;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}

//A vous de jouer

Tunite *creeArcher(int posx, int posy)
{
    Tunite *nouv=(Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 2;
    return nouv;
}
Tunite *creeGargouille(int posx, int posy)
{
    Tunite *nouv=(Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 1;
    return nouv;
}
Tunite *creeDragon(int posx, int posy)
{
    Tunite *nouv=(Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 70;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 3;
    return nouv;
}
Tunite *creeChevalier(int posx, int posy)
{
    Tunite *nouv=(Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 4;
    return nouv;
}



Bool tourRoiDetruite(TListePlayer player)
{
    Bool value=false;
    TListePlayer the_list = player;
    while(the_list!=NULL)/*on vérifie si la liste est vide ou non , ce qui nous permet de savoir si on entre ou pas dans la boucle */
    {
        if (the_list->pdata->nom == 1) /*on vérifie si l'unité courante de la liste (the_list->pdata) est l'unité tourderoi*/
            {
                if(the_list->pdata->pointsDeVie <=0) /*si c'est la cas on vérifie si son point de vie est inférieur ou égale à 0*/
                {
                    value=true; /*si c'est le cas value prend la valeur de true, et avec le break, on sort de la boucle, ce qui fait que la fonction renvoie true si la tour de roi a un pv <=0*/
                    break;
                }
            }
        the_list=the_list->suiv;
    }
    return value;//value == true si la tourderoi a un pv <=0 sinon renvoie false
}

//positionner toutes les unites sur le plateau a l'aide de leurs coordonnees
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu)
{
    TListePlayer the_final_list=player;//on crée ici une copie de la liste player
    int posx=0,posy=0;//on définit 2 variables posx et posy qui vont contenir les positions en x et y de chaque joueur


    while(the_final_list!=NULL)
    {
        posx=the_final_list->pdata->posX; //ici on met en posx la position en x de l'unité coutante de la liste 'the_final_list'
        posy=the_final_list->pdata->posY; //ici on met en posx la position en y de l'unité coutante de la liste 'the_final_list'
        if (jeu[posx][posy]== NULL)// on vérifie si le plateau de jeu en position posx et poxy est vide ou pas
            jeu[posx][posy]=the_final_list->pdata;//si c'est le cas, on place l'unité à la postion posx et posy

        the_final_list=the_final_list->suiv;//on passe à l'unité suivante de la liste
    }

}

//creation d'une liste d'unites d'un joueur qui a la portee pour attaquer une unite de l'autre joueur

TListePlayer quiEstAPortee(TListePlayer player, Tunite *uneUniteDeLautreJoueur)
{
    TListePlayer new_player = player;//on crée ici une copie de la liste player qui représente la liste des unités qui vont attaquer
    TListePlayer value =NULL; //on crée et on initialise à NULL la liste à retourner à la fin de la fonction

    Tcible pos_unite_adverse= uneUniteDeLautreJoueur->maposition;//on stocke en local la position air ou sol de l'unité adverse que l'on veut attaquer

    while(new_player!=NULL)
    {
        int cb_atq=new_player->pdata->cibleAttaquable; /*on stocke en local la postion de l'unite que l'unité courante de la liste new_player peut attaquer, position qui changera en fonction de l'unité courante*/

        /*on vérifie si d'une part l'unité à attaquer est au sol et si la cible qui va l'attaquer est au sol, en solEtAir ou au sol

        et d'autre part si l'unité à attaquer est en air et si la cible qui va l'attaquer est  au solEtAir ou en air */

        if (((pos_unite_adverse ==0) && ((cb_atq==0) || (cb_atq==1) || (cb_atq==2))) || ((pos_unite_adverse ==2) && (cb_atq==1 || cb_atq==2)))
        //si c'est le cas
        {
            float xdis,ydis,distance;
            float portee_new_player=(float)(new_player->pdata->portee);//on stocke en local la portee de l'unitee qui aura validée la première condition

            xdis=(float)((uneUniteDeLautreJoueur->posX)-(new_player->pdata->posX));//on stocke en local la différence en x de l'unité courante qui va attaquer et l'unité qui va se faire attaquée
            ydis=(float)((uneUniteDeLautreJoueur->posY)-(new_player->pdata->posY));//on stocke en local la différence en x de l'unité courante qui va attaquer et l'unité qui va se faire attaquée

            //calcul de la distance entre l'unité qui va taqquer et l'unité attaquée en se basant sur leur difference en x et y a l'aide de Pythagore
            distance=sqrtf(powf(xdis,2)+powf(ydis,2));
            if (distance <= portee_new_player)
                value = AjoutDebut(value,new_player->pdata);
        }
        new_player=new_player->suiv;
    }

    return value;
}

//ajouter une unite au debut de la liste d'unités d'un joueur

TListePlayer AjoutDebut(TListePlayer forme_p,Tunite *unite)
{
	TListePlayer tmp=malloc(sizeof(TListePlayer));//on alloue de la mémoire pour la cellule de TListePlayer a retouné à la fin de la fonction
	tmp->pdata = unite;//on met en pdata l'unité à ajouter

	if (forme_p!=NULL)
	{
		tmp->suiv=NULL;//si la liste au debut est vide, alors le suivant de notre tmp est NULL
	}
	else
	{
		tmp->suiv=forme_p;//sinon, le suivant contiendra la liste du debut(la  liste dans le paramètre de l'appel de la fonction)
	}
	return tmp;
}

//simulation d'un combat entre les unites des deux joueurs
void combat(TListePlayer player, TListePlayer player_2)
{

    TListePlayer the_listAtt = player;//on crée ici une copie de la liste player qui représente la liste des unités qui vont attaquer
	TListePlayer the_listeA = player_2;//on crée ici une copie de la liste player_2 qui représente la liste des unités qui vont se faire attaqué

    while(the_listeA != NULL)
    {
		TListePlayer Atq = quiEstAPortee(the_listAtt,the_listeA->pdata);//cette fonction renvoie la liste d'unités pouvant attaquer l'unité courante de player_2(the_listA)

		while(Atq != NULL)
		{
			if (Atq->pdata->peutAttaquer==1)//on vérifie si l"unité courante qui est est à portée, peut attaquer
			{
				the_listeA->pdata->pointsDeVie -= Atq->pdata->degats;//si oui alors l'autre unité, aura son pv décrementée des points  de degats de l'unitée à portée
				Atq->pdata->peutAttaquer=0;//Et l'unité à portée ne pourra plus attaquer jusqu'à la fin du tour
			}
			Atq=Atq->suiv;// ensuite on passe à l'unité à portée suivante et on répète la même chose
		}
		the_listeA=the_listeA->suiv;
    }
}

//suppression des unites mortes (dont le pv <= 0)

TListePlayer SupprimerValuePvZero(TListePlayer player_2)
{
	TListePlayer new_p = player_2;//on crée ici une copie de la liste player_2

	while(new_p!=NULL)
	{
		if (new_p->pdata->pointsDeVie <= 0) //on vérifie si l'unité courante à son pv <= 0
			supp_unite(&player_2,new_p->pdata);//si c'est le cas, on le supprime avec l'appel de la fonction supp_unite

		new_p=new_p->suiv;
	}
	return player_2;//et à la fin, on retourne la liste player_2 avec les unités mortes en moins
}

void supp_unite(TListePlayer *new_p,Tunite *value) {
    if (*new_p ==NULL)//si la liste est vide, alors on ne fait rien puisqu'il n'ya rien à supprimer
        return;
    else if ((*new_p)->pdata == value)//par  contre si la liste n'est pas vide et que l'unité courante de la liste est égale à 'lunité à supprimer (value)
    {
        TListePlayer tmp=*new_p;//alors on crée une liste locale qui va contenir la liste au début
        *new_p = (*new_p)->suiv;//ensuite on déplce le pointeur de la liste principale sur l'unité suivante
		free(tmp);//et pour finir on supprime l'unité precedent pointé par tmp
    }
    else //si l'unité à supprimer n'est pas au debut de la liste, on fait une boucle et on recommece les vérifications
    {
        for (TListePlayer i = *new_p; i->suiv!=NULL; i = i->suiv)
        {
           if ((i->suiv)->pdata == value)
            {
                TListePlayer tmp = i->suiv;
                i->suiv = tmp->suiv;
                free(tmp);
                break;
           }
        }
    }
}

//incrementer de le nombre d'elixir d'un joueur
void elixir_increase(int *elix)
{
    *elix +=1;
}

//ajouter une unite a la liste d'un joueur
void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite)
{
    if (nouvelleUnite!=NULL)/*pour rajouter une unité à une liste, on vérifie si l'unité est NULL, si c'est pas le cas, on entre dans le if

    et on rajoute l'unité au debut de la liste */
    {
        TListePlayer tmp=malloc(sizeof(struct T_cell));// on crée une liste nouvelle tmp
        tmp->pdata=nouvelleUnite; // son unité courante est la nouvelle unité
        tmp->suiv=*player;//et le pointeur suivant de la nouvelle liste va pointé sur l'ancienne liste du début
        *player=tmp;// et pour finir, on remet dans la fonction player, la nouvelle liste de créer avec la nouvelle unité en plus
    }

}

/*connaitre dans quelle zone de jeu est l'unite: 0 = (la position en y de l'unité est <= 8), 1 = (la position en y de l'unité est >= 10),

2 = (la position en y de l'unité est == 9)*/
int zone(Tunite* unite){
    int ypos = unite->posY;
    int zone_pos=0;

    if (ypos >= 0 && ypos <= 8)
        zone_pos=0;
    else if (ypos >= 10 && ypos <= 18)
        zone_pos=1;
    else if (ypos == 9)
        zone_pos=2;

    return zone_pos;// à la fin, la fonction retourne 0, 1 ou 2
}

void move_player(TplateauJeu jeu, TListePlayer* player, int nbPlayer){
    TListePlayer new_player = *player;

    while (new_player != NULL)
    {
        Tunite* unite = new_player->pdata;//on stocke l'unité courante de la liste new_player
        int new_posX = unite->posX, new_posY = unite->posY;//on stocke également les pos en x et y des unités courantes
        int init_posX = new_posX, init_posY = new_posY;/* on stocke des positions en x ey y qui nous permettront de ne pas déplacer iune unité du joueur
        s'il y 'a un obstacle ou unité à sa future position de déplacement*/

        if (unite->coutEnElixir != 0)//si l'unité a un coutEnElixir différent de 0, alors ça veut dire que l'unité courante à dépalcer n'est ni une tour ni un tour de roi
        {
            if (nbPlayer == 0){//si l'unité est l'une de la parti haute du plateau de jeu (unité rouge)

                if (zone(unite) == 0){//s'il se trouve dans son camp alors

                    if (init_posX == 5)//si l'unité a la même position en x que les tours alors il avance en y de 1
                        new_posY += 1;

                    else if (init_posX <= 4){//si l'unité à une position en x inférieur à celle des tours, alors il avance en x de 1(incrémentation)
                        new_posX += 1;
                        if (init_posY < 8)//et si il est toujours dans son camp, alors sa position en y, incrémente de 1
                            new_posY += 1;
                    }

                    else if (init_posX >= 4){//si l'unité à une position en x supérieur à celle des tours, alors il décrménte en x de 1
                        new_posX -= 1;
                        if (init_posY < 8)//et si il est toujours dans son camp, alors sa position en y, incrémente de 1
                            new_posY += 1;
                    }
                }

                if (zone(unite) == 1 || zone(unite) == 2){ //si l'unité se trouve, dans sson camp, ou alors se trouve sue le pont, alors il avance et donc incrémentation de y de 1
                    new_posY += 1;
                }

            }
            else{//sinon, si l'unité est l'une de la parti basse du plateau de jeu (unité Bleu)

                if (zone(unite) == 1){//si l'unité est dans son camp

                    if (init_posX == 5)//si l'unité a la même position en x que les tours alors il avance en y, donc on décremnte son y de 1
                        new_posY -= 1;
                    else if (init_posX <= 4){//si l'unité à une position en x inférieur à celle des tours, alors il avance en x de 1; donc on incrémente x de 1
                        new_posX += 1;
                        if (init_posY > 10)//et si il est toujours dans son camp, alors sa position en y, décrémente de 1
                            new_posY -= 1;
                    }
                    else if (init_posX >= 4){//si l'unité à une position en x supérieur à celle des tours, alors il décréménte en x de 1
                        new_posX -= 1;
                        if (init_posY > 10)//et si il est toujours dans son camp, alors sa position en y, décrémente de 1
                            new_posY -= 1;
                    }
                }

                if (zone(unite) == 0 || zone(unite) == 2){//si l'unité se trouve, dans sson camp, ou alors se trouve sue le pont, alors il avance et donc décrémentation de y de 1
                    new_posY -= 1;
                }

            }

        }

        new_player = new_player->suiv;//ensuite on passe à l'unité suivante

        if (positionAvailable(new_posX, new_posY, jeu))//on vérifie si les nouvelles prochaines positions en x et y de l'unité sont libres d'usage ou pas
        {
            //si oui, alors on entre dans la boucle et l'unité en question aura comme postions les nouvelles valeurs x et y

            unite->posX = new_posX;
            unite->posY = new_posY;
            jeu[init_posX][init_posY] = NULL;//et on remet l'ancienne position de l'unité à NULL
        }

    }

}

Bool positionAvailable(int xpos, int ypos,TplateauJeu jeu)//savoir si une unité est présente sur la case [xpos][ypos] du plateau de jeu...
{
    if (jeu[xpos][ypos] == NULL)
        return true;
    return false;
}

//acheter une unite a partir du nombre d'elixir du joueur et la placer aléatoirement sur le plateau de jeu
Tunite* AcheteUnite(int *elixirEnStockduJoueur, TplateauJeu jeu, int nbPlayer)
{
    Tunite *unite_cree = NULL;//initialisation de l'unité à retourner à la fin de la liste
    int proba, rand_unite;
    srand(time(NULL));
    proba = (rand() % 2);//retourne une valeur entre 0 et 1

    int xpos, ypos, MAXX = 10, MINX = 0, MAXY, MINY;

    do{

        if (nbPlayer == 0){//si le joueur est dans le côté haut du plateau de jeu
            MINY = 3;//alors la position Y minimale de l'unité à créer est 3
            MAXY = 8;//alors la position Y maximale de l'unité à créer est 8
        }
        else//si le joueur est dans le côté bas du plateau de jeu
        {
            MINY = 10;//alors la position Y minimale de l'unité à créer est 10
            MAXY = 15;//alors la position Y maximale de l'unité à créer est 15
        }

        srand(time(NULL));
        xpos = (rand() % (MAXX + 1 - MINX)) + MINX;//retourne une valeur entre 0 et 10
        ypos = (rand() % (MAXY + 1 - MINY)) + MINY;//retorune une valeur entre 10 et 15 si l'unité se trouve dans le côté bas du plateau de jeu ou alors
                                                    //retorune une valeur entre 3 et 8 si l'unité se trouve dans le côté haut du plateau de jeu
    } while (!positionAvailable(xpos, ypos,jeu));//on boulce tant que la position[xpos][ypos] trouvée n'est pas NULL


    if ((proba == 1) && (*elixirEnStockduJoueur > 0))
    {
        // gargouille = 1, archer = 2, dragon = 3, chevalier = 4

        do
        {
            // selection de l'unité en fonction de cout en elixir

            srand(time(NULL));
            rand_unite =(rand() % 4)+1;//retourne une valeur entre 1 et 4, qui nous permettra avec le switch, de savoir quelle unité créée

        } while (*elixirEnStockduJoueur < rand_unite);//on boulce tant que l'elixir du joueur (player) est inférieur à l'indice de l'unité à créée(rand_unite)

        switch (rand_unite)
        {
            case 1:
                unite_cree = creeGargouille(xpos, ypos);
            break;
            case 2:
                unite_cree = creeArcher(xpos, ypos);
            break;
            case 3:
                unite_cree = creeDragon(xpos, ypos);
            break;
            case 4:
                unite_cree = creeChevalier(xpos, ypos);
            break;
        }

        *elixirEnStockduJoueur -= rand_unite;

    }
    //printf("\n Achat de nouvelle unitee \n");
    return unite_cree;//on retourne ainsi l'unité créée
}

void Affiche_unite(TListePlayer player, int nbPlayer, int *elixir)
{

    for (int i = 0; i < 30; i++)
        printf("=");

    printf("\n JOUEUR ");

    if (nbPlayer == 0)//si nb_player vaut 0 alors on affichera dans la console à côté de joueur, le numéro bleu sinon le numéro Rouge
        printf("Rouge");
    else
        printf("Bleu");

    printf("\n\n");

    TListePlayer new_player = player;

    while(new_player!=NULL)
    {
        char *unite;//initialisation du pointeur que l'on retournera en tant que string

        switch(new_player->pdata->nom){
            case 0:
                unite = "Tour";
            break;
            case 1:
                unite= "Tour_du_Roi";
            break;
            case 2:
                unite= "Archer";
            break;
            case 3:
                unite= "Chevalier";
            break;
            case 4:
                unite= "Dragon";
            break;
            case 5:
                unite= "Gargouille";
            break;
        }

        printf(" %s | %d pv \n", unite, new_player->pdata->pointsDeVie);


        new_player=new_player->suiv;
    }
    printf("\n Nombre d'unites du joueur -> %d \n",longueur_liste(player));

    printf("\n %d elixir \n", *elixir);

}

void can_attack(TListePlayer player)
{
    TListePlayer new_player = player;//on crée ici une copie de la liste player qui va nous permettre de faire la boucle
    while(new_player!=NULL)
    {
        new_player->pdata->peutAttaquer=1; //et on parcourt toutes les unités du joueur player en remettant à 0 leur propriété peut attaquer à 0
        new_player=new_player->suiv;
    }
}

//******************************SAUVEGARDE***************************************************


int longueur_liste(TListePlayer player)
{
    TListePlayer tmp = player;//on crée ici une copie de la liste player qui va nous permettre de faire la boucle
    int len=0;//on initialise une variable len à 0

    while(tmp!=NULL)//tant que la liste tmp n'est pas NULL, on incrémente la varialbe len de 1
    {
        len+=1;
        tmp=tmp->suiv;
    }
    return len;
}

void save_sequential(char *file_name,TListePlayer player_1,TListePlayer player_2)
{
	FILE *path=fopen(file_name,"w");//on ouvre le fichier filename qui aura comme nom path, une fois ouvert

	if (path==NULL)// si on n'arrive pas à ouvrie le fichier
	{
		fprintf(stderr,"\Erreur:Impossible d'ecrire dans le fichier %s \n", file_name);
		return (EXIT_FAILURE);//alors on renvoie un signal de FAILURE et on sort de la fonction
	}
	//si le path est différent de NULL alors

    TListePlayer tmp = player_1;//on crée ici une copie de la liste player_1 qui va nous permettre de faire la boucle
    TListePlayer temp = player_2;//on crée ici une copie de la liste player_2 qui va nous permettre de faire la boucle

    int len = longueur_liste(tmp); //on stocke la longueur de la liste d'unités de tmp

    fprintf(path,"la longueur : %d \n",len); // on écrit dans le fichier ouvert, la longueur

    while(tmp != NULL) //et on écrit, après la longueur,les propriétés de chaque unité: son nom, pv, degat etc...
    {
        fprintf(path,"le nom de l'unité :%d ",tmp->pdata->nom);
        fprintf(path,"la cible attaquable: %d ",tmp->pdata->cibleAttaquable);
        fprintf(path,"sa position: %d ",tmp->pdata->maposition);
        fprintf(path,"son point de vie: %d ",tmp->pdata->pointsDeVie);
        fprintf(path,"sa vitesse d'attaque: %f ",tmp->pdata->vitesseAttaque);
        fprintf(path,"ses degats: %d ",tmp->pdata->degats);
        fprintf(path,"sa portee: %d ",tmp->pdata->portee);
        fprintf(path,"sa vitesse de deplacement: %f ",tmp->pdata->vitessedeplacement);
        fprintf(path,"son posX: %d son posY: %d ",tmp->pdata->posX,tmp->pdata->posY);
        fprintf(path,"peut_attaquer: %d ",tmp->pdata->peutAttaquer);
        fprintf(path,"son cout en elixir: %d\n\n\n",tmp->pdata->coutEnElixir);

        tmp = tmp->suiv;
    }

    //et on répète la même chose pour les unités du joueur temp (player_2)

    int length = longueur_liste(temp);

    printf("la valeur de len : %d \n",length);

    fprintf(path,"la longueur : %d \n",length);

    while(temp != NULL)
    {
        fprintf(path,"le nom de l'unité :%d ",temp->pdata->nom);
        fprintf(path,"la cible attaquable: %d ",temp->pdata->cibleAttaquable);
        fprintf(path,"sa position: %d ",temp->pdata->maposition);
        fprintf(path,"son point de vie: %d ",temp->pdata->pointsDeVie);
        fprintf(path,"sa vitesse d'attaque: %f ",temp->pdata->vitesseAttaque);
        fprintf(path,"ses degats: %d ",temp->pdata->degats);
        fprintf(path,"sa portee: %d ",temp->pdata->portee);
        fprintf(path,"sa vitesse de deplacement: %f ",temp->pdata->vitessedeplacement);
        fprintf(path,"son posX: %d son posY: %d ",temp->pdata->posX,temp->pdata->posY);
        fprintf(path,"peut_attaquer: %d ",temp->pdata->peutAttaquer);
        fprintf(path,"son cout en elixir: %d\n\n\n",temp->pdata->coutEnElixir);

        temp = temp->suiv;
    }


	fclose(path);// à la fin on ferme le fichier ouvert 'path'
	printf("Le fichier  partieseq.cls a ete cree, essayez de le lire avec un notepad++,gedit, etc.\n");

}

void load_sequential(char *file_name,TListePlayer *player_1,TListePlayer *player_2)
{
	FILE *path=fopen(file_name,"r");//on ouvre le fichier filename qui aura comme nom path, une fois ouvert

	if (path==NULL)// si on n'arrive pas à ouvrie le fichier
	{
		fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n",file_name);
		return(EXIT_FAILURE);//alors on renvoie un signal de FAILURE et on sort de la fonction
	}

	int longueur=0,length=0;

	fscanf(path,"la longueur : %d \n",&longueur);//on lie la première valeur du fichier ouvert, qui représente la longueur de la liste des unités du premier joueur, ici (player_1)

	for(int i=0;i<longueur;i++)
    {
        /*on crée ici 3 variables dans la boucles, qui permettront de stocker les informations qui des unités qui sont de type enum

        à savoir: le nom de l'unité, la cible Attaquable et la position de l'unité */

        int unite_nom;
        int cbAtk;
        int position;

        //en passant, on alloue de la mémoire à l'unité que l'on va créer en lisant les informations du fichier ouvert path

        Tunite *unite=malloc(sizeof(Tunite));// et cela en faisant un malloc d'une unité créée

        //ensuite, on lie les informations concernant l'unité à créer, à savoir: son nom, son pv, ses degats, etc...

        fscanf(path,"le nom de l'unité :%d ",&unite_nom);
        fscanf(path,"la cible attaquable: %d ",&cbAtk);
        fscanf(path,"sa position: %d ",&position);
        fscanf(path,"son point de vie: %d ",&unite->pointsDeVie);
        fscanf(path,"sa vitesse d'attaque: %f ",&unite->vitesseAttaque);
        fscanf(path,"ses degats: %d ",&unite->degats);
        fscanf(path,"sa portee: %d ",&unite->portee);
        fscanf(path,"sa vitesse de deplacement: %f ",&unite->vitessedeplacement);
        fscanf(path,"son posX: %d son posY: %d ",&unite->posX,&unite->posY);
        fscanf(path,"peut_attaquer: %d ",&unite->peutAttaquer);
        fscanf(path,"son cout en elixir: %d\n\n\n",&unite->coutEnElixir);

        /*ensuite on stocke directment sur le contenu des propriétés de type enum de l'unité, les valeurs stockés par les les variables

        unite_nom, cb_atk, position*/

        unite->nom=unite_nom;
        unite->cibleAttaquable=cbAtk;
        unite->maposition=position;

        //et pout finir, on ajoute dans la liste d'unité du joueur player_1, l'unité créer

        AjouterUnite(player_1,unite);

    }

    //et on répète les même instructions pour le joueur player_2

    fscanf(path,"la longueur : %d \n",&length);

	for(int i=0;i<length;i++)
    {

        int unite_nom;
        int cbAtk;
        int position;

        Tunite *unite=malloc(sizeof(Tunite));

        fscanf(path,"le nom de l'unité :%d ",&unite_nom);
        fscanf(path,"la cible attaquable: %d ",&cbAtk);
        fscanf(path,"sa position: %d ",&position);
        fscanf(path,"son point de vie: %d ",&unite->pointsDeVie);
        fscanf(path,"sa vitesse d'attaque: %f ",&unite->vitesseAttaque);
        fscanf(path,"ses degats: %d ",&unite->degats);
        fscanf(path,"sa portee: %d ",&unite->portee);
        fscanf(path,"sa vitesse de deplacement: %f ",&unite->vitessedeplacement);
        fscanf(path,"son posX: %d son posY: %d ",&unite->posX,&unite->posY);
        fscanf(path,"peut_attaquer: %d ",&unite->peutAttaquer);
        fscanf(path,"son cout en elixir: %d\n\n\n",&unite->coutEnElixir);

        unite->nom=unite_nom;
        unite->cibleAttaquable=cbAtk;
        unite->maposition=position;

        //et ici, l'unité créée est ajoutée à la liste d'unités du joueur player_2

        AjouterUnite(player_2,unite);

    }

	fclose(path);//ensuite, on ferme le fichier ouvert 'path'
	printf("Le fichier  partieseq.cls a bien ete load, le programme devrait marcher laa ... etc.\n");
}

void save_binary(char *file_name,TListePlayer player_1,TListePlayer player_2)
{
    FILE *path=fopen(file_name,"wb");//on ouvre le fichier filename qui aura comme nom path, une fois ouvert
	if (path==NULL)// si on n'arrive pas à ouvrie le fichier
	{
		fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n",file_name);
		return(EXIT_FAILURE);//alors on renvoie un signal de FAILURE et on sort de la fonction
	}
	//si le path est différent de NULL alors

	int length=longueur_liste(player_1),longueur=longueur_liste(player_2);//on stocke la longueur de la liste d'unités de player_1 et player_2

    //on crée ici une copie tmp de la liste player_1 qui va nous permettre de faire la boucle
    //on crée ici une copie temp de la liste player_2 qui va nous permettre de faire la boucle
	TListePlayer tmp =player_1, temp= player_2;

	fwrite(&length,sizeof(int),1,path);//ici, on écrit dans le fichier binaire ouvert ici 'path',la longueur de la liste du joueur tmp (player_1)

	while(tmp!=NULL)
    {
        fwrite(tmp->pdata,sizeof(Tunite),1,path);//on écrit à la suite, les informations concernant les propriétés de chaque joueur
        tmp=tmp->suiv;
    }

    //et on répète la même chose pour les unités du joueur temp (player_2)

    fwrite(&longueur,sizeof(int),1,path);

    while(temp!=NULL)
    {
        fwrite(temp->pdata,sizeof(Tunite),1,path);
        temp=temp->suiv;
    }

    fclose(path);
    printf("\nle load du fichier partiebin.clb a bien ete fait \n");
}

void load_binary(char *file_name,TListePlayer *player_1, TListePlayer *player_2)
{
    FILE *path=fopen(file_name,"rb");//on ouvre le fichier filename qui aura comme nom path, une fois ouvert
	if (path==NULL)// si on n'arrive pas à ouvrie le fichier
	{
		fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n",file_name);
		return(EXIT_FAILURE);//alors on renvoie un signal de FAILURE et on sort de la fonction
	}

    int len=0,longueur=0;

    fread(&len,sizeof(int),1,path);//on lie la première valeur du fichier ouvert, qui représente la longueur de la liste des unités du premier joueur, ici (player_1)

    for(int i=0;i<len;i++)
    {
        //en passant, on alloue de la mémoire à l'unité que l'on va créer en lisant les informations du fichier ouvert path

        Tunite *unite=malloc(sizeof(Tunite));//et cela en faisant un malloc

        fread(unite,sizeof(Tunite),1,path);//ensuite on lie les informations de chaque unités

        AjouterUnite(player_1,unite); // et on ajoute l'unité créé au player 1
    }

    printf("\nmaintenant lecture de la liste 2 \n");

    //et on répète ensuite le même procédé pour le joueur (player_2)

    fread(&longueur,sizeof(int),1,path);

    for(int i=0;i<longueur;i++)
    {

        Tunite *unite=malloc(sizeof(Tunite));

        fread(unite,sizeof(Tunite),1,path);

        AjouterUnite(player_2,unite);
    }

    fclose(path);// et à la fin, on ferme le fichier ouvert 'path'

    printf("\nle load du fichier partiebin.clb a bien ete fait \n");
}

void suppAllUnite(TListePlayer *new_p)
{
    if (*new_p ==NULL) //si la liste est vie, alors on ne fait rien
        return;

    while(*new_p != NULL)//sinon
    {
        TListePlayer tmp=*new_p;//on crée une liste local qui va contenir l'unité
        *new_p = (*new_p)->suiv;
		free(tmp);
    }
    printf("\nSuppression des unites du joueur reussie \n");
}



