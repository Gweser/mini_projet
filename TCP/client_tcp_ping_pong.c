#include "tcp.h"
#include "erreur.h"
#include "nombre.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Fonction pour vérifier si une chaîne est une adresse IP valide
int is_valid_ip(const char* ip) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1;
}

void traiter_commande_wrapper(int argc, char** argv) {
    // Vérifier le nombre d'arguments
    traiter_commande(argc != 3, argv[0], 
        "<adresse IP> <port>\nmauvais nombre d'aguments");

    // Vérifier le format de l'adresse IP
    traiter_commande(!is_valid_ip(argv[1]), argv[0], 
        "<adresse IP> <port>\n<adresse IP> est une adresse IP au format décimal pointé");

    // Vérifier que le port est valide 
    int port = atoi(argv[2]);
    traiter_commande(port < 1024 || port > 65535, argv[0], 
        "<adresse IP> <port>\n<port> est un port non réservé");
}

int main(int argc, char** argv) {
	
    traiter_commande_wrapper(argc, argv);
    
    // Récupérer les arguments
    char* adresseIP = argv[1];
    int port = atoi(argv[2]);
    
    // Créer la socket client
    SOCK socket_client;
    creer_socket(adresseIP, port, &socket_client);
    
    // Envoyer le message "ping"
    char* message = "ping";
    envoyer_message(&socket_client, message);
    printf("Message envoyé : %s\n", message);
    
    // Attendre la réponse "pong"
    char buffer[TAILLE_BUFFER];
    recevoir_message(&socket_client, buffer);
    printf("Réponse reçue : %s\n", buffer);
    
    // Fermer la connexion
    fermer_connexion(&socket_client);
    
    return 0;
}
