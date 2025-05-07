#include "id.h"
#include <time.h>
#include <stdlib.h>

// Génère un identifiant aléatoire basé sur l'heure et un décalage
int genererID() {
    return (int)time(NULL) % 100000 + rand() % 100;
}
