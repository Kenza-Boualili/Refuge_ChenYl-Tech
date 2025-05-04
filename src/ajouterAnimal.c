#include "../include/animal.h"
#include "../include/id.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/retourmenu.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

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
        printf(YELLOW "    (Tapez 'r' pour recommencer, 'm' pour menu principal)\n" RESET);

        printf(CYAN "📛 Nom : " RESET);
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
            return;
        }
        enleverNewline(input_buffer, sizeof(input_buffer));
        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
            return;
        }
        if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
            printf("\nRecommencement...\n");
            continue;
        }
        if (input_buffer[0] == '\0') {
            printf(RED "Le nom ne peut pas être vide.\n" RESET);
            printf(YELLOW_BOLD "(Rappel : Tapez 'r' pour recommencer ou 'm' pour menu.)\n" RESET);
            continue;
        }
        snprintf(a.nom, sizeof(a.nom), "%.*s", (int)(sizeof(a.nom) - 1), input_buffer);

        a.espece = choisirEspece();

        while (1) {
            printf(CYAN "📅 Année naissance (1980-%d) : " RESET, annee_actuelle);
            if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
                return;
            }
            enleverNewline(input_buffer, sizeof(input_buffer));
            if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
                return;
            }
            if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
                printf("\nRecommencement...\n");
                goto recommencer_ajout_complet;
            }
            if (sscanf(input_buffer, "%d", &a.annee_naissance) == 1 && a.annee_naissance >= 1980 && a.annee_naissance <= annee_actuelle) {
                break;
            } else {
                printf(RED "⚠️ Année invalide !\n" RESET);
                printf(YELLOW_BOLD "(Rappel: 'r'/'m')\n" RESET);
            }
        }

        while (1) {
            printf(CYAN "⚖️ Poids (kg) (>0, <1000) : " RESET);
            if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
                return;
            }
            enleverNewline(input_buffer, sizeof(input_buffer));
            if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
                return;
            }
            if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
                printf("\nRecommencement...\n");
                goto recommencer_ajout_complet;
            }
            float poids_temp;
            if (sscanf(input_buffer, "%f", &poids_temp) == 1 && poids_temp > 0 && poids_temp < 1000) {
                a.poids = poids_temp;
                break;
            } else {
                printf(RED "⚠️ Poids invalide !\n" RESET);
                printf(YELLOW_BOLD "(Rappel: 'r'/'m')\n" RESET);
            }
        }

        printf(CYAN "🗒️ Commentaire (opt., 'r'/'m') : " RESET);
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
            return;
        }
        enleverNewline(input_buffer, sizeof(input_buffer));
        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
            return;
        }
        if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
            printf("\nRecommencement...\n");
            continue;
        }
        snprintf(a.commentaire, sizeof(a.commentaire), "%.*s", (int)(sizeof(a.commentaire) - 1), input_buffer);

        printf("Vérification/Création des dossiers...\n");

        if (mkdir("data", 0755) != 0) {
            if (errno != EEXIST) {
                printf(RED "❌ Erreur création dossier 'data' !\n" RESET);
                perror("   Erreur système mkdir");
            }
        }
        if (mkdir("data/animaux", 0755) != 0) {
            if (errno != EEXIST) {
                printf(RED "❌ Erreur création dossier 'data/animaux' !\n" RESET);
                perror("   Erreur système mkdir");
            }
        }

        const char *chemin_fichier = "data/animaux/animaux.txt";
        printf("Ouverture de '%s' en mode ajout...\n", chemin_fichier);
        f = fopen(chemin_fichier, "a");
        if (!f) {
            printf(RED "❌ Erreur OUVERTURE fichier '%s' pour sauvegarde !\n" RESET, chemin_fichier);
            perror("   >>> Erreur système retournée par fopen");
            printf(YELLOW_BOLD "   Vérifiez les permissions du dossier 'data/animaux' !\n" RESET);
            printf(YELLOW_BOLD "   Vérifiez que vous lancez bien depuis 'vrai-code' avec ./bin/chenil\n" RESET);
            return;
        }

        a.id = genererID();
        fprintf(f, "%d;%s;%s;%d;%.2f;%s\n", a.id, a.nom, especeToStr(a.espece), a.annee_naissance, a.poids, (a.commentaire[0] == '\0') ? "Aucun" : a.commentaire);
        fclose(f);
        f = NULL;

        printf(GREEN "✅ Animal #%d (%s) ajouté avec succès ! 🎊\n" RESET, a.id, a.nom);
        printf("\nAppuyez sur Entrée pour retourner au menu principal...");
        nettoyerBuffer();
        return;

    recommencer_ajout_complet:;
    }
}
