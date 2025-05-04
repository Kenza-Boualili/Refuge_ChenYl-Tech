// Si le symbole 'COMPARER_H' n'a pas encore été défini:
#ifndef COMPARER_H
//on le définit maintenant.
#define COMPARER_H

// 'int' indique que la fonction retourne un nombre entier.
//  pour une fonction de comparaison, la valeur retournée indique le résultat de la comparaison :
//     - 0 si les deux chaînes sont égales.
//     - une valeur négative si la première chaîne (s1) est "avant" la seconde (s2) dans l'ordre alphabétique.
//     - une valeur positive si la première chaîne (s1) est "après" la seconde (s2) dans l'ordre alphabétique.
//   - 'const char *s1' : Un pointeur vers une chaîne de caractères.
//   - 'const char *s2' : Un pointeur vers une seconde chaîne de caractères,
int comparer(const char *s1, const char *s2);
#endif // COMPARER_H