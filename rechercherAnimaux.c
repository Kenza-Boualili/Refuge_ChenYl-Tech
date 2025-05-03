// rechercherAnimaux.c (Avec option 'r')
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// S'assurer que stdio.h est inclus avant stddef.h si utils.h l'inclut pour size_t
#include "animal.h"
#include "comparer.h"
#include "retourmenu.h" // Pour demanderRetourMenu (si on le garde au début)
#include "utils.h"      // Pour nettoyerBuffer, enleverNewline, compareStr

#define RED_BOLD    "\033[1;31m"
#define YELLOW_BOLD "\033[1;33m"
#define BLUE_BOLD   "\033[1;34m"
#define CYAN_BOLD   "\033[1;36m"
#define RESET       "\033[0m"


// ... (calculerAge, menuTypeAge, afficherResultat restent identiques) ...
static int calculerAge(int annee_naissance) {
    time_t maintenant = time(NULL);
    struct tm *tm = localtime(&maintenant);
    return (tm->tm_year + 1900) - annee_naissance;
}

// menuTypeAge modifié pour accepter 'r' ou 'm'
static int menuTypeAgeModifie() {
    char buffer[10];
    int choix_num = 0;

    printf("\n\033[1;35mType d'âge :\033[0m\n");
    printf("1. Jeune \033[1;32m(<2 ans)\033[0m 🐶\n");
    printf("2. Adulte \033[1;33m(2 à 10 ans)\033[0m 🦁\n");
    printf("3. Sénior \033[1;31m(>10 ans)\033[0m 🦓\n");
    printf("4. Âge exact \033[1;34m(entrer un âge)\033[0m 🎯\n");
    printf(" Tapez 'r' pour retour choix mode, 'm' pour menu principal.\n");
    printf("\033[1;36mChoix : \033[0m");

    if (!fgets(buffer, sizeof(buffer), stdin)) return -2; // Erreur de lecture -> quitter
    enleverNewline(buffer, sizeof(buffer));

    if (buffer[0] == 'm' && buffer[1] == '\0') return -1; // Code pour menu principal
    if (buffer[0] == 'r' && buffer[1] == '\0') return 0;  // Code pour retour/recommencer

    if (sscanf(buffer, "%d", &choix_num) == 1 && choix_num >= 1 && choix_num <= 4) {
        return choix_num; // Retourne 1, 2, 3 ou 4
    }

    printf(RED_BOLD "Choix de type d'âge invalide.\n" RESET);
    return 0; // Retour invalide pour redemander
}


static void afficherResultat(const Animal *a, int age) {
    printf("\n" BLUE_BOLD "=== Animal trouvé ===\n" RESET);
    printf(YELLOW_BOLD "ID" RESET ": %d\n", a->id);
    printf("\033[1;35mNom" RESET ": %s\n", a->nom); // Violet
    printf("\033[1;32mEspèce" RESET ": %s 🐾\n", especeToStr(a->espece)); // Vert
    printf(CYAN_BOLD "Âge" RESET ": %d ans 🎂\n", age);
    printf(RED_BOLD "Poids" RESET ": %.2f kg ⚖️\n", a->poids);
    printf("\033[1;37mCommentaire" RESET ": %s\n", a->commentaire[0] == '\0' ? "Aucun" : a->commentaire); // Blanc
}


void rechercherAnimaux() {
    FILE *f = NULL;
    int choix_mode;
    char input_buffer[256]; // Buffer plus grand pour les noms/commentaires
    Animal a; // Déclarer ici pour visibilité dans la boucle
    char buffer_espece[50];
    char buffer_commentaire[TAILLE_COMM];

    // Boucle principale pour permettre de recommencer la recherche
    while (1) {
        f = fopen("animaux/animaux.txt", "r");
        if (!f) {
            printf(RED_BOLD "❌ Aucun animal enregistré ou fichier inaccessible !\n" RESET);
            return; // Quitte la fonction recherche si pas de fichier
        }

        printf("\n" CYAN_BOLD "=== Mode de recherche ===\n" RESET);
        printf("1. Par ID 🔍\n");
        printf("2. Par nom 📛\n");
        printf("3. Par âge 🕒\n");
        printf(" Tapez 'm' pour retourner au menu principal.\n");
        printf(CYAN_BOLD "Choix : " RESET);

        // Lire le choix du mode
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { fclose(f); return; } // Quitte si erreur lecture
        enleverNewline(input_buffer, sizeof(input_buffer));

        // Gérer 'm' pour menu principal
        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
            fclose(f);
            return; // Retourne au menu principal (fin fonction)
        }

        // Essayer de convertir en choix numérique
        if (sscanf(input_buffer, "%d", &choix_mode) != 1 || choix_mode < 1 || choix_mode > 3) {
            printf(RED_BOLD "Choix de mode invalide. Veuillez réessayer.\n" RESET);
            fclose(f);
            continue; // Recommence la boucle while -> redemande le mode
        }

        // Logique interne basée sur le choix du mode
        int trouve = 0;
        int action_terminee = 0; // Pour savoir si on doit sortir de la boucle après une action

        switch (choix_mode) {
            case 1: { // Recherche par ID
                printf(YELLOW_BOLD "ID à rechercher (ou 'r' pour retour choix mode, 'm' pour menu) : " RESET);
                if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { fclose(f); return; }
                enleverNewline(input_buffer, sizeof(input_buffer));

                if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { fclose(f); return; }
                if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
                    fclose(f);
                    continue; // Recommence la boucle while -> redemande le mode
                }

                int idRecherche;
                if (sscanf(input_buffer, "%d", &idRecherche) != 1) {
                    printf(RED_BOLD "ID invalide.\n" RESET);
                    fclose(f);
                    continue; // Recommence la boucle while -> redemande le mode
                }

                // Effectuer la recherche
                while (fscanf(f, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                              &a.id, a.nom, buffer_espece, &a.annee_naissance,
                              &a.poids, buffer_commentaire) == 6) {
                    if (a.id == idRecherche) {
                        a.espece = strToEspece(buffer_espece);
                        snprintf(a.commentaire, TAILLE_COMM, "%s", buffer_commentaire);
                        enleverNewline(a.commentaire, TAILLE_COMM);
                        afficherResultat(&a, calculerAge(a.annee_naissance));
                        trouve = 1;
                        break;
                    }
                }
                if (!trouve) printf(YELLOW_BOLD "Aucun animal trouvé avec l'ID %d.\n" RESET, idRecherche);
                action_terminee = 1; // On a fini cette recherche par ID
                break; // Sortir du switch
            } // Fin case 1

            case 2: { // Recherche par Nom
                printf(YELLOW_BOLD "Nom à rechercher (ou 'r' pour retour choix mode, 'm' pour menu) : " RESET);
                 if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { fclose(f); return; }
                 enleverNewline(input_buffer, sizeof(input_buffer));

                 if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { fclose(f); return; }
                 if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
                     fclose(f);
                     continue; // Recommence la boucle while -> redemande le mode
                 }
                 if (input_buffer[0] == '\0') { // Nom vide
                      printf(RED_BOLD "Le nom ne peut être vide.\n" RESET);
                      fclose(f);
                      continue; // Recommence la boucle while -> redemande le mode
                 }
                 // Conserver le nom recherché
                 char nomRecherche[TAILLE_NOM];
                 // Utilise %.*s pour limiter explicitement le nombre de caractères copiés
snprintf(nomRecherche, sizeof(nomRecherche), "%.*s", (int)(sizeof(nomRecherche) - 1), input_buffer);

                // Effectuer la recherche
                 while (fscanf(f, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                               &a.id, a.nom, buffer_espece, &a.annee_naissance,
                               &a.poids, buffer_commentaire) == 6) {
                     if (comparer(a.nom, nomRecherche)) { // utiliser comparer.h/comparer.c
                         a.espece = strToEspece(buffer_espece);
                         snprintf(a.commentaire, TAILLE_COMM, "%s", buffer_commentaire);
                         enleverNewline(a.commentaire, TAILLE_COMM);
                         afficherResultat(&a, calculerAge(a.annee_naissance));
                         trouve = 1;
                     }
                 }
                 if (!trouve) printf(YELLOW_BOLD "Aucun animal trouvé avec le nom '%s'.\n" RESET, nomRecherche);
                 action_terminee = 1;
                 break; // Sortir du switch
            } // Fin case 2

            case 3: { // Recherche par Age
                int typeAge = menuTypeAgeModifie(); // Utilise la version modifiée

                if (typeAge == -1) { fclose(f); return; } // 'm' choisi dans le sous-menu
                if (typeAge == 0)  { fclose(f); continue; } // 'r' choisi dans le sous-menu, ou erreur

                int ageRecherche = 0;
                if (typeAge == 4) { // Age exact
                     printf(YELLOW_BOLD "Âge exact à rechercher (ou 'r' pour retour choix type âge, 'm' pour menu) : " RESET);
                     if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { fclose(f); return; }
                     enleverNewline(input_buffer, sizeof(input_buffer));

                     if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { fclose(f); return; }
                     if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
                         // Ici 'r' devrait probablement relancer le sous-menu typeAge,
                         // ce qui complique la boucle. Pour l'instant, on retourne au choix de mode.
                         printf("\nRetour au choix du mode de recherche...\n");
                         fclose(f);
                         continue; // Recommence la boucle while -> redemande le mode
                     }

                     if (sscanf(input_buffer, "%d", &ageRecherche) != 1 || ageRecherche < 0) {
                         printf(RED_BOLD "Age invalide.\n" RESET);
                         fclose(f);
                         continue; // Recommence la boucle while -> redemande le mode
                     }
                }

                // Effectuer la recherche par âge
                while (fscanf(f, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                              &a.id, a.nom, buffer_espece, &a.annee_naissance,
                              &a.poids, buffer_commentaire) == 6) {
                    int age = calculerAge(a.annee_naissance);
                    if ((typeAge == 1 && age < 2) ||
                        (typeAge == 2 && age >= 2 && age <= 10) ||
                        (typeAge == 3 && age > 10) ||
                        (typeAge == 4 && age == ageRecherche))
                    {
                        a.espece = strToEspece(buffer_espece);
                        snprintf(a.commentaire, TAILLE_COMM, "%s", buffer_commentaire);
                        enleverNewline(a.commentaire, TAILLE_COMM);
                        afficherResultat(&a, age);
                        trouve = 1;
                    }
                }
                 if (!trouve) printf(YELLOW_BOLD "Aucun animal trouvé pour ce critère d'âge.\n" RESET);
                 action_terminee = 1;
                 break; // Sortir du switch
            } // Fin case 3

        } // Fin du switch(choix_mode)

        fclose(f); // Ferme le fichier après la tentative de recherche

        // Si une action a été effectuée (recherche ID/Nom/Age terminée), on quitte la fonction
        if (action_terminee) {
             // On pourrait demander ici si on veut faire une AUTRE recherche (o/n)
             // ou simplement retourner au menu principal. Retournons au menu.
             printf("\nRecherche terminée. Retour au menu principal.\n");
            return;
        }
        // Si on arrive ici, c'est qu'on a choisi 'r' ou une erreur s'est produite
        // et la boucle while(1) va recommencer.

    } // Fin de la boucle while(1)

} // Fin de la fonction rechercherAnimaux