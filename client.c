# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <arpa/inet.h>
#include <time.h>

#define PORT 6000
#define MAX_BUFFER 100
#define EXIT "exit"

char plateau[60 + 1], nom[20];
char joueur = 'C', pos, adv = 'O', adv2 = 'O', debut, fin;
int vie, tour = 0, tourAdv, posJoueur, posFant1, posFant2, score, bonus;


void lireMessage(char tampon[]) {
    printf("Entrez une direction : \n");
    fgets(tampon, MAX_BUFFER, stdin);
    strtok(tampon, "\n");
    pos = tampon[0];

    while (pos != 'z' && pos != 'q' && pos != 's' && pos != 'd') {
        printf("Veuillez entrer une direction valide \n");
        printf("Entrez une direction : \n");
        scanf(" %c", &pos);
    }

}

void afficheGrille(char *plateau) {
    system("clear");
    printf("Votre score est de :%d\n", tour);
    printf("_____________\n");
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[0], plateau[1], plateau[2], plateau[3], plateau[4], plateau[5],
           plateau[6], plateau[7], plateau[8], plateau[9]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[10], plateau[11], plateau[12], plateau[13], plateau[14],
           plateau[15], plateau[16], plateau[17], plateau[18], plateau[19]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[20], plateau[21], plateau[22], plateau[23], plateau[24],
           plateau[25], plateau[26], plateau[27], plateau[28], plateau[29]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[30], plateau[31], plateau[32], plateau[33], plateau[34],
           plateau[35], plateau[36], plateau[37], plateau[38], plateau[39]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[40], plateau[41], plateau[42], plateau[43], plateau[44],
           plateau[45], plateau[46], plateau[47], plateau[48], plateau[49]);
    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n", plateau[50], plateau[51], plateau[52], plateau[53], plateau[54],
           plateau[55], plateau[56], plateau[57], plateau[58], plateau[59]);
    printf("_____________\n");
    printf("\n");

    fflush(stdout);

}

int testQuitter(char tampon[]) {
    return strcmp(tampon, EXIT) == 0;
}

int main(int argc, char const *argv[]) {
    int fdSocket;
    int nbRecu;
    struct sockaddr_in coordonneesServeur;
    int longueurAdresse;
    char tampon[MAX_BUFFER];
    vie = 1;

    fdSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (fdSocket < 0) {
        printf("socket incorrecte \n");
        exit(EXIT_FAILURE);
    }

    //on prépare l'adresse d'attachement locale
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&coordonneesServeur, 0x00, longueurAdresse);

    coordonneesServeur.sin_family = PF_INET;
    inet_aton("127.0.0.1", &coordonneesServeur.sin_addr);
    coordonneesServeur.sin_port = htons(PORT);

    if (connect(fdSocket, (struct sockaddr *) &coordonneesServeur, sizeof(coordonneesServeur)) == -1) {
        printf("connexion impossible\n");
        exit(EXIT_FAILURE);
    }

    printf("Connexion réussie! \n");

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

    printf("\nEntrez votre nom puis appuyez sur Entree pour commencer :\n");
    fgets(nom, 19, stdin);

    //nbRecu = recv(fdSocket, tampon, MAX_BUFFER, 0);
    //tampon[nbRecu] = vie;

    while (1) {

        //nbRecu = recv(fdSocket, tampon, MAX_BUFFER, 0);
        //tampon[0] = vie;

        //partie reception et affichage grille
        nbRecu = recv(fdSocket, tampon, MAX_BUFFER, 0);

        strcpy(plateau, tampon);

        if (nbRecu > 0) {
            tampon[nbRecu] = 0;

            if (testQuitter(tampon)) {
                break; // on quitte la boucle
            }
        }

        if (nbRecu < 0) {
            printf("Erreur de réception\n");
        }

        afficheGrille(plateau);

        //partie lecture dir et envoie

        lireMessage(tampon);

        if (testQuitter(tampon)) {
            break; // on quitte la boucle
        }

        // on envoie le message au serveur
        printf("tampon : %s", tampon);
        send(fdSocket, tampon, strlen(tampon), 0);

        tour++;

    }

    close(fdSocket);

    // system("PAUSE");
    // system("clear");

    return EXIT_SUCCESS;

}