// Assure que le contenu de ce fichier n'est inclus qu'une seule fois
// lors de la compilation pour éviter les erreurs de redéfinition.
#ifndef ANIMAL_H
#define ANIMAL_H


// Utilisation de '#define' pour créer des constantes.
// Cela rend le code plus lisible et facilite les modifications.
// Définit le nombre maximum d'animaux que le programme peut gérer.
#define MAX_ANIMAUX 50
// Définit la taille maximale pour le nom d'un animal.
#define TAILLE_NOM 50
// Définit la taille maximale pour le commentaire associé à un animal.
#define TAILLE_COMM 256

// 'typedef enum' crée un nouveau type de données qu'on a appelé 'Espece'.
// Une variable de type 'Espece' peut seulement contenir l'une des valeurs listées
// (CHIEN, CHAT, HAMSTER, AUTRUCHE).
typedef enum {
    CHIEN,       // Représente l'espèce Chien
    CHAT,        // Représente l'espèce Chat
    HAMSTER,     // Représente l'espèce Hamster
    AUTRUCHE     // Représente l'espèce Autruche
} Espece;


// 'typedef struct' définit une structure regroupées sous un seul nom.
// Ici, nous créons un nouveau type de données appelé 'Animal'.
typedef struct {
    int id;                     // Identifiant unique pour chaque animal (un nombre entier).
    char nom[TAILLE_NOM];       // Nom de l'animal (une chaîne de caractères, taille max définie par TAILLE_NOM).
    Espece espece;              // L'espèce de l'animal (utilise le type 'Espece' défini ci-dessus).
    int annee_naissance;        // Année de naissance de l'animal (un nombre entier).
    float poids;                // Poids de l'animal (un nombre décimal).
    char commentaire[TAILLE_COMM]; // Un commentaire libre sur l'animal (chaîne de caractères, taille max définie par TAILLE_COMM).
} Animal;



// Déclare une fonction 'choisirEspece'.
// Elle ne prend aucun argument '()' et retourne une valeur de type 'Espece'.
Espece choisirEspece();

// Déclare une fonction 'strToEspece'.
// Elle prend en argument un pointeur vers une chaîne de caractères constante
// et retourne une valeur de type 'Espece'.
// (pour convertir un nom d'espèce écrit en texte comme "CHAT" en valeur 'Espece').
Espece strToEspece(const char* str);

// Déclare une fonction 'especeToStr'.
// Elle prend en argument une valeur de type 'Espece'
// et retourne un pointeur vers une chaîne de caractères constante ('const char*').
// (pour convertir une valeur 'Espece' comme CHAT en texte "CHAT").
const char* especeToStr(Espece e);

// Déclare la fonction 'adopterAnimal'.
// Elle ne prend aucun argument '()' et ne retourne rien ('void').
void adopterAnimal();

#endif 