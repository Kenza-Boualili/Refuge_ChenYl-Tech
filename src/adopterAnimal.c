#include <stdio.h>
#include <stdlib.h>
#include <time.h> //test

#include "animal.h"     
#include "retourmenu.h"
#include "utils.h"      
#include "comparer.h"

#define ROUGE_GRAS     "\033[1;31m"
#define VERT_GRAS  "\033[1;32m"
#define JAUNE_GRAS "\033[1;33m"
#define BLEU_GRAS    "\033[1;34m"
#define CYAN_GRAS    "\033[1;36m"

#define ROSE         "\033[1;35m"
#define VERT       "\033[1;32m"
#define CYAN         "\033[1;36m"
#define ROUGE          "\033[1;31m"
#define BLANC      "\033[1;37m"

#define REINITIALISER        "\033[0m"


static int calculerAgeAdopter(int annee_naissance) {
    if (annee_naissance <= 0) {
        return -2;
    }

    time_t maintenant = time(NULL);
    struct tm *tm = localtime(&maintenant);

    if (tm == NULL) {
        return -1;
    }

    int annee_actuelle = tm->tm_year + 1900;

    if (annee_naissance > annee_actuelle || annee_naissance < 1900) {
        return -2;
    }

    return annee_actuelle - annee_naissance;
}

void adopterAnimal() {
    
    FILE *f_entree = NULL, *f_sortie = NULL;

    
    char tampon_saisie[TAILLE_NOM + 10];

    int id_a_adopter = -1;
    int choix_methode = 0;
    int adoption_terminee = 0;
    char ligne[512];

   
    Animal correspondances[MAX_ANIMAUX];
    int nb_correspondances = 0;
    Animal animal_temporaire; 

    char espece_temp_str[50];
   char commentaire_temp_str[TAILLE_COMM];
    while (!adoption_terminee) {
        id_a_adopter = -1;
        nb_correspondances = 0;

        printf(BLEU_GRAS "\n=== Adopter un Animal ===\n" REINITIALISER);
        printf("Comment identifier l'animal ?\n1. Par ID\n2. Par Nom\n Tapez 'm' pour menu principal.\n");
        printf(CYAN_GRAS "Choix : " REINITIALISER);

        if (!fgets(tampon_saisie, sizeof(tampon_saisie), stdin)) {
            return;
        }

        enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));

        if (tampon_saisie[0] == 'm' && tampon_saisie[1] == '\0') {
            return;
        }

        if (sscanf(tampon_saisie, "%d", &choix_methode) != 1 || (choix_methode != 1 && choix_methode != 2)) {
            printf(ROUGE_GRAS "❌ Choix invalide (1 ou 2).\n" REINITIALISER);
            printf(JAUNE_GRAS "(Rappel : 'm' menu.)\n" REINITIALISER);
            continue;
        }

        if (choix_methode == 1) {
            printf(JAUNE_GRAS "Entrez l'ID ('r' retour, 'm' menu) : " REINITIALISER);
            if (!fgets(tampon_saisie, sizeof(tampon_saisie), stdin)) {
                return;
            }
            enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));

            if (tampon_saisie[0] == 'm' && tampon_saisie[1] == '\0') {
                return;
            }
            if (tampon_saisie[0] == 'r' && tampon_saisie[1] == '\0') {
                continue;
            }

            if (sscanf(tampon_saisie, "%d", &id_a_adopter) != 1 || id_a_adopter <= 0) {
                printf(ROUGE_GRAS "❌ ID invalide.\n" REINITIALISER);
                printf(JAUNE_GRAS "(Rappel : 'r' retour, 'm' menu.)\n" REINITIALISER);
                continue;
            }

            printf(VERT_GRAS "Recherche ID %d...\n" REINITIALISER, id_a_adopter);
        } else { // choix_methode == 2
            printf(JAUNE_GRAS "Entrez le Nom ('r' retour, 'm' menu) : " REINITIALISER);
            if (!fgets(tampon_saisie, sizeof(tampon_saisie), stdin)) {
                return;
            }
            enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));

            if (tampon_saisie[0] == 'm' && tampon_saisie[1] == '\0') {
                return;
            }
            if (tampon_saisie[0] == 'r' && tampon_saisie[1] == '\0') {
                continue;
            }

            if (tampon_saisie[0] == '\0') {
                printf(ROUGE_GRAS "❌ Nom vide.\n" REINITIALISER);
                printf(JAUNE_GRAS "(Rappel : 'r' retour, 'm' menu.)\n" REINITIALISER);
                continue;
            }

            char nomRecherche[TAILLE_NOM]; // Vérifiez TAILLE_NOM
            snprintf(nomRecherche, sizeof(nomRecherche), "%.*s", (int)(sizeof(nomRecherche)-1), tampon_saisie);

            f_entree = fopen("data/animaux/animaux.txt", "r");
            if (!f_entree) {
                printf(ROUGE_GRAS "❌ Erreur ouverture fichier.\n" REINITIALISER);
                return;
            }

            while (fgets(ligne, sizeof(ligne), f_entree) && nb_correspondances < MAX_ANIMAUX) { 
                if (sscanf(ligne, "%d;%49[^;];", &animal_temporaire.id, animal_temporaire.nom) == 2) {
                    if (comparer(animal_temporaire.nom, nomRecherche)) {
                        commentaire_temp_str[0] = '\0'; // Vérifiez TAILLE_COMM pour commentaire_temp_str
                        int lus = sscanf(ligne, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                                         &correspondances[nb_correspondances].id,
                                         correspondances[nb_correspondances].nom,
                                         espece_temp_str,
                                         &correspondances[nb_correspondances].annee_naissance,
                                         &correspondances[nb_correspondances].poids,
                                         commentaire_temp_str);

                        if (lus >= 5) {
                            correspondances[nb_correspondances].espece = chaineVersEspece(espece_temp_str);
                            commentaire_temp_str[sizeof(commentaire_temp_str)-1] = '\0';
                            snprintf(correspondances[nb_correspondances].commentaire, TAILLE_COMM, "%s", commentaire_temp_str); 
                            enleverSautLigne(correspondances[nb_correspondances].commentaire, TAILLE_COMM); 
                            nb_correspondances++;
                        }
                    }
                }
            }
            fclose(f_entree);
            f_entree = NULL;

            if (nb_correspondances == 0) {
                printf(JAUNE_GRAS "⚠️ Aucun trouvé : '%s'.\n" REINITIALISER, nomRecherche);
                printf(JAUNE_GRAS "(Rappel : 'r' retour, 'm' menu.)\n" REINITIALISER);
                continue;
            } else if (nb_correspondances == 1) {
                id_a_adopter = correspondances[0].id;
                printf(VERT_GRAS "✅ Un seul trouvé : '%s' (ID : %d).\n" REINITIALISER, correspondances[0].nom, id_a_adopter);
            } else { // > 1
                printf(JAUNE_GRAS "⚠️ Plusieurs trouvés ('%s'):\n" REINITIALISER, nomRecherche);
                for (int i = 0; i < nb_correspondances; i++) {
                    Animal *a = &correspondances[i]; 
                    int age = calculerAgeAdopter(a->annee_naissance);

                    printf(VERT_GRAS "---\n" REINITIALISER);
                    printf(JAUNE_GRAS " ID : %d\n" REINITIALISER, a->id);
                    printf(ROSE " Nom : %s\n" REINITIALISER, a->nom);
                    printf(VERT " Espèce : %s\n" REINITIALISER, especeVersChaine(a->espece));

                    if (age == -1) {
                        printf(CYAN " Âge : Err\n" REINITIALISER);
                    } else if (age == -2) {
                        printf(CYAN " Âge : Inv\n" REINITIALISER);
                    } else {
                        printf(CYAN " Âge : %d ans\n" REINITIALISER, age);
                    }

                    printf(ROUGE " Poids : %.2f kg\n" REINITIALISER, a->poids);
                    printf(BLANC " Commentaire : %s\n" REINITIALISER, a->commentaire[0] == '\0' ? "Aucun" : a->commentaire);
                }

                printf(VERT_GRAS "------------------------------------\n" REINITIALISER);

                while (id_a_adopter == -1) {
                    printf(CYAN_GRAS "\nLequel adopter ?\n" REINITIALISER);
                    printf(JAUNE_GRAS "Entrez ID exact ('r' retour, 'm' menu) : " REINITIALISER);

                    if (!fgets(tampon_saisie, sizeof(tampon_saisie), stdin)) {
                        return;
                    }
                    enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));

                    if (tampon_saisie[0] == 'm' && tampon_saisie[1] == '\0') {
                        return;
                    }
                    if (tampon_saisie[0] == 'r' && tampon_saisie[1] == '\0') {
                        break;
                    }

                    int id_temp;
                    if (sscanf(tampon_saisie, "%d", &id_temp) == 1) {
                        int id_valide = 0;
                        for (int i = 0; i < nb_correspondances; i++) {
                            if (correspondances[i].id == id_temp) {
                                id_a_adopter = id_temp;
                                id_valide = 1;
                                break;
                            }
                        }
                        if (!id_valide) {
                            printf(ROUGE_GRAS "❌ ID pas listé.\n" REINITIALISER);
                        }
                    } else {
                        printf(ROUGE_GRAS "❌ ID invalide.\n" REINITIALISER);
                        printf(JAUNE_GRAS "(Rappel : 'r' retour, 'm' menu.)\n" REINITIALISER);
                    }
                }
                if (id_a_adopter == -1) { 
                    continue;
                }
            }
        }

        if (id_a_adopter != -1) {
            int trouve_final = 0;
            char nomTrouveFinal[TAILLE_NOM] = ""; 

            f_entree = fopen("data/animaux/animaux.txt", "r");
            f_sortie = fopen("data/animaux/animaux_temp.txt", "w");

            if (!f_entree || !f_sortie) {
                printf(ROUGE_GRAS "❌ Erreur fichiers adoption.\n" REINITIALISER);
                if (f_entree) fclose(f_entree);
                if (f_sortie) fclose(f_sortie);
                remove("data/animaux/animaux_temp.txt");
                return;
            }

            while (fgets(ligne, sizeof(ligne), f_entree)) {
                int idCourant;
                if (sscanf(ligne, "%d;", &idCourant) == 1) {
                    if (idCourant == id_a_adopter) {
                        trouve_final = 1;
                        sscanf(ligne, "%*d;%49[^;];", nomTrouveFinal); 
                    } else {
                        fprintf(f_sortie, "%s", ligne);
                    }
                } else {
                    size_t len = longueurChaine(ligne);
                    if (len > 0) {
                         fprintf(f_sortie, "%s", ligne);
                        
                    }
                }
            }

            fclose(f_entree);
            fclose(f_sortie);

            if (trouve_final) {
                if (remove("data/animaux/animaux.txt") != 0) {
                    printf(ROUGE_GRAS "❌ Erreur suppression.\n" REINITIALISER);
                    remove("data/animaux/animaux_temp.txt");
                } else if (rename("data/animaux/animaux_temp.txt", "data/animaux/animaux.txt") != 0) {
                    printf(ROUGE_GRAS "❌ Erreur renommage.\n" REINITIALISER);
                    printf(JAUNE_GRAS "Données sauvegardées dans 'data/animaux/animaux_temp.txt'.\n" REINITIALISER);
                } else {
                    printf(VERT_GRAS "✅ Adoption de %s (ID : %d) réussie !\n" REINITIALISER, nomTrouveFinal, id_a_adopter);
                }
            } else {
                printf(JAUNE_GRAS "⚠️ Erreur interne : ID %d non retrouvé lors de la réécriture du fichier.\n" REINITIALISER, id_a_adopter);
                remove("data/animaux/animaux_temp.txt");
            }
            adoption_terminee = 1; // L'adoption est terminée, on sort de la boucle principale.
            printf("\nAppuyez sur Entrée...");
            nettoyerTampon(); // Assurez-vous que cette fonction est bien définie et vide le tampon d'entrée.
        }
    } 
} 
