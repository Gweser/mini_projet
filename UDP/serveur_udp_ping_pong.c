#include "udp.h"
#include "erreur.h"
#include "nombre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>


int traiter_commande_wrapper(int argc, char** argv) {
    traiter_commande(argc, argv, "Usage: <port>\nMauvais nombre d'arguments");
    traiter_commande(argc, argv, "Usage: <port>\n<port> est un port non réservé");
    return 0;
}

int main(int argc, char** argv) {
    traiter_commande_wrapper(argc, argv);


    exit(0);
}
