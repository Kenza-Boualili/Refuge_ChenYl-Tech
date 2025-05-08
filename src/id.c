#include<stdlib.h>
#include<time.h>
int genererID() {
    return (int)time(NULL) % 100000 + rand() % 100;
}
