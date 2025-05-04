// Si 'AJOUTER_H' n'a pas été défini avant:
#ifndef AJOUTER_H
// alors on le définit maintenant.
#define AJOUTER_H
// Ceci est la déclaration de la fonction 'ajouterAnimal'.
// Elle sert à informer le compilateur qu'une fonction avec ce nom existe.
// 'void' indique que la fonction ne retourne aucune valeur.
// 'ajouterAnimal' est le nom choisi pour cette fonction.
//  '()' signifie que la fonction n'a besoin d'aucun paramètre pour être appelée.
//le code qui exécute la fonction se trouve dans un fichier source .c.
void ajouterAnimal();

// Si 'AJOUTER_H' était déjà défini, le compilateur
// ignore tout ce qui précède cette ligne.
#endif // AJOUTER_H