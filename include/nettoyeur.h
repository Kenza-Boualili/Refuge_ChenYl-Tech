#ifndef NETTOYEUR_H
#define NETTOYEUR_H

// Compare deux chaînes (retourne 1 si égales, 0 sinon)
int comparer(const char* s1, const char* s2);

// Vérifie si une espèce donnée est valide (Chien, Chat, Hamster, Autruche)
int especeValide(const char* espece);

// Nettoie le fichier des animaux en supprimant les lignes invalides
void nettoyerFichierAnimaux();

#endif // NETTOYEUR_H
