#ifndef ANIMAL_H
#define ANIMAL_H

#define MAX_ANIMAUX 50
#define TAILLE_NOM 50
#define TAILLE_COMM 256

typedef enum {
    CHIEN,
    CHAT,
    HAMSTER,
    AUTRUCHE
} Espece;

typedef struct {
    int id;
    char nom[TAILLE_NOM];
    Espece espece;
    int annee_naissance;
    float poids;
    char commentaire[TAILLE_COMM];
} Animal;

Espece choisirEspece();

Espece chaineVersEspece(const char* str);

const char* especeVersChaine(Espece e);

void adopterAnimal();

#endif
