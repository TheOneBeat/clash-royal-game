#ifndef JEU2048_H_INCLUDED
#define JEU2048_H_INCLUDED

#define LARGEURJEU 11
#define HAUTEURJEU 19

typedef enum{tour, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;

typedef enum
{
    false,
    true
}Bool;


typedef struct {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique la position des unités que l’on peut attaquer
    Tcible maposition;		//indique soit « air » soit « sol », utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c’est petit plus c’est rapide
    int degats;
    int portee ;			//en mètre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu
    int peutAttaquer;		//permet de gérer le fait que chaque unité attaque une
                            //seule fois par tour ;
                            //0 = a déjà attaqué, 1 = peut attaquer ce tour-ci
                            // à remettre à 1 au début de chaque tour
    int coutEnElixir;
} Tunite;

typedef struct T_cell{
    struct T_cell *suiv;//pointeur vers l'unité suivante de l'unité courante
    Tunite *pdata; //pointeur vers l'unité courante
} *TListePlayer;


typedef Tunite* ** TplateauJeu; //Plateau de jeu à 2 dimensions dont les cases sont des pointeurs de type (Tunite *)


TplateauJeu AlloueTab2D(int largeur, int hauteur);
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

//Fonctions creation d'unités de combats......

Tunite *creeTour(int posx, int posy);

Tunite *creeTourRoi(int posx, int posy);

Tunite *creeArcher(int posx, int posy);

Tunite *creeGargouille(int posx, int posy);

Tunite *creeDragon(int posx, int posy);

Tunite *creeChevalier(int posx, int posy);


//fonctions Affichages


void Affiche_unite(TListePlayer player, int nbPlayer, int *elixir);/*affiche dans la console le déroulement du jeu

avec pour chaque joueur, le nom et les pv de ses unités*/

//fonction tourDetruite

Bool tourRoiDetruite(TListePlayer player);

//fonction permettant de positionner les unités sur le plateau de jeu

void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu);

//fonctions Phase combat


TListePlayer quiEstAPortee(TListePlayer player, Tunite *uneUniteDeLautreJoueur); /*cette fonction retourne la liste des unités du player capable

d'aataquer une unité de l'autre joueur*/

void combat(TListePlayer player, TListePlayer new_player); /*cette fonction s'occupe de la phase combat entre les unités de chaque joueur */

TListePlayer SupprimerValuePvZero(TListePlayer player_2); //cette fonction appelle la fonction supp_unite après avoir trouver une unité du player_2 avec un pv <=0

void supp_unite(TListePlayer *new_p,Tunite *value); //cette fonction supprime l'unité value de la liste des unités du joueur new_p


//fonctions Phase déplacement


Bool positionAvailable(int xpos, int ypos,TplateauJeu jeu); //cette fonction permet de savoir si la position [xpos][ypos] sur le plateau de jeu est NULL ou non

int zone(Tunite* unite);//cette fonction permet de déterminer si l'unité du joueur est dans la zone alliée ou ennemie...

void move_player(TplateauJeu jeu, TListePlayer* player, int nbPlayer); //detecte si l'unité peut avancer ou non

//fonctions Phase création d'unités avec elixir au cous du jeu...


Tunite* AcheteUnite(int *elixirEnStockduJoueur, TplateauJeu jeu, int nbPlayer);

void elixir_increase(int *elix); //cette fonction permet d'incrémenter le nombre d'elixir de 1 à chaque fois qu'elle est appelée

void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);//permet d'ajout une unité à une liste, sauf que c'est une fonction void, donc le paramètre player est donc un pointeur de pointeur

TListePlayer AjoutDebut(TListePlayer forme_p,Tunite *unite);//permet d'ajout une unité à une liste... et retourne la liste en question avec l'ajour de l'unité

//fonction remmettant à 0 la propriété peut_attquer des unités du joueur à la fin de chque tour

void can_attack(TListePlayer player);// permet aux unités d'attaquer à nouveau.....


//******************************SAUVEGARDE***************************************************

void load_sequential(char *file_name,TListePlayer *player_1,TListePlayer *player_2); //cette fonction permet de charger le fichier de sauvegarde séquentiel

void save_sequential(char *file_name,TListePlayer player_1,TListePlayer player_2); //cette fonction permet de sauvegarder une partie du programme sous un fichier séquentiel

void suppAllUnite(TListePlayer *new_p);//cette fonction supprime toutes les unités d'une liste TListePlayer...

int longueur_liste(TListePlayer player); // cette fonction retourne le nombre d'unités d'un joueur TListePlayer


void load_binary(char *file_name,TListePlayer *player_1,TListePlayer *player_2);//cette fonction permet de charger le fichier de sauvegarde binaire

void save_binary(char *file_name,TListePlayer player_1,TListePlayer player_2); //cette fonction permet de sauvegarder une partie du programme sous un fichier binaire


#endif // JEU2048_H_INCLUDED
