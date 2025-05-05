#include "id.h"
#include <time.h>
#include <stdlib.h>

int genererID() {
    return (int)time(NULL) % 100000 + rand() % 100;
}