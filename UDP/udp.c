#include "erreur.h"
#include "udp.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void creer_socket(char* adresseIP, int port, int* sock) {
    *sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (*sock == -1) {
        traiter_erreur("Erreur lors de la création de la socket");
        exit(EXIT_FAILURE);
    }
}

void attacher_socket(int* sock, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(*sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        traiter_erreur("Erreur lors de l'attachement de la socket");
        close(*sock);
        exit(EXIT_FAILURE);
    }
}

void init_addr(struct sockaddr_in* addr, char* adresseIP, int port) {
    memset(addr, 0, sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    if (inet_aton(adresseIP, &addr->sin_addr) == 0) {
        traiter_erreur("Adresse IP invalide");
        exit(EXIT_FAILURE);
    }
}

void dimensionner_file_attente_socket(int taille, int* sock) {
    traiter_erreur(__FUNCTION__);
}

void recevoir_message(int* sock, char* buffer, struct sockaddr_in* expediteur) {
    socklen_t exp_len = sizeof(struct sockaddr_in);
    ssize_t bytes_recus = recvfrom(*sock, buffer, 1024, 0, (struct sockaddr*)expediteur, &exp_len);

    if (bytes_recus < 0) {
        traiter_erreur("Erreur de réception du message");
    } else {
        buffer[bytes_recus] = '\0'; 
    }
}

void envoyer_message(int* sock, char* message, struct sockaddr_in* dest) {
    ssize_t bytes_envoyes = sendto(*sock, message, strlen(message), 0, 
                                   (struct sockaddr*)dest, sizeof(struct sockaddr_in));

    if (bytes_envoyes < 0) {
        traiter_erreur("Erreur d'envoi du message");
    }
}
void fermer_connexion(int* sock) {
    close(*sock);
}
