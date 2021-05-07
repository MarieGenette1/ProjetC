#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char plateau[60+1], nom[20];
char joueur = 'C', pos, adv = 'O', adv2 = 'O', debut, fin;
int vie, tour = 0, tourAdv, x, y, score, bonus, a, b;

void clear(void)
{
    for(int i = 0; i < 60; i++){
        plateau[i] = ' ';
    }
}

void clearC(void)
{
    for(int i = 0; i < 60; i++){
        if(plateau[i] == 'C') {
            plateau[i] = ' ';
        }
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

void updatePlayer()
{
    plateau[y*10+x] = 'C';
}

void AdvPos()
{
    //determiner la position du fantome
    srand( time( NULL ) );
    int randomAdv = rand() % 4;

    if(randomAdv == 0 && a >= 10){
        plateau[a-10] = adv;
        plateau[a] = ' ';
    }else if(randomAdv == 1 && a % 10 != 9){
        plateau[a+1] = adv;
        plateau[a] = ' ';
    }else if(randomAdv == 2 && a <= 50 ){
        plateau[a+10] = adv;
        plateau[a] = ' ';
    }else if(randomAdv == 3 && a % 10 != 0){
        plateau[a-1] = adv;
        plateau[a] = ' ';
    }else{
    }

}

/*void Collisions()
{
    tourAdv--;
    if(tourAdv==1&&plateau[20]=='C')	vie--;
    if(tourAdv==2&&plateau[19]=='C')	vie--;
    if(tourAdv==3&&plateau[18]=='C')	vie--;
    if(tourAdv==4&&plateau[17]=='C')	vie--;
    if(tourAdv==5&&plateau[14]=='C')	vie--;
    if(tourAdv==6&&plateau[10]=='C')	vie--;
    if(tourAdv==7&&plateau[11]=='C')	vie--;
    if(tourAdv==8&&plateau[7]=='C')		vie--;
    if(tourAdv==9&&plateau[6]=='C')		vie--;
    if(tourAdv==10&&plateau[3]=='C')	vie--;
    if(tourAdv==11&&plateau[2]=='C')	vie--;
    if(tourAdv==12&&plateau[1]=='C')	vie--;
    if(tourAdv==13&&plateau[0]=='C')	vie--;
    if(tourAdv==14&&plateau[1]=='C')	vie--;
    if(tourAdv==15&&plateau[2]=='C')	vie--;
    if(tourAdv==16&&plateau[3]=='C')	vie--;
    if(tourAdv==17&&plateau[4]=='C')	vie--;
    if(tourAdv==18&&plateau[5]=='C')	vie--;
    if(tourAdv==19&&plateau[4]=='C')	vie--;
    if(tourAdv==20&&plateau[3]=='C')	vie--;
    if(tourAdv==21&&plateau[6]=='C')	vie--;
    if(tourAdv==22&&plateau[7]=='C')	vie--;
    if(tourAdv==23&&plateau[11]=='C')	vie--;
    if(tourAdv==24&&plateau[12]=='C')	vie--;
    if(tourAdv==25&&plateau[13]=='C')	vie--;
    if(tourAdv==26&&plateau[12]=='C')	vie--;
    if(tourAdv==27&&plateau[11]=='C')	vie--;
    if(tourAdv==28&&plateau[10]=='C')	vie--;
    if(tourAdv==29&&plateau[9]=='C')	vie--;
    if(tourAdv==30&&plateau[8]=='C')	vie--;
    if(tourAdv==31&&plateau[9]=='C')	vie--;
    if(tourAdv==32&&plateau[10]=='C')	vie--;
    if(tourAdv==33&&plateau[14]=='C')	vie--;
    if(tourAdv==34&&plateau[17]=='C')	vie--;
    if(tourAdv==35&&plateau[16]=='C')	vie--;
    if(tourAdv==36&&plateau[15]=='C')	vie--;
    if(tourAdv==37&&plateau[16]=='C')	vie--;
    if(tourAdv==38&&plateau[17]=='C')	vie--;
    if(tourAdv==39&&plateau[18]=='C')	vie--;
    if(tourAdv==40&&plateau[19]=='C')	vie--;
    if(tourAdv==41&&plateau[20]=='C')	vie--;
    if(tourAdv==42&&plateau[19]=='C')	vie--;
    if(tourAdv==43&&plateau[18]=='C')	vie--;
    if(tourAdv==44&&plateau[17]=='C')	vie--;
    if(tourAdv==45&&plateau[14]=='C')	vie--;
    if(tourAdv==46&&plateau[10]=='C')	vie--;
    if(tourAdv==47&&plateau[11]=='C')	vie--;
    if(tourAdv==48&&plateau[7]=='C')	vie--;
    if(tourAdv==49&&plateau[6]=='C')	vie--;
    if(tourAdv==50&&plateau[3]=='C')	vie--;
    if(tourAdv==51&&plateau[4]=='C')	vie--;
    if(tourAdv==52&&plateau[5]=='C')	vie--;
    if(tourAdv==53&&plateau[4]=='C')	vie--;
    if(tourAdv==54&&plateau[3]=='C')	vie--;
    if(tourAdv==55&&plateau[2]=='C')	vie--;
    if(tourAdv==56&&plateau[1]=='C')	vie--;
    if(tourAdv==57&&plateau[0]=='C')	vie--;
    if(tourAdv==58&&plateau[1]=='C')	vie--;
    if(tourAdv==59&&plateau[2]=='C')	vie--;
    if(tourAdv==60&&plateau[3]=='C')	vie--;
    if(tourAdv==61&&plateau[6]=='C')	vie--;
    if(tourAdv==62&&plateau[7]=='C')	vie--;
    if(tourAdv==63&&plateau[11]=='C')	vie--;
    if(tourAdv==64&&plateau[10]=='C')	vie--;
    if(tourAdv==65&&plateau[9]=='C')	vie--;
    if(tourAdv==66&&plateau[8]=='C')	vie--;
    if(tourAdv==67&&plateau[9]=='C')	vie--;
    if(tourAdv==68&&plateau[10]=='C')	vie--;
    if(tourAdv==69&&plateau[11]=='C')	vie--;
    if(tourAdv==70&&plateau[12]=='C')	vie--;
    if(tourAdv==71&&plateau[13]=='C')	vie--;
    if(tourAdv==72&&plateau[12]=='C')	vie--;
    if(tourAdv==73&&plateau[11]=='C')	vie--;
    if(tourAdv==74&&plateau[10]=='C')	vie--;
    if(tourAdv==75&&plateau[14]=='C')	vie--;
    if(tourAdv==76&&plateau[17]=='C')	vie--;
    if(tourAdv==77&&plateau[18]=='C')	vie--;
    if(tourAdv==78&&plateau[19]=='C')	vie--;
    if(tourAdv==79&&plateau[20]=='C')	vie--;
    if(tourAdv==80&&plateau[19]=='C')	vie--;
    if(tourAdv==81&&plateau[18]=='C')	vie--;
    if(tourAdv==82&&plateau[17]=='C')	vie--;
    if(tourAdv==83&&plateau[16]=='C')	vie--;
    if(tourAdv==84&&plateau[15]=='C')	vie--;
    if(tourAdv==85&&plateau[16]=='C')	vie--;
    if(tourAdv==86&&plateau[17]=='C')	vie--;
    if(tourAdv==87&&plateau[18]=='C')	vie--;
    if(tourAdv==88&&plateau[19]=='C')	vie--;
    tourAdv++;
}*/

void initialisationGrille(){
    printf("\nEntrez votre nom puis appuyez sur Entree pour commencer :\n");
    fgets(nom, 19, stdin);

    bonus=0;
    x=3; y=0;
    a=20;
    vie=1;

    //affichage de la grille de jeu
    clear();
    plateau[3] = joueur;
    plateau[20] = adv;
    plateau[59] = adv2;

    int etoiles = 0;
    srand( time( NULL ) );
    while(etoiles < 20){
        int randomValue = rand() % 61;
        if(plateau[randomValue] == ' '){
            plateau[randomValue] = '*';
            etoiles ++;
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

    printf("Fantome1    -> 'O'\n");
    printf("Fantome2    -> 'O'\n");
    printf("Pacman      -> 'C'\n");

    printf("Votre but est de manger toutes les étoiles, bonne chance!\n");

    //debut de la boucle du jeu
    do
    {
        //si c est le premier tour alors les positions sont les suivantes
        if(tour==0)
        {
            initialisationGrille();
        } else {
            afficheGrille();
        }

        //determiner la boucle du tour des fantomes
        AdvPos();

        clearC();

        //modification de x et de y en fonction de la lettre saisi par le joueur
        printf("Entrez une direction : ");
        scanf("%c", &pos);
        do {
            printf("Veuillez entrer une direction valide \n");
            printf("Entrez une direction : ");
            scanf("%c", &pos);
        } while (pos != 'z' && pos != 'q' && pos != 's' && pos != 'd');

        if(x != 0){
            if(pos=='q') x--;
        }
        if(x != 9) {
            if (pos == 'd') x++;
        }
        if(y != 0) {
            if (pos == 'z') y--;
        }
        if(y != 5) {
            if (pos == 's') y++;
        }


        //place et eventuellement mort de LukeS pour chaque configuration de x et de y
        updatePlayer();

        //evaluation de la mort ou non de LukeS si la case est deja occupee par DarkV
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
