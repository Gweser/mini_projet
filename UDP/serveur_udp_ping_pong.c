#include "udp.h"
#include "erreur.h"
#include "nombre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

int main(int argc, char** argv) {

    traiter_commande(argc != 2, argv[0], "<port>\nmauvais nombre d'arguments");
    
    int port = atoi(argv[1]);
    traiter_commande(port < 1024 || port > 65535, argv[0], "<port>\n<port> est un port non réservé");
    
    // Créer la socket serveur
    SOCK socket_serveur;
    creer_socket(NULL, port, &socket_serveur);
    
    attacher_socket(&socket_serveur);
    
    printf("Serveur démarré sur le port %d\n", port);
    
    char buffer[TAILLE_BUFFER];
    
    while(1) {
        init_addr(&socket_serveur);
        
        recevoir_message(&socket_serveur, buffer);
        
        printf("Message reçu : %s\n", buffer);
        
        // Vérifier si le message reçu est "ping" et répondre avec "pong"
        if (strcmp(buffer, "ping") == 0) {
            envoyer_message(&socket_serveur, "pong");
            printf("Réponse envoyée : pong\n");
        } else {
            char reponse[TAILLE_BUFFER];
            snprintf(reponse, TAILLE_BUFFER, "Message reçu: %s", buffer);
            envoyer_message(&socket_serveur, reponse);
            printf("Réponse envoyée : %s\n", reponse);
        }
    }
    
    // Fermer la socket
    fermer_connexion(&socket_serveur);
    exit(0);
}
