# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <arpa/inet.h>

#define PORT 6001
#define MAX_BUFFER 1000
#define EXIT "exit"


void lireMessage(char tampon[]) {
    printf("Saisir un message à envoyer:\n");
    fgets(tampon, MAX_BUFFER, stdin);
    strtok(tampon, "\n");
}

int testQuitter(char tampon[]) {
    return strcmp(tampon, EXIT) == 0;
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

    for (int i = 0; i < 3; ++i) {


        if ((fdSocketCommunication = accept(fdSocketAttente, (struct sockaddr *) &coordonneesAppelant, &tailleCoord)) ==
            -1) {
            printf("erreur accept\n");
            exit(EXIT_FAILURE);
        }

        int pid = fork();
        char *ip = inet_ntoa(coordonneesAppelant.sin_addr);

        if(pid == 0) {

            printf("Cient %s Connecté!\n", ip);

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

                lireMessage(tampon);

                if (testQuitter(tampon)) {
                    send(fdSocketCommunication, tampon, strlen(tampon), 0);
                    break; // on quitte la boucle
                }
            }

            close(fdSocketCommunication);
            exit(EXIT_SUCCESS);
        }
    }
    close(fdSocketAttente);

    return EXIT_SUCCESS;

}