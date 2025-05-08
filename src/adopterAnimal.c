#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "animal.h"
#include "retourmenu.h"
#include "utils.h"
#include "comparer.h"

#define ROUGE_GRAS     "\033[1;31m"
#define VERT_GRAS      "\033[1;32m"
#define JAUNE_GRAS     "\033[1;33m"
#define BLEU_GRAS      "\033[1;34m"
#define CYAN_GRAS      "\033[1;36m"

#define ROSE           "\033[1;35m"
#define VERT           "\033[1;32m"
#define CYAN           "\033[1;36m"
#define ROUGE          "\033[1;31m"
#define BLANC          "\033[1;37m"
#define REINITIALISER  "\033[0m"

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

    while (adoption_terminee == 0) {
        id_a_adopter = -1;
        nb_correspondances = 0;

        printf(BLEU_GRAS "\n=== Adopter un Animal ===\n" REINITIALISER);
        printf("Comment identifier l'animal ?\n1. Par ID\n Tapez 'm' pour menu principal.\n");
        printf(CYAN_GRAS "Choix : " REINITIALISER);

        if (fgets(tampon_saisie, sizeof(tampon_saisie), stdin) == NULL) {
            return;
        }

        enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));

        if (tampon_saisie[0] == 'm' && tampon_saisie[1] == '\0') {
            return;
        }

        if (sscanf(tampon_saisie, "%d", &choix_methode) != 1 || (choix_methode != 1)) {
            printf(ROUGE_GRAS "❌ Choix invalide (1).\n" REINITIALISER);
            continue;
        }

        if (choix_methode == 1) {
            printf(JAUNE_GRAS "Entrez l'ID ('r' retour, 'm' menu) : " REINITIALISER);
            if (fgets(tampon_saisie, sizeof(tampon_saisie), stdin) == NULL) {
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
        }

        f_entree = fopen("data/animaux/animaux.txt", "r");
        if (f_entree == NULL) {
            printf(ROUGE_GRAS "❌ Erreur ouverture fichier.\n" REINITIALISER);
            return;
        }

        while (fgets(ligne, sizeof(ligne), f_entree) != NULL && nb_correspondances < MAX_ANIMAUX) {
            int id_lu;
            char nom_temp[TAILLE_NOM];
            if (sscanf(ligne, "%d;%49[^;]", &id_lu, nom_temp) == 2) {
                if (id_lu == id_a_adopter) {
                    commentaire_temp_str[0] = '\0';
                    int lus = sscanf(ligne, "%d;%[^;];%[^;];%d;%f;%[^\n]",
                        &correspondances[nb_correspondances].id,
                        correspondances[nb_correspondances].nom,
                        espece_temp_str,
                        &correspondances[nb_correspondances].annee_naissance,
                        &correspondances[nb_correspondances].poids,
                        commentaire_temp_str);

                    if (lus >= 5) {
                        correspondances[nb_correspondances].espece = chaineVersEspece(espece_temp_str);
                        snprintf(correspondances[nb_correspondances].commentaire, TAILLE_COMM, "%s", commentaire_temp_str);
                        enleverSautLigne(correspondances[nb_correspondances].commentaire, TAILLE_COMM);
                        nb_correspondances++;
                    }
                    break;
                }
            }
        }

        fclose(f_entree);

        if (nb_correspondances == 0) {
            printf(JAUNE_GRAS "⚠️ Aucun animal trouvé avec l'ID %d.\n" REINITIALISER, id_a_adopter);
            continue;
        } else {
            Animal a = correspondances[0];
            int age = calculerAgeAdopter(a.annee_naissance);

            printf(VERT_GRAS "✅ Animal trouvé : '%s' (ID : %d).\n" REINITIALISER, a.nom, id_a_adopter);
            printf(VERT " Espèce : %s\n" REINITIALISER, especeVersChaine(a.espece));

            if (age == -1) {
                printf(CYAN " Âge : Err\n" REINITIALISER);
            } else if (age == -2) {
                printf(CYAN " Âge : Inv\n" REINITIALISER);
            } else {
                printf(CYAN " Âge : %d ans\n" REINITIALISER, age);
            }

            printf(ROUGE " Poids : %.2f kg\n" REINITIALISER, a.poids);
            printf(BLANC " Commentaire : %s\n" REINITIALISER, a.commentaire[0] == '\0' ? "Aucun" : a.commentaire);
        }

        int adoption_confirmee = 0;
        while (!adoption_confirmee) {
            printf(CYAN_GRAS "\nVoulez-vous adopter cet animal ? (O/N) : " REINITIALISER);
            if (fgets(tampon_saisie, sizeof(tampon_saisie), stdin) == NULL) {
                return;
            }
            enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));

            if (tampon_saisie[0] == 'O' || tampon_saisie[0] == 'o') {
                adoption_confirmee = 1;

                f_entree = fopen("data/animaux/animaux.txt", "r");
                f_sortie = fopen("data/animaux/animaux_temp.txt", "w");

                if (f_entree == NULL || f_sortie == NULL) {
                    printf(ROUGE_GRAS "❌ Erreur fichiers adoption.\n" REINITIALISER);
                    if (f_entree != NULL) { fclose(f_entree); }
                    if (f_sortie != NULL) { fclose(f_sortie); }
                    remove("data/animaux/animaux_temp.txt");
                    return;
                }

                while (fgets(ligne, sizeof(ligne), f_entree) != NULL) {
                    int idCourant;
                    if (sscanf(ligne, "%d;", &idCourant) == 1) {
                        if (idCourant != id_a_adopter) {
                            fprintf(f_sortie, "%s", ligne);
                        }
                    } else {
                        size_t longueur = longueurChaine(ligne);
                        if (longueur > 0) {
                            fprintf(f_sortie, "%s", ligne);
                        }
                    }
                }

                fclose(f_entree);
                fclose(f_sortie);

                if (remove("data/animaux/animaux.txt") != 0) {
                    printf(ROUGE_GRAS "❌ Erreur suppression.\n" REINITIALISER);
                    remove("data/animaux/animaux_temp.txt");
                } else if (rename("data/animaux/animaux_temp.txt", "data/animaux/animaux.txt") != 0) {
                    printf(ROUGE_GRAS "❌ Erreur renommage.\n" REINITIALISER);
                } else {
                    printf(VERT_GRAS "✅ Adoption réussie pour '%s' (ID : %d) !\n" REINITIALISER, correspondances[0].nom, id_a_adopter);
                }
            } else if (tampon_saisie[0] == 'N' || tampon_saisie[0] == 'n') {
                adoption_confirmee = 1;
                printf(JAUNE_GRAS "⚠️ Adoption annulée.\n" REINITIALISER);
            } else {
                printf(ROUGE_GRAS "❌ Réponse invalide. Entrez 'O' pour adopter ou 'N' pour annuler.\n" REINITIALISER);
            }
        }

        adoption_terminee = 1;
        printf("\nAppuyez sur Entrée...");
        nettoyerTampon();
    }
}

