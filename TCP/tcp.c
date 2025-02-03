#include "erreur.h"
#include "tcp.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int creer_socket(char* adresseIP, int port) {
    int sock;
    int ip;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        traiter_erreur(__FUNCTION__);
    }

    ip = inet_addr(adresseIP);
    if (ip == -1) {
        traiter_erreur(__FUNCTION__);
    }

    if (connect(sock, (struct sockaddr *)&ip, sizeof(ip)) == -1) {
        traiter_erreur(__FUNCTION__);
    }

    return sock;
}

void connecter_socket(int sock, char* adresseIP, int port) {
    int ip;
    
    ip = inet_addr(adresseIP);
    if (ip == -1) {
        traiter_erreur(__FUNCTION__);
    }

    if (connect(sock, (struct sockaddr *)&ip, sizeof(ip)) == -1) {
        traiter_erreur(__FUNCTION__);
    }
}

void attacher_socket(int sock, int port) {
    int ip;
    
    ip = INADDR_ANY;

    if (bind(sock, (struct sockaddr *)&ip, sizeof(ip)) == -1) {
        traiter_erreur(__FUNCTION__);
    }
}

void dimensionner_file_attente_socket(int sock, int taille) {
    if (listen(sock, taille) == -1) {
        traiter_erreur(__FUNCTION__);
    }
}

void init_addr_client(int sock) {
}

int attendre_connexion(int sock) {
    int socktraitement;
    
    socktraitement = accept(sock, NULL, NULL);
    if (socktraitement == -1) {
        traiter_erreur(__FUNCTION__);
    }

    return socktraitement;
}

void recevoir_message(int socktraitement, char * buffer) {
    int n;
    n = recv(socktraitement, buffer, 1024, 0);
    if (n == -1) {
        traiter_erreur(__FUNCTION__);
    }
    buffer[n] = '\0'; 
}

void envoyer_message(int socktraitement, char * message) {
    int n;
    n = send(socktraitement, message, strlen(message), 0);
    if (n == -1) {
        traiter_erreur(__FUNCTION__);
    }
}

void fermer_connexion(int socktraitement) {
    if (close(socktraitement) == -1) {
        traiter_erreur(__FUNCTION__);
    }
}
