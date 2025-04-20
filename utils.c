#include "utils.h"
#include <stdio.h>

void nettoyerBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Comparaison manuelle sans string.h (insensible à la casse)
int compareStr(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i]) {
        char ca = (a[i] >= 'A' && a[i] <= 'Z') ? a[i] + 32 : a[i];
        char cb = (b[i] >= 'A' && b[i] <= 'Z') ? b[i] + 32 : b[i];
        if (ca != cb) return 0;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}