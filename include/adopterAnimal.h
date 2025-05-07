// Fichier d'en-tête pour la fonction 'adopterAnimal'
// Ces lignes servent à éviter que le contenu de ce fichier soit inclus
// plusieurs fois dans un même fichier source 
// Si 'ADOPTER_ANIMAL_H' n'a pas encore été défini:
#ifndef ADOPTER_ANIMAL_H
// alors on le définit maintenant:
#define ADOPTER_ANIMAL_H

// :Déclaration de la fonction
// c'est une déclaration de fonction.
// Elle informe le compilateur qu'une fonction appelé 'adopterAnimal' existe quelque part
// void signifie que la fonction ne retourne aucune valeur.
// adopterAnimal est le nom de la fonction.
// () signifie que la fonction ne prend aucun paramètre en entrée.
// Le code de cette fonction  se trouve dans un fichier .c séparé.
void adopterAnimal();

// Si 'ADOPTER_ANIMAL_H' était déjà défini,
// le compilateur ignore tout ce qui se trouve entre #ifndef et #endif.
#endif // ADOPTER_ANIMAL_H
