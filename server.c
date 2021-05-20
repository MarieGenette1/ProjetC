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

char plateau[60 + 1], nom[20];
char joueur = 'C', pos, adv = 'O', adv2 = 'O', debut, fin;
int vie, tour = 0, tourAdv, posJoueur, posFant1, posFant2, score, bonus, adv1e = '0', adv2e = '0', nbetoiles;

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
    for (int i = 0; i < 60; i++) {
        if (plateau[i] == 'C') {
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
}

void mouvementFantome1() {
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


        //va en haut
        if (randomAdv1 == 0 && posFant1 > 10 && posFant1 - 10 != posFant2) {
            if (plateau[posFant1 - 10] == ' ') {
                posFant1 = posFant1 - 10;
                plateau[posFant1] = adv;
                aBouge++;

            } else if (plateau[posFant1] - 10 == '*') {
                posFant1 = posFant1 - 10;
                plateau[posFant1] = adv1e;
                aBouge++;
            }


            //va à droite
        } else if (randomAdv1 == 1 && posFant1 % 10 < 9 && posFant1 + 1 != posFant2) {
            if (plateau[posFant1 + 1] == ' ') {
                posFant1 = posFant1 + 1;
                plateau[posFant1] = adv;

                aBouge++;

            } else if (plateau[posFant1] + 1 == '*') {
                posFant1 = posFant1 + 1;
                plateau[posFant1] = adv1e;
                aBouge++;
            }



            //va en bas
        } else if (randomAdv1 == 2 && posFant1 < 50 && posFant1 + 10 != posFant2) {
            if (plateau[posFant1 + 10] == ' ') {
                posFant1 = posFant1 + 10;
                plateau[posFant1] = adv;

                aBouge++;

            } else if (plateau[posFant1] + 10 == '*') {
                posFant1 = posFant1 + 10;
                plateau[posFant1] = adv1e;
                aBouge++;

            }

            //va à gauche
        } else if (randomAdv1 == 3 && posFant1 % 10 != 0 && posFant1 - 1 != posFant2) {
            if (plateau[posFant1 - 1] == ' ') {
                posFant1 = posFant1 - 1;
                plateau[posFant1] = adv;
                aBouge++;

            } else if (plateau[posFant1] - 1 == '*') {
                posFant1 = posFant1 - 1;
                plateau[posFant1] = adv1e;
                aBouge++;
            }
        }
    }

}

void mouvementFantome2() {
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


        //va en haut
        if (randomAdv2 == 0 && posFant2 > 10 && posFant2 - 10 != posFant1) {
            if (plateau[posFant2 - 10] == ' ') {
                posFant2 = posFant2 - 10;
                plateau[posFant2] = adv2;
                aBouge++;

            } else if (plateau[posFant2] - 10 == '*') {
                posFant2 = posFant2 - 10;
                plateau[posFant2] = adv2e;
                aBouge++;
            }


            //va à droite
        } else if (randomAdv2 == 1 && posFant2 % 10 < 9 && posFant2 + 1 != posFant1) {
            if (plateau[posFant2 + 1] == ' ') {
                posFant2 = posFant2 + 1;
                plateau[posFant2] = adv2;
                aBouge++;

            } else if (plateau[posFant2] + 1 == '*') {
                posFant2 = posFant2 + 1;
                plateau[posFant2] = adv2e;
                aBouge++;

            }



            //va en bas
        } else if (randomAdv2 == 2 && posFant2 < 50 && posFant2 + 10 != posFant1) {
            if (plateau[posFant2 + 10] == ' ') {
                posFant2 = posFant2 + 10;
                plateau[posFant2] = adv2;
                aBouge++;

            } else if (plateau[posFant2] + 10 == '*') {
                posFant2 = posFant2 + 10;
                plateau[posFant2] = adv2e;
                aBouge++;

            }



            //va à gauche
        } else if (randomAdv2 == 3 && posFant2 % 10 != 0 && posFant2 - 1 != posFant1) {
            if (plateau[posFant2 - 1] == ' ') {
                posFant2 = posFant2 - 1;
                plateau[posFant2] = adv2;
                aBouge++;

            } else if (plateau[posFant2] - 1 == '*') {
                posFant2 = posFant2 - 1;
                plateau[posFant2] = adv2e;
                aBouge++;

            }
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

    fdSocketAttente = socket(PF_INET, SOCK_STREAM, 0);

    if (fdSocketAttente < 0) {
        printf("socket incorrecte\n");
        exit(EXIT_FAILURE);
    }

    //on prépare l'adresse d'attachement locale
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&coordonneesServeur, 0x00, longueurAdresse);

    coordonneesServeur.sin_family = PF_INET;
    coordonneesServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    coordonneesServeur.sin_port = htons(PORT);

    if (bind(fdSocketAttente, (struct sockaddr *) &coordonneesServeur, sizeof(coordonneesServeur)) == -1) {
        printf("erreur de bind \n");
        exit(EXIT_FAILURE);
    }

    if (listen(fdSocketAttente, 5) == -1) {
        printf("erreur de listen \n");
        exit(EXIT_FAILURE);
    }

    socklen_t tailleCoord = sizeof(coordonneesAppelant);

    int nbClients = 0;

    while (nbClients < MAX_CLIENTS) {


        if ((fdSocketCommunication = accept(fdSocketAttente, (struct sockaddr *) &coordonneesAppelant, &tailleCoord)) ==
            -1) {
            printf("erreur accept\n");
            exit(EXIT_FAILURE);
        }

        int pid = fork();
        char *ip = inet_ntoa(coordonneesAppelant.sin_addr);

        if (pid == 0) {

            printf("Joueur %s Connecté!\n", ip);

            if ((pid = fork()) == 0) {
                close(fdSocketAttente);

                while (1) {
                    //on attend le message du client
                    //la fonction recv est bloquante
                    nbRecu = recv(fdSocketCommunication, tampon, MAX_BUFFER, 0);

                    if (nbRecu < 0) {
                        printf("Erreur de réception");
                    }

                    if (nbRecu > 0) {
                        tampon[nbRecu] = 0;
                        printf("Reçu: %s \n", tampon);
                    }

                    //modification de la position du joueur
                    //fflush(stdout);
                    pos = ' ';
                    scanf(" %c", &tampon[0]);
                    while (pos != 'z' && pos != 'q' && pos != 's' && pos != 'd') {
                        printf("Veuillez entrer une direction valide \n");
                        printf("Entrez une direction : \n");
                        scanf(" %c", &pos);
                    }

                    if (posJoueur % 10 != 0) {
                        if (pos == 'q') posJoueur--;
                    }
                    if (posJoueur % 10 != 9) {
                        if (pos == 'd') posJoueur++;
                    }
                    if (posJoueur > 9) {
                        if (pos == 'z') posJoueur = posJoueur - 10;
                    }
                    if (posJoueur < 50) {
                        if (pos == 's') posJoueur = posJoueur + 10;
                    }

                    mouvementJoueur();
                    mouvementFantome2();
                    mouvementFantome1();

                    //evaluation des points et de la mort eventuelle
                    Collisions();

                    tampon[nbRecu] = plateau[nbRecu];

                    if (testQuitter(tampon)) {
                        send(fdSocketCommunication, tampon, strlen(tampon), 0);
                        break; // on quitte la boucle
                    }

                    send(fdSocketCommunication, tampon, strlen(tampon), 0);
                }

                // determination du score avec presence ou non du bonus
                score = bonus + score;

                // si non alors le joueur a perdu
                // system("CLS");
                if (bonus == 0) printf("\n\nLe Fantôme a été plus rusé que vous, %s... Vous avez perdu.\n\n", nom);

                //si oui alors le joueur a gagne
                if (bonus == 50) {
                    // system("CLS");
                    printf("\n\n%s vous avez atteint l'objectif. Vous remportez la victoire.\nVous etes acclame par votre public !\n\n",
                           nom);
                    printf("%s votre score est de : %d\n\n", nom, score);

                    close(fdSocketCommunication);
                    exit(EXIT_SUCCESS);
                }
                nbClients++;
            }
            close(fdSocketAttente);

            for (int i = 0; i < MAX_CLIENTS; i++) {
                wait(NULL);
            }

            return EXIT_SUCCESS;
        }

    }
}