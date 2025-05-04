#include <stdio.h>      
#include "retourmenu.h" 
#include "utils.h"       

#define YELLOW "\033[1;33m"
#define RESET "\033[0m"


int demanderRetourMenu() {
    char buffer[10];

    printf("\n" YELLOW "Appuyez sur 'm' + Entrée pour retourner au menu, ou juste Entrée pour continuer... " RESET);

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 0;
    }

  
    if ((buffer[0] == 'm' || buffer[0] == 'M') &&
        (buffer[1] == '\n' || (buffer[1] == '\r' && buffer[2] == '\n') || buffer[1] == '\0') ) {
         return 1;
    }


    return 0;
}

