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

#define ROSE         "\033[95m"
#define VERT         "\033[92m"
#define CYAN         "\033[96m"
#define JAUNE        "\033[93m"
#define JAUNE_GRAS   "\033[1;33m"
#define ROUGE        "\033[91m"
#define REINITIALISER "\033[0m"

void ajouterAnimal() {
    Animal a;
    char tampon_saisie[TAILLE_COMM];
    FILE *f = NULL;
    int annee_actuelle;

    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);
    annee_actuelle = tm_info.tm_year + 1900;

    while (1) {
        printf(ROSE "\n🎉 --- Ajout d’un nouvel animal --- 🐾\n" REINITIALISER);
        printf(JAUNE "    (Tapez 'r' pour recommencer, 'm' pour menu principal)\n" REINITIALISER);

        // Nom
        printf(CYAN "📛 Nom : " REINITIALISER);
        if (!fgets(tampon_saisie, sizeof(tampon_saisie), stdin)) {
            return;
        }
        enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));
        if (tampon_saisie[0] == 'm' && tampon_saisie[1] == '\0') {
            return;
        }
        if (tampon_saisie[0] == 'r' && tampon_saisie[1] == '\0') {
            printf("\nRecommencement...\n");
            continue;
        }
        if (tampon_saisie[0] == '\0') {
            printf(ROUGE "Le nom ne peut pas être vide.\n" REINITIALISER);
            printf(JAUNE_GRAS "(Rappel : Tapez 'r' pour recommencer ou 'm' pour menu.)\n" REINITIALISER);
            continue;
        }
        snprintf(a.nom, sizeof(a.nom), "%.*s", (int)(sizeof(a.nom) - 1), tampon_saisie);

        // Espèce
        a.espece = choisirEspece();

        // Année de naissance
        while (1) {
            printf(CYAN "📅 Année naissance (1980-%d) : " REINITIALISER, annee_actuelle);
            if (!fgets(tampon_saisie, sizeof(tampon_saisie), stdin)) {
                return;
            }
            enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));
            if (tampon_saisie[0] == 'm' && tampon_saisie[1] == '\0') {
                return;
            }
            if (tampon_saisie[0] == 'r' && tampon_saisie[1] == '\0') {
                printf("\nRecommencement...\n");
                goto recommencer_ajout_complet;
            }
            if (sscanf(tampon_saisie, "%d", &a.annee_naissance) == 1 &&
                a.annee_naissance >= 1980 && a.annee_naissance <= annee_actuelle) {
                break;
            } else {
                printf(ROUGE "⚠️ Année invalide !\n" REINITIALISER);
                printf(JAUNE_GRAS "(Rappel : 'r' / 'm')\n" REINITIALISER);
            }
        }

        // Poids
        while (1) {
            printf(CYAN "⚖️ Poids (kg) (>0, <1000) : " REINITIALISER);
            if (!fgets(tampon_saisie, sizeof(tampon_saisie), stdin)) {
                return;
            }
            enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));
            if (tampon_saisie[0] == 'm' && tampon_saisie[1] == '\0') {
                return;
            }
            if (tampon_saisie[0] == 'r' && tampon_saisie[1] == '\0') {
                printf("\nRecommencement...\n");
                goto recommencer_ajout_complet;
            }
            float poids_temp;
            if (sscanf(tampon_saisie, "%f", &poids_temp) == 1 && poids_temp > 0 && poids_temp < 1000) {
                a.poids = poids_temp;
                break;
            } else {
                printf(ROUGE "⚠️ Poids invalide !\n" REINITIALISER);
                printf(JAUNE_GRAS "(Rappel : 'r' / 'm')\n" REINITIALISER);
            }
        }

        // Commentaire
        printf(CYAN "🗒️ Commentaire (optionnel, 'r' / 'm') : " REINITIALISER);
        if (!fgets(tampon_saisie, sizeof(tampon_saisie), stdin)) {
            return;
        }
        enleverSautLigne(tampon_saisie, sizeof(tampon_saisie));
        if (tampon_saisie[0] == 'm' && tampon_saisie[1] == '\0') {
            return;
        }
        if (tampon_saisie[0] == 'r' && tampon_saisie[1] == '\0') {
            printf("\nRecommencement...\n");
            continue;
        }
        snprintf(a.commentaire, sizeof(a.commentaire), "%.*s", (int)(sizeof(a.commentaire) - 1), tampon_saisie);

        // Vérification des dossiers
        printf("Vérification/Création des dossiers...\n");

        if (mkdir("data", 0755) != 0 && errno != EEXIST) {
            printf(ROUGE "❌ Erreur création dossier 'data' !\n" REINITIALISER);
            perror("   Erreur système mkdir");
        }
        if (mkdir("data/animaux", 0755) != 0 && errno != EEXIST) {
            printf(ROUGE "❌ Erreur création dossier 'data/animaux' !\n" REINITIALISER);
            perror("   Erreur système mkdir");
        }

        // Sauvegarde
        const char *chemin_fichier = "data/animaux/animaux.txt";
        printf("Ouverture de '%s' en mode ajout...\n", chemin_fichier);
        f = fopen(chemin_fichier, "a");
        if (!f) {
            printf(ROUGE "❌ Erreur OUVERTURE fichier '%s' pour sauvegarde !\n" REINITIALISER, chemin_fichier);
            perror("   >>> Erreur système retournée par fopen");
            printf(JAUNE_GRAS "   Vérifiez les permissions du dossier 'data/animaux' !\n" REINITIALISER);
            printf(JAUNE_GRAS "   Vérifiez que vous lancez bien depuis 'vrai-code' avec ./bin/chenil\n" REINITIALISER);
            return;
        }

        a.id = genererID();
        fprintf(f, "%d;%s;%s;%d;%.2f;%s\n", a.id, a.nom, especeVersChaine(a.espece), a.annee_naissance, a.poids, (a.commentaire[0] == '\0') ? "Aucun" : a.commentaire);
        fclose(f);
        f = NULL;

        printf(VERT "✅ Animal #%d (%s) ajouté avec succès ! 🎊\n" REINITIALISER, a.id, a.nom);
        printf("\nAppuyez sur Entrée pour retourner au menu principal...");
        nettoyerTampon();
        return;

    recommencer_ajout_complet:;
    }
}

