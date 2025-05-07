#include "../include/comparer.h"

int comparer(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] && s2[i]) {
        if ((s1[i] | 32) != (s2[i] | 32)) return 0;
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0');
}
