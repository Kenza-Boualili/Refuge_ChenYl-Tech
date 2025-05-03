// ajouterAnimal.c (Avec option 'r')
#include "animal.h"
#include "id.h"
#include <stdio.h>  // Pour snprintf, fgets, printf, FILE, etc.
#include <stdlib.h> // Pour exit ou autres si besoin
#include <time.h>   // Pour la validation de l'année
#include "utils.h"  // Pour nettoyerBuffer, enleverNewline
#include "retourmenu.h" // Pas vraiment utilisé ici, 'm' est géré localement

#define PINK    "\033[95m"
#define GREEN   "\033[92m"
#define CYAN    "\033[96m"
#define YELLOW  "\033[93m"
#define RED     "\033[91m"
#define RESET   "\033[0m"

void ajouterAnimal() {
    Animal a; // Déclarée ici pour être visible dans toute la fonction/boucle
    char input_buffer[TAILLE_COMM]; // Buffer assez grand pour nom et commentaire
    FILE *f = NULL; // Initialiser le pointeur de fichier
    int annee_actuelle; // Calculée une fois

    // Calculer l'année actuelle
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);
    annee_actuelle = tm_info.tm_year + 1900;

    // Boucle pour permettre de recommencer
    while (1) {
        printf(PINK "\n🎉 --- Ajout d’un nouvel animal --- 🐾\n" RESET);
        printf(YELLOW "    (Tapez 'r' à tout moment pour recommencer, 'm' pour menu principal)\n" RESET);

        // --- Nom ---
        printf(CYAN "📛 Nom : " RESET);
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { return; } // Quitter si erreur lecture
        enleverNewline(input_buffer, sizeof(input_buffer));
        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { return; } // Menu principal
        if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
            printf("\nRecommencement de l'ajout...\n");
            continue; // Recommence la boucle while(1)
        }
        if (input_buffer[0] == '\0') { // Nom vide
             printf(RED "Le nom ne peut pas être vide.\n" RESET);
             continue; // Recommence la boucle while(1)
        }
        // Copie sûre dans la structure animal
        snprintf(a.nom, sizeof(a.nom), "%.*s", (int)(sizeof(a.nom) - 1), input_buffer);


        // --- Espèce ---
        // choisirEspece() ne gère pas 'r'/'m', on la garde simple
        // Si on voulait gérer 'r'/'m' ici, il faudrait refaire choisirEspece
        a.espece = choisirEspece();
        // On pourrait ajouter une vérification après pour 'r'/'m' si nécessaire


        // --- Année de naissance ---
        while (1) { // Boucle interne pour redemander l'année si invalide
            printf(CYAN "📅 Année de naissance (entre 1980 et %d) : " RESET, annee_actuelle);
             if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { return; }
             enleverNewline(input_buffer, sizeof(input_buffer));
             if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { return; }
             if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
                 printf("\nRecommencement de l'ajout...\n");
                 goto recommencer_ajout; // Utilise goto pour sortir de la boucle interne et recommencer l'externe
             }

             if (sscanf(input_buffer, "%d", &a.annee_naissance) == 1 &&
                 a.annee_naissance >= 1980 && a.annee_naissance <= annee_actuelle) {
                 break; // Sort de la boucle de saisie de l'année
             } else {
                 printf(RED "⚠️ Année invalide !\n" RESET);
                 // Reste dans la boucle interne pour redemander l'année
             }
        }

        // --- Poids ---
         while (1) { // Boucle interne pour poids
             printf(CYAN "⚖️ Poids (kg) (> 0 et < 1000) : " RESET);
             if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { return; }
             enleverNewline(input_buffer, sizeof(input_buffer));
             if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { return; }
             if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
                 printf("\nRecommencement de l'ajout...\n");
                 goto recommencer_ajout;
             }

             float poids_temp;
             if (sscanf(input_buffer, "%f", &poids_temp) == 1 &&
                 poids_temp > 0 && poids_temp < 1000) {
                 a.poids = poids_temp;
                 break; // Sort de la boucle de saisie du poids
             } else {
                 printf(RED "⚠️ Poids invalide !\n" RESET);
             }
         }

        // --- Commentaire ---
        printf(CYAN "🗒️ Commentaire (optionnel, tapez 'r' pour recommencer, 'm' pour menu) : " RESET);
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { return; }
        enleverNewline(input_buffer, sizeof(input_buffer));
        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { return; }
        if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
            printf("\nRecommencement de l'ajout...\n");
            goto recommencer_ajout; // Recommence l'ajout complet
        }
        // Copie sûre dans la structure animal
        snprintf(a.commentaire, sizeof(a.commentaire), "%.*s", (int)(sizeof(a.commentaire) - 1), input_buffer);


        // --- Sauvegarde ---
        f = fopen("animaux/animaux.txt", "a");
        if (!f) {
             printf(RED "❌ Erreur : impossible d'ouvrir le fichier pour sauvegarde !\n" RESET);
             return; // Quitte si erreur critique
        }

        a.id = genererID(); // Génère l'ID juste avant sauvegarde
        fprintf(f, "%d;%s;%s;%d;%.2f;%s\n",
                a.id, a.nom, especeToStr(a.espece), a.annee_naissance, a.poids,
                (a.commentaire[0] == '\0') ? "Aucun" : a.commentaire);
        fclose(f);
        f = NULL; // Remettre à NULL après fermeture

        printf(GREEN "✅ Animal #%d (%s) ajouté avec succès ! 🎊\n" RESET, a.id, a.nom);
        return; // Termine la fonction ajouterAnimal après succès

    recommencer_ajout:; // Label pour le goto (utilisé pour sortir des boucles internes)
        if (f) { // S'assurer que le fichier est fermé si on utilise goto
            fclose(f);
            f = NULL;
        }
        // La boucle while(1) va maintenant continuer
    } // Fin while(1)

} // Fin fonction ajouterAnimal