#include "udp.h"
#include "erreur.h"
#include "nombre.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>


void traiter_commande(int, const char *, const char *);

void traiter_commande_wrapper(int argc, char** argv) {
    traiter_commande(argc, argv, "Usage: <adresse IP> <port> <message>\nMauvais nombre d'arguments");
    traiter_commande(argc, argv, "Usage: <adresse IP> <port> <message>\n<adresse IP> est une adresse IP au format décimal pointé");
    traiter_commande(argc, argv, "Usage: <adresse IP> <port> <message>\n<port> est un port non réservé");
    return 0;
}

int main(int argc, char** argv) {
    traiter_commande_wrapper(argc, argv);

    exit(0);
}
