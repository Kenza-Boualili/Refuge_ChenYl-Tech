#ifndef NETTOYEUR_H          // Si NETTOYEUR_H n'est pas défini,
                             // cela permet d'éviter les inclusions multiples

#define NETTOYEUR_H          // Définit NETTOYEUR_H pour "bloquer" 
                             // ce fichier lors des prochaines inclusions

int comparer(const char* s1, const char* s2);  // Déclaration d'une fonction :
                                               // - Retourne un entier (résultat de comparaison)
                                               // - Prend 2 chaînes de caractères en entrée (s1 et s2)

int especeValide(const char* espece);          // Déclaration d'une fonction :
                                               // - Retourne 1 (vrai) ou 0 (faux)
                                               // - Vérifie si l'espèce (exemple: "Chat") est valide

void nettoyerFichierAnimaux();                 // Déclaration d'une fonction :
                                               // - Ne retourne rien (void)
                                               // - Effectue un nettoyage du fichier d'animaux  pour corriger les erreurs dans le fichier

#endif                     // Fin de la protection contre les inclusions multiples
