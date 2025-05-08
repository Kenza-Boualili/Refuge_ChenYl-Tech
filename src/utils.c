#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
void nettoyerTampon() {
    while (getchar() != '\n'); 
}    
void enleverSautLigne(char *chaine, size_t taille_maximale) {
    for (size_t i = 0; i < taille_maximale && chaine[i] != '\0'; i++) {
        if (chaine[i] == '\n' || chaine[i] == '\r') {
            chaine[i] = '\0';
            return;
        }
    }
    if (taille_maximale > 0) {
        chaine[taille_maximale - 1] = '\0';
    }
}

size_t longueurChaine(const char *chaine) {
    size_t longueur = 0;  
    if (!chaine){
        return 0;
    } 
    while (chaine[longueur] && chaine[longueur] != '\n' && chaine[longueur] != '\r') {
        longueur++;
    }
    return longueur;
}

void copierTexte(char *destination, const char *source, int max_size) {
    size_t i = 0;
    while (source[i] != '\0' && i < max_size - 1) {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';  
}

void nettoyerLigne(char *ligne) {
    size_t i = 0;
    
    while (ligne[i]) {
        if (ligne[i] == '\n' || ligne[i] == '\r') {
            ligne[i] = '\0';  
            break;
        }
        i++;
    }
}

int extraireChamps(char *ligne, Animal *animal, char *especeTemp, char *commentaireTemp) {
    int champ = 0, index = 0, i = 0;
    char morceau[256];

    if (ligne == NULL || ligne[0] == '\0') {
        return 0;  // Ligne vide, on retourne
    }

    while (ligne[i]) {
        if (ligne[i] == ';' || ligne[i] == '\n' || ligne[i] == '\0') {
            morceau[index] = '\0'; 

            if (champ == 0 && morceau[0] == '\0') {
                printf("⚠️ Champ id manquant\n");
                return 0;  // Champ 'id' manquant, erreur
            }

            switch (champ) {
                case 0:  // id
                    animal->id = atoi(morceau);
                    break;
                case 1:  // nom
                    copierTexte(animal->nom, morceau, TAILLE_NOM);
                    break;
                case 2:  // espèce
                    copierTexte(especeTemp, morceau, 50);
                    break;
                case 3:  // année de naissance
                    animal->annee_naissance = atoi(morceau);
                    break;
                case 4:  // poids
                    animal->poids = atof(morceau);
                    break;
                case 5:  // commentaire
                    copierTexte(commentaireTemp, morceau, TAILLE_COMM);
                    break;
                default:
                    break;
            }

            champ++;
            index = 0;

            if (ligne[i] == '\n' || ligne[i] == '\0') {
                break;
            }
        } else {
            if (index < sizeof(morceau) - 1) {
                morceau[index++] = ligne[i];
            }
        }
        i++;
    }

    return champ >= 5;  
}
