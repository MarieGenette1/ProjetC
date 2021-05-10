#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char carre[60+1], nom[20];
char joueur = 'C', pos, adv = 'O', adv2 = 'O', debut, fin;
int vie, tour = 0, tourAdv, posJoueur, posFant1, posFant2, score, bonus;


void videGrille(void)
{
    for(int i = 0; i < 60; i++){
        carre[i] = ' ';
    }
}

void afficheGrille()
{
    system("clear");
    printf("Votre score est de :%d\n",tour);
    printf("_____________\n");
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", carre[0],carre[1],carre[2],carre[3],carre[4],carre[5],carre[6],carre[7],carre[8],carre[9]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", carre[10],carre[11],carre[12],carre[13],carre[14],carre[15],carre[16],carre[17],carre[18],carre[19]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", carre[20],carre[21],carre[22],carre[23],carre[24],carre[25],carre[26],carre[27],carre[28],carre[29]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", carre[30],carre[31],carre[32],carre[33],carre[34],carre[35],carre[36],carre[37],carre[38],carre[39]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", carre[40],carre[41],carre[42],carre[43],carre[44],carre[45],carre[46],carre[47],carre[48],carre[49]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", carre[50],carre[51],carre[52],carre[53],carre[54],carre[55],carre[56],carre[57],carre[58],carre[59]);
    printf("_____________\n");
    printf("\n");

    fflush(stdout);

}

void mouvementJoueur()
{
    //on nettoie l'ancien pacman
    for(int i = 0; i < 60; i++){
        if(carre[i] == 'C') {
            carre[i] = ' ';
        }
    }
    //on place le nouveau
    carre[posJoueur] = joueur;
}

void mouvementFantome1()
{
    //determiner la position du fantome
    srand( time( NULL ) );

    int aBouge = 0;

    while(!aBouge) {
        int randomAdv = rand() % 4;
        //va en haut
        if (randomAdv == 0 && posFant1 > 10) {
            carre[posFant1 - 10] = adv;
            carre[posFant1] = ' ';
            aBouge++;
        //va à droite
        } else if (randomAdv == 1 && posFant1 %10 < 9) {
            carre[posFant1 + 1] = adv;
            carre[posFant1] = ' ';
            aBouge++;
        //va en bas
        } else if (randomAdv == 2 && posFant1 < 50) {
            carre[posFant1 + 10] = adv;
            carre[posFant1] = ' ';
            aBouge++;
        //va à gauche
        } else if (randomAdv == 3 && posFant1 %10 != 0) {
            carre[posFant1 - 1] = adv;
            carre[posFant1] = ' ';
            aBouge++;
        }
    }

}

void mouvementFantome2()
{
    //determiner la position du fantome
    srand( time( NULL ) );

    int aBouge = 0;

    while(!aBouge) {
        int randomAdv = rand() % 4;
        //va en haut
        if (randomAdv == 0 && posFant1 > 10) {
            carre[posFant1 - 10] = adv;
            carre[posFant1] = ' ';
            aBouge++;
            //va à droite
        } else if (randomAdv == 1 && posFant1 %10 < 9) {
            carre[posFant1 + 1] = adv;
            carre[posFant1] = ' ';
            aBouge++;
            //va en bas
        } else if (randomAdv == 2 && posFant1 < 50) {
            carre[posFant1 + 10] = adv;
            carre[posFant1] = ' ';
            aBouge++;
            //va à gauche
        } else if (randomAdv == 3 && posFant1 %10 != 0) {
            carre[posFant1 - 1] = adv;
            carre[posFant1] = ' ';
            aBouge++;
        }
    }

}

/*void Collisions()
{
    tourAdv--;
    if(tourAdv==1&&carre[20]=='C')	vie--;
    if(tourAdv==2&&carre[19]=='C')	vie--;
    if(tourAdv==3&&carre[18]=='C')	vie--;
    if(tourAdv==4&&carre[17]=='C')	vie--;
    if(tourAdv==5&&carre[14]=='C')	vie--;
    if(tourAdv==6&&carre[10]=='C')	vie--;
    if(tourAdv==7&&carre[11]=='C')	vie--;
    if(tourAdv==8&&carre[7]=='C')		vie--;
    if(tourAdv==9&&carre[6]=='C')		vie--;
    if(tourAdv==10&&carre[3]=='C')	vie--;
    if(tourAdv==11&&carre[2]=='C')	vie--;
    if(tourAdv==12&&carre[1]=='C')	vie--;
    if(tourAdv==13&&carre[0]=='C')	vie--;
    if(tourAdv==14&&carre[1]=='C')	vie--;
    if(tourAdv==15&&carre[2]=='C')	vie--;
    if(tourAdv==16&&carre[3]=='C')	vie--;
    if(tourAdv==17&&carre[4]=='C')	vie--;
    if(tourAdv==18&&carre[5]=='C')	vie--;
    if(tourAdv==19&&carre[4]=='C')	vie--;
    if(tourAdv==20&&carre[3]=='C')	vie--;
    if(tourAdv==21&&carre[6]=='C')	vie--;
    if(tourAdv==22&&carre[7]=='C')	vie--;
    if(tourAdv==23&&carre[11]=='C')	vie--;
    if(tourAdv==24&&carre[12]=='C')	vie--;
    if(tourAdv==25&&carre[13]=='C')	vie--;
    if(tourAdv==26&&carre[12]=='C')	vie--;
    if(tourAdv==27&&carre[11]=='C')	vie--;
    if(tourAdv==28&&carre[10]=='C')	vie--;
    if(tourAdv==29&&carre[9]=='C')	vie--;
    if(tourAdv==30&&carre[8]=='C')	vie--;
    if(tourAdv==31&&carre[9]=='C')	vie--;
    if(tourAdv==32&&carre[10]=='C')	vie--;
    if(tourAdv==33&&carre[14]=='C')	vie--;
    if(tourAdv==34&&carre[17]=='C')	vie--;
    if(tourAdv==35&&carre[16]=='C')	vie--;
    if(tourAdv==36&&carre[15]=='C')	vie--;
    if(tourAdv==37&&carre[16]=='C')	vie--;
    if(tourAdv==38&&carre[17]=='C')	vie--;
    if(tourAdv==39&&carre[18]=='C')	vie--;
    if(tourAdv==40&&carre[19]=='C')	vie--;
    if(tourAdv==41&&carre[20]=='C')	vie--;
    if(tourAdv==42&&carre[19]=='C')	vie--;
    if(tourAdv==43&&carre[18]=='C')	vie--;
    if(tourAdv==44&&carre[17]=='C')	vie--;
    if(tourAdv==45&&carre[14]=='C')	vie--;
    if(tourAdv==46&&carre[10]=='C')	vie--;
    if(tourAdv==47&&carre[11]=='C')	vie--;
    if(tourAdv==48&&carre[7]=='C')	vie--;
    if(tourAdv==49&&carre[6]=='C')	vie--;
    if(tourAdv==50&&carre[3]=='C')	vie--;
    if(tourAdv==51&&carre[4]=='C')	vie--;
    if(tourAdv==52&&carre[5]=='C')	vie--;
    if(tourAdv==53&&carre[4]=='C')	vie--;
    if(tourAdv==54&&carre[3]=='C')	vie--;
    if(tourAdv==55&&carre[2]=='C')	vie--;
    if(tourAdv==56&&carre[1]=='C')	vie--;
    if(tourAdv==57&&carre[0]=='C')	vie--;
    if(tourAdv==58&&carre[1]=='C')	vie--;
    if(tourAdv==59&&carre[2]=='C')	vie--;
    if(tourAdv==60&&carre[3]=='C')	vie--;
    if(tourAdv==61&&carre[6]=='C')	vie--;
    if(tourAdv==62&&carre[7]=='C')	vie--;
    if(tourAdv==63&&carre[11]=='C')	vie--;
    if(tourAdv==64&&carre[10]=='C')	vie--;
    if(tourAdv==65&&carre[9]=='C')	vie--;
    if(tourAdv==66&&carre[8]=='C')	vie--;
    if(tourAdv==67&&carre[9]=='C')	vie--;
    if(tourAdv==68&&carre[10]=='C')	vie--;
    if(tourAdv==69&&carre[11]=='C')	vie--;
    if(tourAdv==70&&carre[12]=='C')	vie--;
    if(tourAdv==71&&carre[13]=='C')	vie--;
    if(tourAdv==72&&carre[12]=='C')	vie--;
    if(tourAdv==73&&carre[11]=='C')	vie--;
    if(tourAdv==74&&carre[10]=='C')	vie--;
    if(tourAdv==75&&carre[14]=='C')	vie--;
    if(tourAdv==76&&carre[17]=='C')	vie--;
    if(tourAdv==77&&carre[18]=='C')	vie--;
    if(tourAdv==78&&carre[19]=='C')	vie--;
    if(tourAdv==79&&carre[20]=='C')	vie--;
    if(tourAdv==80&&carre[19]=='C')	vie--;
    if(tourAdv==81&&carre[18]=='C')	vie--;
    if(tourAdv==82&&carre[17]=='C')	vie--;
    if(tourAdv==83&&carre[16]=='C')	vie--;
    if(tourAdv==84&&carre[15]=='C')	vie--;
    if(tourAdv==85&&carre[16]=='C')	vie--;
    if(tourAdv==86&&carre[17]=='C')	vie--;
    if(tourAdv==87&&carre[18]=='C')	vie--;
    if(tourAdv==88&&carre[19]=='C')	vie--;
    tourAdv++;
}*/

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
    carre[3] = joueur;
    carre[20] = adv;
    carre[59] = adv2;

    int etoile = 0;
    srand( time( NULL ) );
    while(etoile < 20){
        int randomValeur = rand() % 61;
        if(carre[randomValeur] == ' '){
            carre[randomValeur] = '*';
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
