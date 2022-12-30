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
    Tcible cibleAttaquable;	//indique la position des unit�s que l�on peut attaquer
    Tcible maposition;		//indique soit � air � soit � sol �, utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c�est petit plus c�est rapide
    int degats;
    int portee ;			//en m�tre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu
    int peutAttaquer;		//permet de g�rer le fait que chaque unit� attaque une
                            //seule fois par tour ;
                            //0 = a d�j� attaqu�, 1 = peut attaquer ce tour-ci
                            // � remettre � 1 au d�but de chaque tour
    int coutEnElixir;
} Tunite;

typedef struct T_cell{
    struct T_cell *suiv;//pointeur vers l'unit� suivante de l'unit� courante
    Tunite *pdata; //pointeur vers l'unit� courante
} *TListePlayer;


typedef Tunite* ** TplateauJeu; //Plateau de jeu � 2 dimensions dont les cases sont des pointeurs de type (Tunite *)


TplateauJeu AlloueTab2D(int largeur, int hauteur);
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

//Fonctions creation d'unit�s de combats......

Tunite *creeTour(int posx, int posy);

Tunite *creeTourRoi(int posx, int posy);

Tunite *creeArcher(int posx, int posy);

Tunite *creeGargouille(int posx, int posy);

Tunite *creeDragon(int posx, int posy);

Tunite *creeChevalier(int posx, int posy);


//fonctions Affichages


void Affiche_unite(TListePlayer player, int nbPlayer, int *elixir);/*affiche dans la console le d�roulement du jeu

avec pour chaque joueur, le nom et les pv de ses unit�s*/

//fonction tourDetruite

Bool tourRoiDetruite(TListePlayer player);

//fonction permettant de positionner les unit�s sur le plateau de jeu

void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu);

//fonctions Phase combat


TListePlayer quiEstAPortee(TListePlayer player, Tunite *uneUniteDeLautreJoueur); /*cette fonction retourne la liste des unit�s du player capable

d'aataquer une unit� de l'autre joueur*/

void combat(TListePlayer player, TListePlayer new_player); /*cette fonction s'occupe de la phase combat entre les unit�s de chaque joueur */

TListePlayer SupprimerValuePvZero(TListePlayer player_2); //cette fonction appelle la fonction supp_unite apr�s avoir trouver une unit� du player_2 avec un pv <=0

void supp_unite(TListePlayer *new_p,Tunite *value); //cette fonction supprime l'unit� value de la liste des unit�s du joueur new_p


//fonctions Phase d�placement


Bool positionAvailable(int xpos, int ypos,TplateauJeu jeu); //cette fonction permet de savoir si la position [xpos][ypos] sur le plateau de jeu est NULL ou non

int zone(Tunite* unite);//cette fonction permet de d�terminer si l'unit� du joueur est dans la zone alli�e ou ennemie...

void move_player(TplateauJeu jeu, TListePlayer* player, int nbPlayer); //detecte si l'unit� peut avancer ou non

//fonctions Phase cr�ation d'unit�s avec elixir au cous du jeu...


Tunite* AcheteUnite(int *elixirEnStockduJoueur, TplateauJeu jeu, int nbPlayer);

void elixir_increase(int *elix); //cette fonction permet d'incr�menter le nombre d'elixir de 1 � chaque fois qu'elle est appel�e

void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);//permet d'ajout une unit� � une liste, sauf que c'est une fonction void, donc le param�tre player est donc un pointeur de pointeur

TListePlayer AjoutDebut(TListePlayer forme_p,Tunite *unite);//permet d'ajout une unit� � une liste... et retourne la liste en question avec l'ajour de l'unit�

//fonction remmettant � 0 la propri�t� peut_attquer des unit�s du joueur � la fin de chque tour

void can_attack(TListePlayer player);// permet aux unit�s d'attaquer � nouveau.....


//******************************SAUVEGARDE***************************************************

void load_sequential(char *file_name,TListePlayer *player_1,TListePlayer *player_2); //cette fonction permet de charger le fichier de sauvegarde s�quentiel

void save_sequential(char *file_name,TListePlayer player_1,TListePlayer player_2); //cette fonction permet de sauvegarder une partie du programme sous un fichier s�quentiel

void suppAllUnite(TListePlayer *new_p);//cette fonction supprime toutes les unit�s d'une liste TListePlayer...

int longueur_liste(TListePlayer player); // cette fonction retourne le nombre d'unit�s d'un joueur TListePlayer


void load_binary(char *file_name,TListePlayer *player_1,TListePlayer *player_2);//cette fonction permet de charger le fichier de sauvegarde binaire

void save_binary(char *file_name,TListePlayer player_1,TListePlayer player_2); //cette fonction permet de sauvegarder une partie du programme sous un fichier binaire


#endif // JEU2048_H_INCLUDED
