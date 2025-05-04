// src/ajouterAnimal.c (Chemins Corrigés)
#include "animal.h"
#include "id.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "retourmenu.h"

#define PINK        "\033[95m"
#define GREEN       "\033[92m"
#define CYAN        "\033[96m"
#define YELLOW      "\033[93m"
#define YELLOW_BOLD "\033[1;33m"
#define RED         "\033[91m"
#define RESET       "\033[0m"

void ajouterAnimal() {
    Animal a;
    char input_buffer[TAILLE_COMM];
    FILE *f = NULL;
    int annee_actuelle;

    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);
    annee_actuelle = tm_info.tm_year + 1900;

    while (1) {
        printf(PINK "\n🎉 --- Ajout d’un nouvel animal --- 🐾\n" RESET);
        printf(YELLOW "    (Tapez 'r' à tout moment pour recommencer, 'm' pour menu principal)\n" RESET);

        // --- Nom ---
        printf(CYAN "📛 Nom : " RESET);
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { return; }
        enleverNewline(input_buffer, sizeof(input_buffer));
        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { return; }
        if (input_buffer[0] == 'r' && input_buffer[1] == '\0') { 
            printf("\nRecommencement...\n"); continue; }
        if (input_buffer[0] == '\0') {
             printf(RED "Le nom ne peut pas être vide.\n" RESET);
             printf(YELLOW_BOLD "(Rappel : Tapez 'r' pour recommencer ou 'm' pour menu.)\n" RESET);
             continue;
        }
        snprintf(a.nom, sizeof(a.nom), "%.*s", (int)(sizeof(a.nom) - 1), input_buffer);

        // --- Espèce ---
        a.espece = choisirEspece();

        // --- Année de naissance ---
        while (1) { /* ... (logique saisie année inchangée)... */
            printf(CYAN "📅 Année de naissance (entre 1980 et %d) : " RESET, annee_actuelle);
             if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { return; }
             enleverNewline(input_buffer, sizeof(input_buffer));
             if (input_buffer[0] == 'm' && input_buffer[1] == '\0') 
             { return; }
             if (input_buffer[0] == 'r' && input_buffer[1] == '\0') { 
                printf("\nRecommencement...\n"); 
                goto recommencer_ajout_externe_aj; 
            } // Utilise label spécifique
             if (sscanf(input_buffer, "%d", &a.annee_naissance) == 1 && a.annee_naissance >= 1980 && a.annee_naissance <= annee_actuelle) { 
                break; }
             else { 
                printf(RED "⚠️ Année invalide !\n" RESET); 
                printf(YELLOW_BOLD "(Rappel : 'r' recommencer, 'm' menu.)\n" RESET); }
        }

        // --- Poids ---
         while (1) { /* ... (logique saisie poids inchangée)... */
             printf(CYAN "⚖️ Poids (kg) (> 0 et < 1000) : " RESET);
             if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { return; }
             enleverNewline(input_buffer, sizeof(input_buffer));
             if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { return; }
             if (input_buffer[0] == 'r' && input_buffer[1] == '\0') { printf("\nRecommencement...\n"); goto recommencer_ajout_externe_aj; }
             float poids_temp;
             if (sscanf(input_buffer, "%f", &poids_temp) == 1 && poids_temp > 0 && poids_temp < 1000) { a.poids = poids_temp; break; }
             else { printf(RED "⚠️ Poids invalide !\n" RESET); printf(YELLOW_BOLD "(Rappel : 'r' recommencer, 'm' menu.)\n" RESET); }
         }

        // --- Commentaire ---
        printf(CYAN "🗒️ Commentaire (optionnel, 'r' recommencer, 'm' menu) : " RESET);
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { return; }
        enleverNewline(input_buffer, sizeof(input_buffer));
        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { return; }
        if (input_buffer[0] == 'r' && input_buffer[1] == '\0') { printf("\nRecommencement...\n"); continue; } // 'continue' ici suffit
        snprintf(a.commentaire, sizeof(a.commentaire), "%.*s", (int)(sizeof(a.commentaire) - 1), input_buffer);

        // --- Sauvegarde ---
        // *** CHEMIN CORRIGÉ ICI ***
        f = fopen("data/animaux/animaux.txt", "a");
        if (!f) { 
        printf(RED "❌ Erreur ouverture fichier '%s' !\n" RESET, "data/animaux/animaux.txt"); 
        return; }
        a.id = genererID();
        fprintf(f, "%d;%s;%s;%d;%.2f;%s\n", a.id, a.nom, especeToStr(a.espece), a.annee_naissance, a.poids, (a.commentaire[0] == '\0') ? "Aucun" : a.commentaire);
        fclose(f); f = NULL;

        printf(GREEN "✅ Animal #%d (%s) ajouté avec succès ! 🎊\n" RESET, a.id, a.nom);
        printf("\nAppuyez sur Entrée pour retourner au menu principal...");
        nettoyerBuffer();
        return;

    recommencer_ajout_externe_aj:; // Label spécifique au fichier
        // Pas besoin de gérer f ici car ouvert seulement à la fin
    } // Fin while(1)
}