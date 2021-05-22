# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <arpa/inet.h>
#include <time.h>
#include <sys/wait.h>

#define PORT 6000
#define MAX_BUFFER 100
#define EXIT "exit"
#define MAX_CLIENTS 3

char plateau[60+1], nom[20];
char joueur = 'C', pos, adv = 'O', adv2 = 'O', debut, fin;
int vie=1, tour = 0, posJoueur, posFant1, posFant2, score, bonus, adv1e = '0', adv2e = '0', nbetoiles, nbClients = 0;

int testQuitter(char tampon[]) {
    return strcmp(tampon, EXIT) == 0;
}

void videGrille(void) {
    for (int i = 0; i < 60; i++) {
        plateau[i] = ' ';
    }
}

void initialisationGrille() {

    bonus = 0;
    posJoueur = 3;
    posFant1 = 20;
    posFant2 = 59;

    //affichage de la grille de jeu
    videGrille();
    plateau[3] = joueur;
    plateau[20] = adv;
    plateau[59] = adv2;

    int etoile = 0;
    srand(time(NULL));
    while (etoile < 20) {
        int randomValeur = rand() % 61;
        if (plateau[randomValeur] == ' ') {
            plateau[randomValeur] = '*';
            etoile++;
        }
    }
}

void mouvementJoueur(int posJoueur) {

    //on nettoie l'ancien pacman

    for (int i = 0; i < 60; i++) {
        if (plateau[i] == joueur) {
            plateau[i] = ' ';
        }
    }

    //on place le nouveau
    if (posJoueur == posFant1 || posJoueur == posFant2) {
        vie--;
        printf("vie--\n");
        fflush(stdout);
    } else if (plateau[posJoueur] == ' ') {
        plateau[posJoueur] = joueur;
    } else if (plateau[posJoueur] == '*') {
        plateau[posJoueur] = joueur;
        score = score + 100;
        nbetoiles = nbetoiles - 1;
        if (nbetoiles == 0) {
            bonus = bonus + 50;
            vie--;
        }
    }
}

void updatePosFantome1(int deplacement) {
    plateau[posFant1] = plateau[posFant1 + deplacement] == ' ' ? adv : adv1e;
    posFant1 = posFant1 + deplacement;

}

void updatePosFantome2(int deplacement) {
    plateau[posFant2] = plateau[posFant2 + deplacement] == ' ' ? adv2 : adv2e;
    posFant2 = posFant2 + deplacement;
}

void mouvementFantome1(int posFant1) {
    //determiner la position du fantome
    srand(time(NULL));

    int aBouge = 0;

    while (aBouge == 0) {
        int randomAdv1 = rand() % 4;

        //on nettoie l'ancien fantome 1

        if (plateau[posFant1] == adv) {
            plateau[posFant1] = ' ';
        } else if (plateau[posFant1] == adv1e) {
            plateau[posFant1] = '*';
        }

        switch (randomAdv1) {
            case 0: // go up
                if (posFant1 < 10 || posFant1 - 10 == posFant2) { // cas d'erreur
                    break;
                }
                updatePosFantome1(10);
                aBouge++;
                printf("abouge\n");
                fflush(stdout);
                break;
            case 1: //go right
                if (posFant1 % 10 == 9 || posFant1 + 1 == posFant2) {
                    break;
                }
                updatePosFantome1(1);
                aBouge++;
                printf("abouge\n");
                fflush(stdout);
                break;
            case 2: //go down
                if (posFant1 >= 50 || posFant1 + 10 == posFant2) {
                    break;
                }
                updatePosFantome1(-10);
                aBouge++;
                printf("abouge\n");
                fflush(stdout);
                break;
            case 3: //go left
                if (posFant1 % 10 == 0 && posFant1 - 1 == posFant2) {
                    break;
                }
                updatePosFantome1(-1);
                aBouge++;
                printf("abouge\n");
                fflush(stdout);
                break;
            default:
                break;
        }

    }

}

void mouvementFantome2(int pos) {
    //determiner la position du fantome
    srand(time(NULL));

    int aBouge = 0;

    while (aBouge == 0) {

        int randomAdv2 = rand() % 4;

        //on nettoie l'ancien fantome2

        if (plateau[posFant2] == adv2) {
            plateau[posFant2] = ' ';
        } else if (plateau[posFant2] == adv2e) {
            plateau[posFant2] = '*';
        }

        switch (randomAdv2) {
            case 0: // go up
                if (posFant2 < 10 || posFant2 - 10 == posFant1) { // cas d'erreur
                    break;
                }
                updatePosFantome2(10);
                aBouge++;
                printf("abouge\n");
                fflush(stdout);
                break;
            case 1: //go right
                if (posFant2 % 10 == 9 || posFant2 + 1 == posFant1) {
                    break;
                }
                updatePosFantome2(1);
                aBouge++;
                printf("abouge\n");
                fflush(stdout);
                break;
            case 2: //go down
                if (posFant2 >= 50 || posFant2 + 10 == posFant1) {
                    break;
                }
                updatePosFantome2(-10);
                aBouge++;
                printf("abouge\n");
                fflush(stdout);
                break;
            case 3: //go left
                if (posFant2 % 10 == 0 && posFant2 - 1 == posFant1) {
                    break;
                }
                updatePosFantome2(-1);
                aBouge++;
                printf("abouge\n");
                fflush(stdout);
                break;
            default:
                break;
        }
    }
}

void Collisions() {
    if (plateau[posJoueur] == plateau[posFant1] || plateau[posJoueur] == plateau[posFant2]) {
        vie--;
    }
}

int main(int argc, char const *argv[]) {
    int fdSocketAttente;
    int fdSocketCommunication;
    struct sockaddr_in coordonneesServeur;
    struct sockaddr_in coordonneesAppelant;
    char tampon[MAX_BUFFER];
    int nbRecu;
    int longueurAdresse;
    int pid;
    char *ip = inet_ntoa(coordonneesAppelant.sin_addr);

    fdSocketAttente = socket(PF_INET, SOCK_STREAM, 0);

    if (fdSocketAttente < 0) {
        printf("socket incorrecte\n");
        exit(EXIT_FAILURE);
    }

    // On prépare l’adresse d’attachement locale
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&coordonneesServeur, 0x00, longueurAdresse);

    coordonneesServeur.sin_family = PF_INET;
    // toutes les interfaces locales disponibles
    coordonneesServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    // toutes les interfaces locales disponibles
    coordonneesServeur.sin_port = htons(PORT);

    if (bind(fdSocketAttente, (struct sockaddr *) &coordonneesServeur, sizeof(coordonneesServeur)) == -1) {
        printf("erreur de bind\n");
        exit(EXIT_FAILURE);
    }

    if (listen(fdSocketAttente, 5) == -1) {
        printf("erreur de listen\n");
        exit(EXIT_FAILURE);
    }

    socklen_t tailleCoord = sizeof(coordonneesAppelant);

    int nbClients = 0;

    while (nbClients < MAX_CLIENTS) {

        if ((fdSocketCommunication = accept(fdSocketAttente, (struct sockaddr *) &coordonneesAppelant,
                                            &tailleCoord)) == -1) {
            printf("erreur de accept\n");
            exit(EXIT_FAILURE);
        }

        printf("Joueur %s Connecté!\n", ip);

        if ((pid = fork()) == 0) {
            close(fdSocketAttente);

            while (vie == 1) {

                if(tour==0) initialisationGrille();

                //partie envoie de la grille
                strcpy(tampon, plateau);

                if (testQuitter(tampon)) {
                    break; // on quitte la boucle
                }

                send(fdSocketCommunication, tampon, strlen(tampon), 0);

                //tampon[0] = 1;
                //send(fdSocketCommunication, tampon, strlen(tampon), 0);
                //on attend le message du client
                //la fonction recv est bloquante<<<<<<<<<<<<<<<<<<<<<<attente direction
                nbRecu = recv(fdSocketCommunication, tampon, MAX_BUFFER, 0);



                if (nbRecu > 0) {
                    tampon[nbRecu] = 0;
                    printf("Recu : %s\n", tampon);

                    if (testQuitter(tampon)) {
                        break; // on quitte la boucle
                    }
                }

                if (nbRecu < 0) {
                    printf("Erreur de réception\n");
                }

                //modification de la position du joueur

                pos = tampon[nbRecu-1];
                printf("%s\n", tampon);
                fflush(stdout);

                if (posJoueur % 10 != 0) {
                    if (pos == 'q') {
                        posJoueur--;
                    }
                }
                if (posJoueur % 10 != 9) {
                    if (pos == 'd') {
                        posJoueur++;
                    }
                }
                if (posJoueur > 9) {
                    if (pos == 'z') posJoueur = posJoueur - 10;
                }
                if (posJoueur < 50) {
                    if (pos == 's') posJoueur = posJoueur + 10;
                }

                mouvementJoueur(posJoueur);
                //vie = tampon[0];
                //send(fdSocketCommunication, tampon, strlen(tampon), 0);


                mouvementFantome1(posFant1);
                mouvementFantome2(posFant2);

                //evaluation des points et de la mort eventuelle
                Collisions();
                //vie = tampon[0];
                //send(fdSocketCommunication, tampon, strlen(tampon), 0);

                strcpy(tampon,plateau);

                if (testQuitter(tampon)) {
                    send(fdSocketCommunication, tampon, strlen(tampon), 0);
                    break; // on quitte la boucle
                }

                send(fdSocketCommunication, tampon, strlen(tampon), 0);

                tour++;
            }

            // determination du score avec presence ou non du bonus
            //core = bonus + score;

            //core = tampon[0];
            //onus = tampon[1];
            //end(fdSocketCommunication, tampon, strlen(tampon), 0);

            // si non alors le joueur a perdu
            // system("CLS");
            //f (bonus == 0) printf("\n\nLe Fantôme a été plus rusé que vous, %s... Vous avez perdu.\n\n", nom);

            //si oui alors le joueur a gagne
            //f (bonus == 50) {
            //   // system("CLS");
            //   printf("\n\n%s vous avez atteint l'objectif. Vous remportez la victoire.\nVous êtes acclamé par votre public !\n\n",
            //          nom);
            //   printf("%s votre score est de : %d\n\n", nom, score);

            exit(EXIT_SUCCESS);
        }

        nbClients++;

    }

    close(fdSocketCommunication);
    close(fdSocketAttente);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}

