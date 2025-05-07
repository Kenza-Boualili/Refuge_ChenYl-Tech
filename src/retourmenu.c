#include <stdio.h>      
#include "retourmenu.h" 
#include "utils.h"       

#define JAUNE  "\033[1;33m"
#define REINITIALISER "\033[0m"

// Demande à l'utilisateur s’il souhaite revenir au menu
int demanderRetourMenu() {
    char tampon[10];

    printf("\n" JAUNE "Appuyez sur 'm' + Entrée pour retourner au menu, ou juste Entrée pour continuer... " REINITIALISER);

    if (!fgets(tampon, sizeof(tampon), stdin)) {
        return 0;
    }

    if ((tampon[0] == 'm' || tampon[0] == 'M') &&
        (tampon[1] == '\n' || (tampon[1] == '\r' && tampon[2] == '\n') || tampon[1] == '\0')) {
        return 1;
    }

    return 0;
}


