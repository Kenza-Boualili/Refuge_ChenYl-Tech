
#ifndef ANIMAL_H
#define ANIMAL_H
#define MAX_ANIMAUX 50
#define TAILLE_COMM 256
#define TAILLE_NOM 50



// Définition de l'énumération des espèces

typedef enum Espece {
CHIEN,
 CHAT,
HAMSTER,
 AUTRUCHE,
 INCONNU

} Espece;
// Structure représentant un animal
typedef struct Animal {

    int id;

    char nom[TAILLE_NOM];  // Utilisation de TAILLE_NOM

    Espece espece;

    int annee_naissance;

    float poids;

    char commentaire[TAILLE_COMM];

} Animal;
// Déclarations des fonctions

Espece chaineVersEspece(const char *str);

const char* especeVersChaine(Espece e);

void enleverSautLigne(char *chaine, int taille_max);

Espece choisirEspece();
#endif // ANIMAL_H











