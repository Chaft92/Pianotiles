#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//SOURCES UTILISES
//pour avoir une idee de deplacement et la fonction getch
//http://fvirtman.free.fr/recueil/04_02_05_minilaby.c.php



typedef struct joueur{
    int positionX;
    int positionY;
    char perso;
    char cartestresor[12];
    int carte_en_cours;
    int fin;

}Joueur;


int nmb_players;
int actuplayer=0;
Joueur tab_joueurs[4];

typedef struct tile{
    int shape;
    char tresor;
    int pion;

}tuile;

char cartes_tresor[24]={'@','&','#','*','^','$','!','?','=','+','~','%','v','-','<','>','0','1','9','3','8','5','6','7'};
tuile plateau [7][7];

///définition de la structure du plateau
typedef struct{

    int shape[3][3];

}tuiles;

tuiles tuiles_plus; //la tuile restante

///sous-programme qui permet d'avoir un nombre aléatoire entre un minimum et un maximum qui sera utile tout au long du code
int alea(int min, int max){

    int result;
    srand(time(NULL));
    result=rand()%(max - min) + min;

    return result;
}


int randomcards()
{
    for (int i=0; i<nmb_players; i++)
    {
        int nb_cartes = 24/nmb_players;
        for (int j=0; j<nb_cartes; j++)
        {
            if (cartes_tresor[alea(0,24)] != ' ')
            {
                tab_joueurs[i].cartestresor[j] = cartes_tresor[alea(0,24)];
                cartes_tresor[alea(0,24)] = ' ';
            }
        }
    }
    return 0;
}
///placement des tuiles fixes
int plateau1(){
    srand(time(NULL));
    tuiles tab[10];

    tuiles map[7][7];

    ///les tuiles aux 4 coins
    tuiles lbasgauche={
            0xDB,' ',0xDB,0xDB,'0',' ',0xDB,0xDB,0xDB
    };
    tuiles lhautgauche={
            0xDB,0xDB,0xDB,0xDB,'0',' ',0xDB,' ',0xDB
    };
    tuiles lhautroite={
            0xDB,0xDB,0xDB,' ','0',0xDB,0xDB,' ',0xDB
    };
    tuiles lbasdroite={
            0xDB,' ',0xDB,' ','0', 0xDB, 0xDB,0xDB, 0xDB
    };

    ///les tuiles entre chaque coins
    tuiles midhaut={
            0xDB,0xDB,0xDB,' ','0',' ',0xDB,' ',0xDB
    };
    tuiles midgauche={
            0xDB,' ',0xDB,0xDB,'0',' ',0xDB,' ',0xDB,
    };
    tuiles middroite={
            0xDB,' ',0xDB,' ','0',0xDB,0xDB,' ',0xDB,
    };
    tuiles midbas={
            0xDB,' ',0xDB,' ','0',' ',0xDB,0xDB,0xDB
    };
    ///utilisation des tuiles au dessus pour celles fixes au milieu du plateau

    ///formes des tuiles et insertion dans le tableau des tuiles non fixes
    tuiles thaut={
            0xDB,0xDB,0xDB,' ',' ',' ',0xDB,' ',0xDB
    };
    tab[0]=thaut;

    tuiles tbas={
            0xDB,' ',0xDB,' ',' ',' ',0xDB,0xDB,0xDB
    };
    tab[1]=tbas;

    tuiles tdroite={
            0xDB,' ',0xDB,0xDB,' ',' ',0xDB,' ',0xDB,
    };
    tab[2]=tdroite;

    tuiles tgauche={
            0xDB,' ',0xDB,' ',' ',0xDB,0xDB,' ',0xDB,
    };
    tab[3]=tgauche;

    tuiles lbas={
            0xDB,0xDB,0xDB,0xD  ,' ',' ',0xDB,' ',0xDB
    };
    tab[4]=lbas;

    tuiles lhaut={
            0xDB,' ',0xDB,0xDB,' ',' ',0xDB,0xDB,0xDB
    };
    tab[5]=lhaut;

    tuiles ldroite={
            0xDB,0xDB,0xDB,' ',' ',0xDB,0xDB,' ',0xDB
    };
    tab[6]=ldroite;

    tuiles lgauche={
            0xDB,' ',0xDB,' ',' ', 0xDB, 0xDB,0xDB, 0xDB
    };
    tab[7]=lgauche;

    tuiles ivertical={
            0xDB,' ',0xDB,0xDB,' ',0xDB,0xDB,' ',0xDB
    };
    tab[8]=ivertical;

    tuiles ihorizontal={
            0xDB,0xDB,0xDB,' ',' ',' ',0xDB,0xDB,0xDB
    };
    tab[9]=ihorizontal;


    int a,b,c,d;
    for(a=0;a<7;a++){

        for(b=0;b<3;b++){

            for(c=0;c<7;c++){

                for(d=0;d<3;d++){
                    map[c][a].shape[b][d]=0xDB;

                    ///tuiles fixes
                    map[0][0]=lhautgauche;
                    map[0][6]=lbasgauche;
                    map[6][0]=lhautroite;
                    map[6][6]=lbasdroite;
                    map[2][0]=midhaut;
                    map[4][0]=midhaut;
                    map[0][2]=midgauche;
                    map[0][4]=midgauche;
                    map[6][2]=middroite;
                    map[6][4]=middroite;
                    map[2][6]=midbas;
                    map[4][6]=midbas;
                    map[2][2]=middroite;
                    map[4][2]=midhaut;
                    map[2][4]=midbas;
                    map[4][4]=middroite;

                    ///tuiles non fixes
                    map[1][0]=tab[alea(0,9)];
                    map[3][0]=tab[alea(0,9)];
                    map[5][0]=tab[alea(0,9)];
                    map[0][1]=tab[alea(0,9)];
                    map[1][1]=tab[alea(0,9)];
                    map[2][1]=tab[alea(0,9)];
                    map[3][1]=tab[alea(0,9)];
                    map[4][1]=tab[alea(0,9)];
                    map[5][1]=tab[alea(0,9)];
                    map[6][1]=tab[alea(0,9)];
                    map[1][2]=tab[alea(0,9)];
                    map[3][2]=tab[alea(0,9)];
                    map[5][2]=tab[alea(0,9)];
                    map[0][3]=tab[alea(0,9)];
                    map[1][3]=tab[alea(0,9)];
                    map[2][3]=tab[alea(0,9)];
                    map[3][3]=tab[alea(0,9)];
                    map[4][3]=tab[alea(0,9)];
                    map[5][3]=tab[alea(0,9)];
                    map[6][3]=tab[alea(0,9)];
                    map[1][4]=tab[alea(0,9)];
                    map[3][4]=tab[alea(0,9)];
                    map[5][4]=tab[alea(0,9)];
                    map[0][5]=tab[alea(0,9)];
                    map[1][5]=tab[alea(0,9)];
                    map[2][5]=tab[alea(0,9)];
                    map[3][5]=tab[alea(0,9)];
                    map[4][5]=tab[alea(0,9)];
                    map[5][5]=tab[alea(0,9)];
                    map[6][5]=tab[alea(0,9)];
                    map[1][6]=tab[alea(0,9)];
                    map[3][6]=tab[alea(0,9)];
                    map[5][6]=tab[alea(0,9)];

                    printf("%c ",map[c][a].shape[b][d]);
                }
            }
            printf("\n");
        }
    }
    return 0;
}


void verificationMouvement(int* x,int* y,int vx,int vy) {

int plateau [7][7];
    if (plateau[ *x + vx] [ *y + vy] == 0xDB)  {
        return;
    }
    (*x)+=vx;
    (*y)+=vy;
}


int MyGetch()
{
#ifdef _WIN32
    return getch();
#endif

}


int cartes_tresorsdujoueur_atrouver(int joueur)
{
    int nb_cartes = 24/nmb_players;//on divise le nombre de cartes tresor au total par le nombre de joueurs

    for (int j = 0; j < nb_cartes; j++)
    {
        printf("%c,",tab_joueurs[joueur].cartestresor[j]);
    }
    printf("\nVous devez trouver ce tresor :%c\n",tab_joueurs[joueur].cartestresor[tab_joueurs[joueur].carte_en_cours]);

    return 0;
}
/*
int decaler_tuile_droite(int indice)
{
    tuile tuile_sortie;

    tuile_sortie = plateau[indice][6];

    for (int i=6; i>0; i--)
    {
        plateau[indice][i] = plateau[indice][i - 1];
    }
    plateau[indice][0] = tuile_enplus;
    tuile_enplus = tuile_sortie;

    return 0;
}

int decaler_tuile_gauche(int indice)
{
    tuile tuile_sortie;
    tuile_sortie = plateau[indice][0];

    for (int i=0; i<6; i++)
    {
        plateau[indice][i] = plateau[indice][i + 1];
    }
    plateau[indice][6] = tuile_enplus;
    tuile_enplus = tuile_sortie;

    return 0;
}

int decaler_tuile_haut(int indice)
{
    tuile tuile_sortie;

    tuile_sortie = plateau[6][indice];

    for (int j=6; j>0; j--)
    {
        plateau[j][indice] = plateau[j - 1][indice];
    }
    plateau[0][indice]= tuile_enplus;
    tuile_enplus = tuile_sortie;

    return 0;
}

int decaler_tuile_bas(int indice)
{
    tuile tuile_sortie;

    tuile_sortie =plateau[indice][0];

    for (int j=0; j<6; j++)
    {
        plateau[j][indice] = plateau[j + 1][indice];
    }
    plateau[6][indice]=tuile_enplus;
    tuile_enplus = tuile_sortie;

    return 0;
}
*/
int main() {
    srand(time(NULL));
    int rep,rep1;
    int touche;
    int nmb_players;
    int actuplayer=0;
    char cartes[24];
    tuile plateau [7][7];

    printf("Bienvenue au jeu du LABYRINTHE! %c\n",0x0F);
    printf("\n");

    printf("**               **        *******    **    **  *********   ********   ***     **  ********** ***    ***  *********\n");
    printf("**              *  *       **     *     *   *   **      *     ***      ** *    **     ***     ***    ***  *********\n");
    printf("**             *    *      **     *      **     **      *     ***      **  *   **     ***     ***    ***  **\n");
    printf("**            ********     *******       **     *********     ***      **   *  **     ***     **********  *********\n");
    printf("**           **********    ***** *       **     **            ***      **    * **     ***     ***    ***  **\n");
    printf("*********   *          *   **     *      **     *   **        ***      **     ***     ***     ***    ***  *********\n");
    printf("*********  *            *  ** ****       **     *     **    ********   **      **     ***     ***    ***  *********\n");
    //printf("|------------------------------------------------------------------------------|\n");
	//printf("|_______________________________|*************|________________________________|\n");
	//printf("|_______________________________|  LABYRINTHE |________________________________|\n");
	//printf("|_______________________________|*************|________________________________|\n");
    //printf("|------------------------------------------------------------------------------|\n");

    printf("\n");
    printf("1-Demarer une nouvelle partie!\n");
    printf("2-Afficher les REGLE du jeu\n");
    printf("3-Quitter le jeu\n");
    scanf("%d",&rep1);

    switch(rep1){

        case 1:

            //initialisation du plateau

            printf("Combien d'aventuriers participent a la partie?(entre 2 et 4 inclus)\n");
            scanf("%d",&nmb_players);
            if(nmb_players<2 || nmb_players>4){
                printf("Vous etes pas assez ou trop d'aventuriers a vouloir participer!");
                printf("Choisssisez un autre nombre d'aventuriers!\n");
                scanf("%d",&nmb_players);
            }
            for (int i = 0; i < nmb_players; ++i) {
                printf("Selectionnez un personnage de jeu!\n");
                printf("Le jongleur %c (notez J)\n",0x01);
                printf("Le brave %c(notez B)\n",0x02);
                printf("Le chanceux %c (notez V)\n",0x05);
                printf("Le rayonnant %c(notez R)\n",0x0F);
                printf("Ne choississez pas le meme personnage!:\n");
                scanf("%s",&tab_joueurs[i].perso);
            }

            for (int i = 0; i < nmb_players; i++)
            {
                switch (tab_joueurs[i].perso)
                {
                    case 0x01 :
                        tab_joueurs[i].positionX = 0;
                        tab_joueurs[i].positionY = 0;
                        plateau[0][0].pion = 1;
                        break;

                    case 0x0D:
                        tab_joueurs[i].positionX = 0;
                        tab_joueurs[i].positionY = 6;
                        plateau[0][6].pion = 2;
                        break;

                    case 0x02:
                        tab_joueurs[i].positionX = 6;
                        tab_joueurs[i].positionY = 0;
                        plateau[6][0].pion = 3;
                        break;

                    case 0x0F:
                        tab_joueurs[i].positionX = 6;
                        tab_joueurs[i].positionY = 6;
                        plateau[6][6].pion = 4;
                        break;

                }
            }
            randomcards();
            plateau1();
            break;
        case 2:
            printf("REGLES DU JEU\n");
            printf("Chaque joueur regarde secrètement la carte supérieure de sa pile. Le plus jeune joueur commence. La partie se poursuit dans le sens des aiguilles d’une montre.");
            printf("À son tour de jeu, le joueur doit essayer d’atteindre la plaque représentant le même dessin que celui sur la carte supérieure de sa pile.");
            printf("Pour cela il commence toujours par faire coulisser une rangée ou une colonne du labyrinthe en insérant la plaque supplémentaire du bord vers l’intérieur du plateau, puis il déplace son pion.");
            printf("12 flèches sont dessinées en bordure de plateau. Elles indiquent les rangées et colonnes où peut être insérée la plaque supplémentaire pour modifier les couloirs du labyrinthe.");
            printf("Quand vient son tour, le joueur choisit l’une de ces rangées ou colonnes et pousse la plaque supplémentaire vers l’intérieur du plateau jusqu’à ce qu’une nouvelle plaque soit expulsée à l’opposé. ");
            printf("La plaque expulsée reste au bord du plateau jusqu’à ce qu’elle soit réintroduite à un autre endroit par le joueur suivant.");
            printf("Ce dernier n’a cependant pas le droit de réintroduire la plaque Couloir à l’endroit d’où elle vient d’être expulsée");
            printf("la partie s arrete quand un joueur atteint tout ses objectifs");
            break;

        case 3:
            return 0;
            break;
        default: return 0;
    }


    do {
        printf("C'est votre tour !\n");
        printf("Inserez la tuile manquante:\n");
        //code pour la tuile manquante


        printf("Voulez vous:\n");
        printf("1-Se deplacer?\n");
        printf("2-Passer au joueur suivant?\n");
        printf("3-afficher les regles\n");
        printf("4-Quitter le jeu\n");

        scanf("%d", rep);


        switch (rep) {
            case 1:

                touche = 0;
                while (touche != 27) // ECHAP
                {
                    touche = MyGetch();
                    switch (touche) {
                        case 'q':
                            //verificationMouvement(tab_joueurs[actuplayer].positionX, tab_joueurs[actuplayer].positionY,0, -1);

                            break;
                        case 'd':
                            //verificationMouvement(tab_joueurs[actuplayer].positionX, tab_joueurs[actuplayer].positionY,0, 1);

                            break;
                        case 'z':
                            //verificationMouvement(tab_joueurs[actuplayer].positionX, tab_joueurs[actuplayer].positionY,-1, 0);

                            break;
                        case 's':
                            //verificationMouvement(tab_joueurs[actuplayer].positionX, tab_joueurs[actuplayer].positionY,1, 0);


                        default:
                            break;
                    }
                }
            case 2:
                  printf("REGLES DU JEU\n");
                  printf("Chaque joueur regarde secrètement la carte supérieure de sa pile. Le plus jeune joueur commence. La partie se poursuit dans le sens des aiguilles d’une montre.");
                  printf("À son tour de jeu, le joueur doit essayer d’atteindre la plaque représentant le même dessin que celui sur la carte supérieure de sa pile.");
                  printf("Pour cela il commence toujours par faire coulisser une rangée ou une colonne du labyrinthe en insérant la plaque supplémentaire du bord vers l’intérieur du plateau, puis il déplace son pion.");
                  printf("12 flèches sont dessinées en bordure de plateau. Elles indiquent les rangées et colonnes où peut être insérée la plaque supplémentaire pour modifier les couloirs du labyrinthe.");
                  printf("Quand vient son tour, le joueur choisit l’une de ces rangées ou colonnes et pousse la plaque supplémentaire vers l’intérieur du plateau jusqu’à ce qu’une nouvelle plaque soit expulsée à l’opposé. ");
                  printf("La plaque expulsée reste au bord du plateau jusqu’à ce qu’elle soit réintroduite à un autre endroit par le joueur suivant.");
                  printf("Ce dernier n’a cependant pas le droit de réintroduire la plaque Couloir à l’endroit d’où elle vient d’être expulsée");
                  printf("la partie s arrete quand un joueur atteint tout ses objectifs");
            break;



            case 4:
                actuplayer = actuplayer + 1;
                if (actuplayer == nmb_players)actuplayer = 0;
        }

        //analyse des cartes tresor
        if (plateau[tab_joueurs[actuplayer].positionX, tab_joueurs[actuplayer].positionY]->tresor ==tab_joueurs[actuplayer].cartestresor[tab_joueurs[actuplayer].carte_en_cours]) {
            plateau[tab_joueurs[actuplayer].positionX, tab_joueurs[actuplayer].positionY]->tresor = ' ';//efface le tresor
            if (tab_joueurs[actuplayer].carte_en_cours == (24 / nmb_players - 1)) {
                tab_joueurs[actuplayer].fin = true;
            } else
                tab_joueurs[actuplayer].carte_en_cours++;
        }

        ///fonction victoire
        if (tab_joueurs[actuplayer].fin == true) {
            switch (tab_joueurs[actuplayer].perso) {
                case 0x01:
                    if (tab_joueurs[actuplayer].positionX == 0 || tab_joueurs[actuplayer].positionY == 0) {
                        printf("Vous avez gagné!!!\n");
                        return 0;
                    }
                    break;
                case 0x0D:
                    if (tab_joueurs[actuplayer].positionX == 0 || tab_joueurs[actuplayer].positionY == 6) {
                        printf("Vous avez gagné!!\n");
                        return 0;
                    }
                    break;
                case 0x02:
                    if (tab_joueurs[actuplayer].positionX == 6 || tab_joueurs[actuplayer].positionY == 0) {
                        printf("Vous avez gagné!!\n");
                        return 0;
                    }
                    break;
                case 0x0F:
                    if (tab_joueurs[actuplayer].positionX == 6 || tab_joueurs[actuplayer].positionY == 6) {
                        printf("Vous avez gagné!!\n");
                        return 0;
                    }
                    break;
            }

        }while (rep==2 || rep==1);


        printf("Tuile restante:\n");
        //affichertuile(tuile_restante);

    }while(rep==3);

    return 0;
}
