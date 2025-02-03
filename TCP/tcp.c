#include "tcp.h"
#include "erreur.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static struct sockaddr_in serv_addr, cli_addr;
static socklen_t clilen;

int creer_socket(char* adresseIP, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        traiter_erreur("Erreur lors de la création de la socket");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (adresseIP == NULL) {
        serv_addr.sin_addr.s_addr = INADDR_ANY;
    } else {
        if (inet_pton(AF_INET, adresseIP, &serv_addr.sin_addr) <= 0) {
            traiter_erreur("Adresse IP invalide");
        }
    }

    return sockfd;
}

void connecter_socket(int sockfd) {
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        traiter_erreur("Erreur lors de la connexion de la socket");
    }
}

void attacher_socket(int sockfd) {
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        traiter_erreur("Erreur lors de l'attachement de la socket");
    }
}

void dimensionner_file_attente_socket(int sockfd, int taille) {
    if (listen(sockfd, taille) < 0) {
        traiter_erreur("Erreur lors de l'écoute des connexions");
    }
}

void init_addr_client() {
    clilen = sizeof(cli_addr);
    memset(&cli_addr, 0, clilen);
}

int attendre_connexion(int sockfd) {
    int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        traiter_erreur("Erreur lors de l'acceptation de la connexion");
    }
    return newsockfd;
}

void recevoir_message(int sockfd, char *buffer) {
    ssize_t nbytes = read(sockfd, buffer, TAILLE_MSG - 1);
    if (nbytes < 0) {
        traiter_erreur("Erreur lors de la réception du message");
    }
    buffer[nbytes] = '\0'; // Assurer que le message est terminé par un caractère nul
}

void envoyer_message(int sockfd, char *message) {
    ssize_t nbytes = write(sockfd, message, strlen(message));
    if (nbytes < 0) {
        traiter_erreur("Erreur lors de l'envoi du message");
    }
}

void fermer_connexion(int sockfd) {
    if (close(sockfd) < 0) {
        traiter_erreur("Erreur lors de la fermeture de la connexion");
    }
}
