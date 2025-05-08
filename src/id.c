#include "../include/comparer.h"
#include "../include/animal.h"
int comparer(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] && s2[i]) {
        if ((s1[i] | 32) != (s2[i] | 32)) return 0;
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0');
}
int comparerAnimauxParEspece(const void *a, const void *b) {
    Animal *animal1 = (Animal *)a;
    Animal *animal2 = (Animal *)b;

    // Compare les espèces des animaux
    if (animal1->espece < animal2->espece) {
        return -1; // animal1 est avant animal2
    } else if (animal1->espece > animal2->espece) {
        return 1; // animal1 est après animal2
    } else {
        return 0; // Les deux animaux ont la même espèce
    }
}
