#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char plateau[60+1], nom[20];
char joueur = 'C', pos, adv = 'O', adv2 = 'O', debut, fin;
int vie, tour = 0, tourAdv, posJoueur, posFant1, posFant2, score, bonus;

void videGrille(void)
{
    for(int i = 0; i < 60; i++){
        plateau[i] = ' ';
    }
}

void afficheGrille()
{
    system("clear");
    printf("Votre score est de :%d\n",tour);
    printf("_____________\n");
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[0],plateau[1],plateau[2],plateau[3],plateau[4],plateau[5],plateau[6],plateau[7],plateau[8],plateau[9]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[10],plateau[11],plateau[12],plateau[13],plateau[14],plateau[15],plateau[16],plateau[17],plateau[18],plateau[19]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[20],plateau[21],plateau[22],plateau[23],plateau[24],plateau[25],plateau[26],plateau[27],plateau[28],plateau[29]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[30],plateau[31],plateau[32],plateau[33],plateau[34],plateau[35],plateau[36],plateau[37],plateau[38],plateau[39]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[40],plateau[41],plateau[42],plateau[43],plateau[44],plateau[45],plateau[46],plateau[47],plateau[48],plateau[49]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[50],plateau[51],plateau[52],plateau[53],plateau[54],plateau[55],plateau[56],plateau[57],plateau[58],plateau[59]);
    printf("_____________\n");
    printf("\n");

    fflush(stdout);

}

void mouvementJoueur()
{
    //on nettoie l'ancien pacman
    for(int i = 0; i < 60; i++){
        if(plateau[i] == 'C') {
            plateau[i] = ' ';
        }
    }
    //on place le nouveau
    plateau[posJoueur] = joueur;
}

void mouvementFantome1()
{
    //determiner la position du fantome
    srand( time( NULL ) );

    int aBouge = 0;

    while(aBouge == 0) {
        int randomAdv = rand() % 4;
        //va en haut
        if (randomAdv == 0 && posFant1 > 10) {
            plateau[posFant1 - 10] = adv;
            plateau[posFant1] = ' ';
            posFant1 = posFant1 - 10;
            aBouge++;
        //va à droite
        } else if (randomAdv == 1 && posFant1 %10 < 9) {
            plateau[posFant1 + 1] = adv;
            plateau[posFant1] = ' ';
            posFant1 = posFant1 + 1;
            aBouge++;
        //va en bas
        } else if (randomAdv == 2 && posFant1 < 50) {
            plateau[posFant1 + 10] = adv;
            plateau[posFant1] = ' ';
            posFant1 = posFant1 + 10;
            aBouge++;
        //va à gauche
        } else if (randomAdv == 3 && posFant1 %10 != 0) {
            plateau[posFant1 - 1] = adv;
            plateau[posFant1] = ' ';
            posFant1 = posFant1 - 1;
            aBouge++;
        }
    }

}

void mouvementFantome2()
{
    //determiner la position du fantome
    srand( time( NULL ) );

    int aBouge = 0;

    while(aBouge == 0) {
        int randomAdv = rand() % 4;
        //va en haut
        if (randomAdv == 0 && posFant2 > 10) {
            plateau[posFant2 - 10] = adv2;
            plateau[posFant2] = ' ';
            posFant2 = posFant2 - 10;
            aBouge++;
            //va à droite
        } else if (randomAdv == 1 && posFant2 %10 < 9) {
            plateau[posFant2 + 1] = adv2;
            plateau[posFant2] = ' ';
            posFant2 = posFant2 + 1;
            aBouge++;
            //va en bas
        } else if (randomAdv == 2 && posFant2 < 50) {
            plateau[posFant2 + 10] = adv2;
            plateau[posFant2] = ' ';
            posFant2 = posFant2 + 10;
            aBouge++;
            //va à gauche
        } else if (randomAdv == 3 && posFant2 %10 != 0) {
            plateau[posFant2 - 1] = adv2;
            plateau[posFant2] = ' ';
            posFant2 = posFant2 - 1;
            aBouge++;
        }
    }

}


void initialisationGrille(){
    printf("\nEntrez votre nom puis appuyez sur Entree pour commencer :\n");
    fgets(nom, 19, stdin);

    bonus=0;
    posJoueur=3;
    posFant1=20;
    posFant2=59;
    vie=1;

    //affichage de la grille de jeu
    videGrille();
    plateau[3] = joueur;
    plateau[20] = adv;
    plateau[59] = adv2;

    int etoile = 0;
    srand( time( NULL ) );
    while(etoile < 20){
        int randomValeur = rand() % 61;
        if(plateau[randomValeur] == ' '){
            plateau[randomValeur] = '*';
            etoile ++;
        }
    }

    afficheGrille();
}

int main (void)
{

    //sommaire avec description
    printf("                     88888b.  8888b.  .d8888b88888b.d88b.  8888b. 88888b.  \n");
    printf("                     888 \"88b    \"88bd88P\"   888 \"888 \"88b    \"88b888 \"88b \n");
    printf("                     888  888.d888888888     888  888  888.d888888888  888 \n");
    printf("                     888 d88P888  888Y88b.   888  888  888888  888888  888 \n");
    printf("                     88888P " "  Y888888 \"Y8888P888  888  888\"Y888888888  888 \n");
    printf("                     888                                                   \n");
    printf("                     888                                                   \n");
    printf("                     888 \n");

    printf("          Appuyer sur 'q' pour aller a gauche.\n");
    printf("                 -sur 'z' pour aller en haut.\n");
    printf("                 -sur 's' pour aller en bas.\n");
    printf("                 -sur 'd' pour aller a droite.\n\n");

    printf("Pacman      -> 'C'\n");
    printf("Fantome1    -> 'O'\n");
    printf("Fantome2    -> 'O'\n");

    printf("Votre but est de manger toutes les étoiles, bonne chance!\n");

    //debut de la boucle du jeu
    do
    {
        //initialisation premier tour
        if(tour==0){
            initialisationGrille();
        } else {
            afficheGrille();
        }

        mouvementFantome1();

        mouvementFantome2();

        printf("position du fant1 : %d \n", posFant1);
        printf("position du fant2 : %d \n", posFant2);

        //modification de la position du joueur
        printf("Entrez une direction : \n");
        fflush(stdout);
        pos = ' ';
        scanf(" %c", &pos);
        while (pos != 'z' && pos != 'q' && pos != 's' && pos != 'd') {
            printf("Veuillez entrer une direction valide \n");
            printf("Entrez une direction : \n");
            scanf(" %c", &pos);
        }

        if(posJoueur % 10 != 0){
            if(pos=='q') posJoueur--;
        }
        if(posJoueur % 10 != 9) {
            if (pos == 'd') posJoueur++;
        }
        if(posJoueur > 9) {
            if (pos == 'z') posJoueur = posJoueur-10;
        }
        if(posJoueur < 50) {
            if (pos == 's') posJoueur = posJoueur+10;
        }

        mouvementJoueur();

        //evaluation des points et de la mort eventuelle
        //Collisions();
        tour++;
    }
    while (vie==1);
    //fin de la boucle de jeu

    // determination du score avec presence ou non du bonus
    score=bonus+tour;

    // si non alors le joueur a perdu
    // system("CLS");
    if(bonus==0)	printf("\n\nLe Chasseur a ete plus ruse que vous, %s... Vous avez perdu.\n\n", nom);

    //si oui alors le joueur a gagne
    if(bonus==50)
    {
        // system("CLS");
        printf("\n\n%s a atteint l'objectif. Vous remportez la victoire.\nVous etes acclame par votre public !\n\n", nom);
        printf("%s, votre score est de : %d\n\n", (nom), score);
        system("PAUSE");
    }


    system("PAUSE");
    system("clear");
    return 0;
}
