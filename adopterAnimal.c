// adopterAnimal.c (Avec option 'r')
#include <stdio.h>
#include <stdlib.h>
#include "animal.h"
#include "retourmenu.h" // Pas utilisé directement ici
#include "utils.h"      // Pour enleverNewline

#define RED_BOLD    "\033[1;31m"
#define GREEN_BOLD  "\033[1;32m"
#define YELLOW_BOLD "\033[1;33m"
#define BLUE_BOLD   "\033[1;34m"
#define RESET       "\033[0m"

// Fonction helper pour calculer longueur chaîne sans string.h
size_t longueurChaineAdopter(const char *chaine) {
    size_t len = 0;
    while(chaine[len] != '\0') len++;
    return len;
}

void adopterAnimal() {
    FILE *f_in = NULL;  // Fichier original en lecture
    FILE *f_out = NULL; // Fichier temporaire en écriture
    char input_buffer[50];
    int idRecherche;
    int trouve;
    char ligne[512];
    int idCourant;
    char nomTrouve[TAILLE_NOM];

    // Boucle pour permettre de recommencer la saisie de l'ID
    while (1) {
        trouve = 0; // Réinitialiser 'trouve' à chaque tentative
        nomTrouve[0] = '\0'; // Réinitialiser nomTrouve

        printf(BLUE_BOLD "\n=== Adopter un Animal ===\n" RESET);

        f_in = fopen("animaux/animaux.txt", "r");
        if (!f_in) {
            printf(RED_BOLD "❌ Fichier animaux.txt introuvable ou inaccessible.\n" RESET);
            return; // Quitte la fonction si pas de fichier
        }

        printf(YELLOW_BOLD "Entrez l'ID de l'animal à adopter (ou 'r' pour recommencer, 'm' pour menu) : " RESET);
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { fclose(f_in); return; }
        enleverNewline(input_buffer, sizeof(input_buffer));

        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { fclose(f_in); return; } // Menu principal
        if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
            printf("\nRecommencement...\n");
            fclose(f_in);
            continue; // Recommence la boucle while(1) -> redemande ID
        }

        if (sscanf(input_buffer, "%d", &idRecherche) != 1) {
            printf(RED_BOLD "❌ ID invalide.\n" RESET);
            fclose(f_in);
            continue; // Recommence la boucle while(1) -> redemande ID
        }

        // Si l'ID est valide, on continue le processus d'adoption
        f_out = fopen("animaux/animaux_temp.txt", "w");
        if (!f_out) {
            printf(RED_BOLD "❌ Erreur lors de la création du fichier temporaire.\n" RESET);
            fclose(f_in);
            return; // Erreur critique, on quitte
        }

        // Logique de copie/filtrage
        while (fgets(ligne, sizeof(ligne), f_in)) {
            size_t len_ligne = longueurChaineAdopter(ligne);

            if (sscanf(ligne, "%d;", &idCourant) == 1) {
                if (idCourant == idRecherche) {
                    trouve = 1;
                    sscanf(ligne, "%*d;%49[^;];", nomTrouve); // Extrait le nom
                    // Ne pas écrire cette ligne dans f_out
                } else {
                    fprintf(f_out, "%s", ligne);
                }
            } else {
                 if (len_ligne > 1 || (len_ligne == 1 && ligne[0] != '\n' && ligne[0] != '\r')) {
                     fprintf(f_out, "%s", ligne); // Copie lignes mal formées aussi
                     printf(YELLOW_BOLD "⚠️ Ligne ignorée ou mal formatée copiée : %s" RESET, ligne);
                     if (ligne[len_ligne-1] != '\n') fprintf(f_out, "\n");
                 }
            }
        }

        fclose(f_in);  f_in = NULL;
        fclose(f_out); f_out = NULL;

        // Remplacement des fichiers ou suppression du temp
        if (trouve) {
            printf(GREEN_BOLD "✅ Animal '%s' (ID: %d) trouvé.\n" RESET, nomTrouve, idRecherche);
            if (remove("animaux/animaux.txt") != 0) {
                 printf(RED_BOLD "❌ Erreur: Impossible de supprimer animaux.txt.\n" RESET);
                 remove("animaux/animaux_temp.txt"); // Nettoyer
            } else if (rename("animaux/animaux_temp.txt", "animaux/animaux.txt") != 0) {
                 printf(RED_BOLD "❌ Erreur: Impossible de renommer animaux_temp.txt.\n" RESET);
                 printf(YELLOW_BOLD "   Données restantes dans 'animaux_temp.txt'.\n" RESET);
            } else {
                 printf(GREEN_BOLD "✅ L'animal ID %d (%s) a été adopté !\n" RESET, idRecherche, nomTrouve);
            }
            return; // Termine la fonction après l'adoption réussie (ou échec critique)
        } else {
            remove("animaux/animaux_temp.txt");
            printf(YELLOW_BOLD "⚠️ Aucun animal trouvé avec l'ID %d. Veuillez réessayer.\n" RESET, idRecherche);
            // La boucle while(1) va continuer pour redemander l'ID
            continue;
        }

    } // Fin while(1)

} // Fin fonction adopterAnimal