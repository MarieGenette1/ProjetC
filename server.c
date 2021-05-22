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
int vie=1, tour = 0, posJoueur=3, posFant1=20, posFant2=59, score=0, bonus=0, adv1e = '0', adv2e = '0', nbetoiles, nbClients = 0;

void videGrille(void) {
    for (int i = 0; i < 60; i++) {
        plateau[i] = ' ';
    }
}

int testQuitter(char tampon[]) {
    return strcmp(tampon, EXIT) == 0;
}

void mouvementJoueur() {
    //on nettoie l'ancien pacman
    printf("in mvt j\n");
    fflush(stdout);
    for (int i = 0; i < 60; i++) {
        if (plateau[i] == joueur) {
            plateau[i] = ' ';
        }
    }
    //on place le nouveau
    if (plateau[posJoueur] == plateau[posFant1] || plateau[posJoueur] == plateau[posFant2]) {
        vie--;
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
    printf("%c", plateau[4]);
}

void updatePosFantome1(int deplacement) {
    posFant1 = posFant1 + deplacement;
    plateau[posFant1] = plateau[posFant1 + deplacement] == ' ' ? adv : adv1e;
}

void updatePosFantome2(int deplacement) {
    posFant2 = posFant2 + deplacement;
    plateau[posFant2] = plateau[posFant2 + deplacement] == ' ' ? adv2 : adv2e;
}

void mouvementFantome1() {
    //determiner la position du fantome
    printf("in mvt f1\n");
    fflush(stdout);

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

void mouvementFantome2() {
    //determiner la position du fantome
    srand(time(NULL));
    printf("in mvt f2\n");
    fflush(stdout);


    int aBouge = 0;

    while (aBouge == 0) {

        int randomAdv2 = rand() % 4;

        printf("random: %d\n", randomAdv2);
        fflush(stdout);
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
    printf("out mvt f2\n");
    fflush(stdout);
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

            while (1) {
                //tampon[0] = 1;
                //send(fdSocketCommunication, tampon, strlen(tampon), 0);
                //on attend le message du client
                //la fonction recv est bloquante<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                nbRecu = recv(fdSocketCommunication, tampon, MAX_BUFFER, 0);

                if (nbRecu > 0) {
                    tampon[nbRecu] = 0;
                    printf("Recu : %s\n", tampon);

                    if (testQuitter(tampon)) {
                        break; // on quitte la boucle
                    }
                    printf("ccccc\n");
                }

                printf("jnkvnekrbv\n");
                fflush(stdout);

                if (nbRecu < 0) {
                    printf("Erreur de réception\n");
                }

                //modification de la position du joueur

                pos = tampon[nbRecu-1];
                printf("%s, %d", tampon, nbRecu);
                fflush(stdout);

                if (posJoueur % 10 != 0) {
                    if (pos == 'q') {
                        posJoueur--;
                        printf("joie");
                        fflush(stdout);
                    }
                }
                if (posJoueur % 10 != 9) {
                    if (pos == 'd') {
                        posJoueur++;
                        printf("pate\n");
                        fflush(stdout);
                    }
                }
                if (posJoueur > 9) {
                    if (pos == 'z') posJoueur = posJoueur - 10;
                }
                if (posJoueur < 50) {
                    if (pos == 's') posJoueur = posJoueur + 10;
                }

                mouvementJoueur();
                //vie = tampon[0];
                //send(fdSocketCommunication, tampon, strlen(tampon), 0);

                mouvementFantome2();
                mouvementFantome1();

                //evaluation des points et de la mort eventuelle
                Collisions();
                //vie = tampon[0];
                //send(fdSocketCommunication, tampon, strlen(tampon), 0);

                printf("nouveau\n");
                fflush(stdout);
                printf("%c", plateau[4]);
                fflush(stdout);
                *tampon = *plateau;

                if (testQuitter(tampon)) {
                    send(fdSocketCommunication, tampon, strlen(tampon), 0);
                    break; // on quitte la boucle
                }
                printf("avant d'envoyer\n");
                fflush(stdout);

                send(fdSocketCommunication, tampon, strlen(tampon), 0);

                printf("%s\n", tampon);
                fflush(stdout);
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

