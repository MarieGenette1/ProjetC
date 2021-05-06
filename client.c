
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <arpa/inet.h>

#define PORT 6000
#define MAX_BUFFER 1000

const char *EXIT = "exit";

void lireMessage(char tampon[]){
    printf("Saisir un message à envoyer:\n");
    fgets(tampon ,MAX_BUFFER, stdin);
    strtok(tampon, "\n");
}


int testQuitter(char tampon[]) {
    return strcmp(tampon, EXIT) == 0;
}

int main(int argc, char const *argv[]){
    int fdSocket;
    int nbRecu;
    struct sockaddr_in coordonneesServeur;
    int longueurAdresse;
    char tampon[MAX_BUFFER];

    fdSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(fdSocket < 0){
        printf("socket incorrecte \n");
        exit(EXIT_FAILURE);
    }

    //on prépare l'adresse d'attachement locale
    longueurAdresse = sizeof(struct sockaddr_in);
    memset(&coordonneesServeur, 0x00, longueurAdresse);

    coordonneesServeur.sin_family=PF_INET;
    inet_aton("192.168.192.39", &coordonneesServeur.sin_addr);
    coordonneesServeur.sin_port = htons(PORT);

    if(connect(fdSocket, (struct sockaddr *) &coordonneesServeur, sizeof(coordonneesServeur)) ==-1){
        printf("connexion impossible\n");
        exit(EXIT_FAILURE);
    }

    printf("Connexion réussie! \n");

    for(int i = 0; i < 4; i++){
        printf("Envoie du message au serveur\n");
        lireMessage(tampon);

        send(fdSocket, tampon, strlen(tampon), 0);

        nbRecu = recv(fdSocket, tampon, MAX_BUFFER, 0); //on attend la réponse du serveur

        if (nbRecu > 0) {
            tampon[nbRecu] = 0;
            printf("Reçu : %s \n", tampon);
        }

        if (testQuitter(tampon)) {
            break; // on quitte la boucle
        }
    }

    close(fdSocket);

    return EXIT_SUCCESS;

}