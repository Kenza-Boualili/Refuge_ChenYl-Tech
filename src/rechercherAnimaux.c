#include <stdio.h>
#include <stdlib.h>
#include <time.h>       

#include "../include/animal.h"     
#include "../include/comparer.h"   
#include "../include/utils.h"     
#include "../include/affichage.h"  


#ifndef RESET 
#define RESET       "\033[0m"
#define GRAS_ROUGE  "\033[1;31m"
#define GRAS_VERT   "\033[1;32m"
#define GRAS_JAUNE  "\033[1;33m"
#define GRAS_BLEU   "\033[1;34m"
#define GRAS_CYAN   "\033[1;36m"
#define GRAS_MAUVE  "\033[1;35m"

#define GRAS_BLANC  "\033[1;37m"
#endif

#define CHEMIN_FICHIER_ANIMAUX "data/animaux/animaux.txt"

#define SCANF_NOM_WIDTH "49"   
#define SCANF_COMM_WIDTH "255"  
#define SCANF_ESPECE_WIDTH "49" 


static int calculerAge(int annee_naissance) {
    if (annee_naissance <= 0) {
        return -2;
    }
    time_t maintenant = time(NULL);
    if (maintenant == ((time_t)-1)) {
         perror(GRAS_ROUGE "Erreur time() dans calculerAge" RESET);
         return -1;
    }
    struct tm *tm_local = localtime(&maintenant);
    if (tm_local == NULL) {
        fprintf(stderr, GRAS_ROUGE "Erreur localtime() dans calculerAge\n" RESET);
        return -1; 
    }
    int annee_actuelle = tm_local->tm_year + 1900;
    if (annee_naissance > annee_actuelle || annee_naissance < 1950) { 
        return -2; 
    }
    return annee_actuelle - annee_naissance;
}

void rechercherAnimaux() {
    FILE *fichier = NULL;
    int choix_mode_recherche;
    char buffer_lecture[512];
    Animal animal_courant;
    char buffer_espece_str[50];
    char buffer_commentaire_str[TAILLE_COMM];


    while (1) {
        printf("\n" GRAS_CYAN "--- 🔍 Mode Recherche 🐾 ---\n" RESET);
       
        printf(GRAS_BLANC "1. Par ID unique 🆔\n" RESET);    // Blanc
        printf(GRAS_MAUVE "2. Par Nom (affiche tous les matchs) 📛\n" RESET); // Mauve
        printf(GRAS_JAUNE  "3. Par Catégorie d'âge ⏳\n" RESET); // Jaune
        // Instructions
        printf(GRAS_JAUNE "➡️ Tapez 'm' pour retourner au menu principal.\n" RESET);
        printf(GRAS_BLEU "Votre choix : " RESET);

        if (!fgets(buffer_lecture, sizeof(buffer_lecture), stdin)) {
            fprintf(stderr, GRAS_ROUGE "\nErreur fatale lecture stdin.\n" RESET);
            return;
        }
        enleverNewline(buffer_lecture, sizeof(buffer_lecture));

        // Option 'm'
        if ((buffer_lecture[0] == 'm' || buffer_lecture[0] == 'M') && buffer_lecture[1] == '\0') {
             printf(GRAS_VERT "\nRetour au menu principal...\n" RESET);
             return;
        }

        // Validation choix
        if (sscanf(buffer_lecture, "%d", &choix_mode_recherche) != 1 || choix_mode_recherche < 1 || choix_mode_recherche > 3) {
            printf(GRAS_ROUGE "❌ Choix invalide. Entrez 1, 2, 3 ou 'm'.\n" RESET);
            continue;
        }

        fichier = fopen(CHEMIN_FICHIER_ANIMAUX, "r");
        if (!fichier) {
            fprintf(stderr, GRAS_ROUGE "\n❌ Erreur ouverture fichier '%s': " RESET, CHEMIN_FICHIER_ANIMAUX);
            perror("");
            printf(GRAS_JAUNE "   Vérifiez existence et permissions.\n" RESET);
            printf(GRAS_JAUNE "Appuyez sur Entrée..." RESET);
            nettoyerBuffer();
            continue;
        }

        int trouve = 0;
        int action_terminee = 0;
        int ligne_actuelle; 
        switch (choix_mode_recherche) {

            case 1: {
                printf(GRAS_BLEU "\nRecherche par ID 🆔\n" RESET);
                printf(GRAS_JAUNE "➡️ ID exact ('r' retour, 'm' menu) : " RESET);

                if (!fgets(buffer_lecture, sizeof(buffer_lecture), stdin)) { fclose(fichier); return; }
                enleverNewline(buffer_lecture, sizeof(buffer_lecture));

                if ((buffer_lecture[0] == 'm' || buffer_lecture[0] == 'M') && buffer_lecture[1] == '\0') { fclose(fichier); return; }
                if ((buffer_lecture[0] == 'r' || buffer_lecture[0] == 'R') && buffer_lecture[1] == '\0') { fclose(fichier); continue; }

                int idRecherche;
                if (sscanf(buffer_lecture, "%d", &idRecherche) != 1 || idRecherche <= 0) {
                    printf(GRAS_ROUGE "❌ ID invalide (nombre positif requis).\n" RESET);
                    fclose(fichier); continue;
                }

                printf(GRAS_VERT "Recherche ID %d...\n" RESET, idRecherche);
                ligne_actuelle = 0; 

                while (fgets(buffer_lecture, sizeof(buffer_lecture), fichier)) {
                    ligne_actuelle++;
                    buffer_commentaire_str[0] = '\0';
                    int champs_lus = sscanf(buffer_lecture, "%d;%" SCANF_NOM_WIDTH "[^;];%" SCANF_ESPECE_WIDTH "[^;];%d;%f;%" SCANF_COMM_WIDTH "[^\n]",
                               &animal_courant.id, animal_courant.nom, buffer_espece_str,
                               &animal_courant.annee_naissance, &animal_courant.poids, buffer_commentaire_str);

                    if (champs_lus >= 5) {
                        if (animal_courant.id == idRecherche) {
                            animal_courant.espece = strToEspece(buffer_espece_str);
                            snprintf(animal_courant.commentaire, TAILLE_COMM, "%s", buffer_commentaire_str);
                            enleverNewline(animal_courant.commentaire, TAILLE_COMM);
                            int age = calculerAge(animal_courant.annee_naissance);
                            afficherResultat(&animal_courant, age);
                            trouve = 1;
                            break;
                        }
                    } else if (buffer_lecture[0] != '\n' && buffer_lecture[0] != '\0') {
                        printf(GRAS_JAUNE "⚠️ Ligne %d mal formatée ignorée (Recherche ID).\n" RESET, ligne_actuelle);
                    }
                }

                if (!trouve) {
                    printf(GRAS_JAUNE "❓ ID %d non trouvé.\n" RESET, idRecherche);
                }
                action_terminee = 1;
                break; 
            }

            case 2: {
                printf(GRAS_BLEU "\nRecherche par Nom 📛\n" RESET);
                printf(GRAS_JAUNE "➡️ Nom ('r' retour, 'm' menu) : " RESET);

                if (!fgets(buffer_lecture, sizeof(buffer_lecture), stdin)) { fclose(fichier); return; }
                enleverNewline(buffer_lecture, sizeof(buffer_lecture));

                if ((buffer_lecture[0] == 'm' || buffer_lecture[0] == 'M') && buffer_lecture[1] == '\0') { fclose(fichier); return; }
                if ((buffer_lecture[0] == 'r' || buffer_lecture[0] == 'R') && buffer_lecture[1] == '\0') { fclose(fichier); continue; }

                if (buffer_lecture[0] == '\0') {
                    printf(GRAS_ROUGE "❌ Nom vide.\n" RESET);
                    fclose(fichier); continue;
                }

                char nomRecherche[TAILLE_NOM];
                snprintf(nomRecherche, TAILLE_NOM, "%.*s", (int)(TAILLE_NOM - 1), buffer_lecture);

                printf(GRAS_VERT "Recherche '%s'...\n" RESET, nomRecherche);
                ligne_actuelle = 0; 

                while (fgets(buffer_lecture, sizeof(buffer_lecture), fichier)) {
                    ligne_actuelle++;
                    buffer_commentaire_str[0] = '\0';
                    int champs_lus = sscanf(buffer_lecture, "%d;%" SCANF_NOM_WIDTH "[^;];%" SCANF_ESPECE_WIDTH "[^;];%d;%f;%" SCANF_COMM_WIDTH "[^\n]",
                               &animal_courant.id, animal_courant.nom, buffer_espece_str,
                               &animal_courant.annee_naissance, &animal_courant.poids, buffer_commentaire_str);

                     if (champs_lus >= 5) {
                        if (comparer(animal_courant.nom, nomRecherche)) {
                        
                            animal_courant.espece = strToEspece(buffer_espece_str);
                    
                            snprintf(animal_courant.commentaire, TAILLE_COMM, "%s", buffer_commentaire_str);
                         
                            enleverNewline(animal_courant.commentaire, TAILLE_COMM);
                           
                            int age = calculerAge(animal_courant.annee_naissance);
                           
                            afficherResultat(&animal_courant, age);
                        
                            trouve++;
                        }
                    } else if (buffer_lecture[0] != '\n' && buffer_lecture[0] != '\0') {
                         printf(GRAS_JAUNE "⚠️ Ligne %d mal formatée ignorée (Recherche Nom).\n" RESET, ligne_actuelle);
                    }
                } 

                if (trouve == 0) {
                    printf(GRAS_JAUNE "❓ Nom '%s' non trouvé.\n" RESET, nomRecherche);
                } else {
                    printf(GRAS_VERT "%d correspondance(s) pour '%s'.\n" RESET, trouve, nomRecherche);
                }
                action_terminee = 1;
                break; // Fin case 2
            }

            case 3: {
                 printf(GRAS_BLEU "\nRecherche par Catégorie d'Âge ⏳\n" RESET);
                 printf(GRAS_CYAN   "1. Jeune (moins de 2 ans) 🍼\n" RESET);
                 printf(GRAS_VERT   "2. Adulte (2 à 10 ans) 🧑\n" RESET);
                 printf(GRAS_MAUVE  "3. Senior (plus de 10 ans) 👴\n" RESET);
                 printf(GRAS_JAUNE "➡️ Catégorie ('r' retour, 'm' menu) : " RESET);

                if (!fgets(buffer_lecture, sizeof(buffer_lecture), stdin)) { fclose(fichier); return; }
                enleverNewline(buffer_lecture, sizeof(buffer_lecture));

                if ((buffer_lecture[0] == 'm' || buffer_lecture[0] == 'M') && buffer_lecture[1] == '\0') { fclose(fichier); return; }
                if ((buffer_lecture[0] == 'r' || buffer_lecture[0] == 'R') && buffer_lecture[1] == '\0') { fclose(fichier); continue; }

                int categorieChoisie;
                if (sscanf(buffer_lecture, "%d", &categorieChoisie) != 1 || categorieChoisie < 1 || categorieChoisie > 3) {
                    printf(GRAS_ROUGE "❌ Catégorie invalide (1, 2 ou 3).\n" RESET);
                    fclose(fichier); continue;
                }

                const char* nomCategorie = "";
                if(categorieChoisie == 1) nomCategorie = "Jeune (< 2 ans)";
                else if(categorieChoisie == 2) nomCategorie = "Adulte (2-10 ans)";
                else nomCategorie = "Senior (> 10 ans)";

                printf(GRAS_VERT "Recherche catégorie '%s'...\n" RESET, nomCategorie);
                ligne_actuelle = 0; 

                 while (fgets(buffer_lecture, sizeof(buffer_lecture), fichier)) {
                    ligne_actuelle++;
                    buffer_commentaire_str[0] = '\0';
                    int champs_lus = sscanf(buffer_lecture, "%d;%" SCANF_NOM_WIDTH "[^;];%" SCANF_ESPECE_WIDTH "[^;];%d;%f;%" SCANF_COMM_WIDTH "[^\n]",
                               &animal_courant.id, animal_courant.nom, buffer_espece_str,
                               &animal_courant.annee_naissance, &animal_courant.poids, buffer_commentaire_str);

                    if (champs_lus >= 5) {
                        int age = calculerAge(animal_courant.annee_naissance);
                        int correspond = 0;
                        if (age >= 0) {
                             switch (categorieChoisie) {
                                case 1: if (age < 2)  correspond = 1; break;
                                case 2: if (age >= 2 && age <= 10) correspond = 1; break;
                                case 3: if (age > 10) correspond = 1; break;
                             }
                        }
                        if (correspond) {
                             animal_courant.espece = strToEspece(buffer_espece_str);
                             snprintf(animal_courant.commentaire, TAILLE_COMM, "%s", buffer_commentaire_str);
                             enleverNewline(animal_courant.commentaire, TAILLE_COMM);
                             afficherResultat(&animal_courant, age);
                             trouve++;
                        }
                    } else if (buffer_lecture[0] != '\n' && buffer_lecture[0] != '\0') {
                         printf(GRAS_JAUNE "⚠️ Ligne %d mal formatée ignorée (Recherche Age).\n" RESET, ligne_actuelle);
                    }
                }

                if (trouve == 0) {
                     printf(GRAS_JAUNE "❓ Aucun animal trouvé catégorie '%s'.\n" RESET, nomCategorie);
                } else {
                    printf(GRAS_VERT "%d animal(aux) trouvé(s) catégorie '%s'.\n" RESET, trouve, nomCategorie);
                }
                action_terminee = 1;
                break; // Fin case 3
            }

        } 
        fclose(fichier);
        fichier = NULL;

        if (action_terminee) {
            printf(GRAS_JAUNE "\nAppuyez sur Entrée pour revenir au menu de recherche..." RESET);
            nettoyerBuffer();
         
        }

    } 
}


