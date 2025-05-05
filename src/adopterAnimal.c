#include <stdio.h>      // Bibliothèque pour afficher du texte à l'écran 
#include <stdlib.h>     // Bibliothèque pour gérer la mémoire, les conversions, les nombres aléatoires...
#include <time.h>       // Bibliothèque pour gérer le temps 

#include "animal.h"     // Fichier avec des fonctions liées aux animaux 
#include "retourmenu.h" // Fichier avec des fonctions pour revenir au menu 
#include "utils.h"      // Fichier contenant des fonctions utilitaires 
#include "comparer.h"   // Fichier pour comparer des éléments

#define RED_BOLD    "\033[1;31m"  // Texte en rouge et en gras
#define GREEN_BOLD  "\033[1;32m"  // Texte en vert et en gras
#define YELLOW_BOLD "\033[1;33m"  // Texte en jaune et en gras
#define BLUE_BOLD   "\033[1;34m"  // Texte en bleu et en gras
#define CYAN_BOLD   "\033[1;36m"  // Texte cyan et en gras

#define PINK        "\033[1;35m"  // Texte en rose
#define GREEN       "\033[1;32m"  // Texte en vert
#define CYAN        "\033[1;36m"  // Texte cyan
#define RED         "\033[1;31m"  // Texte en rouge
#define WHITE       "\033[1;37m"  // Texte en blanc

#define RESET       "\033[0m"     // Revient à la couleur normale


static int calculerAgeAdopter(int annee_naissance) { 
    if (annee_naissance <= 0) { // Si l'année de naissance est inférieure ou égale à 0, ce n'est pas valide
        return -2; // Code d'erreur : année invalide
    }
    
    time_t maintenant = time(NULL);// Récupère l'heure actuelle (en secondes depuis 1970)

    // Convertit cette heure en une structure contenant la date locale (jour, mois et anné)
    struct tm *tm = localtime(&maintenant);

    // Si la conversion échoue (tm est NULL) on retourne une erreur
    if (tm == NULL) {
        return -1; // Code d'erreur 
    }
    
    // tm_year donne l'année actuelle - 1900 donc on ajoute 1900 pour avoir l'année réelle
    int annee_actuelle = tm->tm_year + 1900;

    // Vérifie si l'année de naissance est supérieure à l'année actuelle
    // ou si elle est trop ancienne (avant 1900)
    if (annee_naissance > annee_actuelle || annee_naissance < 1900) {
        return -2; // année incohérente
    }

    // Si tout est correct, on calcule l'âge en faisant la différence entre l'année actuelle et l'année de naissance
    return annee_actuelle - annee_naissance;
}

void adopterAnimal() {
    // Déclare deux pointeurs de fichiers, un pour lire (f_in) et l’autre pour écrire (f_out)
    FILE *f_in = NULL, *f_out = NULL;

    // Une zone mémoire pour stocker du texte tapé par l'utilisateur (un nom ou un choix)
    char input_buffer[TAILLE_NOM + 10];

    // Variable qui contient l’identifiant de l’animal à adopter
    int id_a_adopter = -1;

    // Variable pour stocker le choix de l’utilisateur entre plusieurs méthodes d’adoption
    int choix_methode = 0;

    // Booléen pour savoir si l’adoption est terminée
    int adoption_terminee = 0;

    // Une chaîne de caractères utilisée pour lire une ligne depuis un fichier
    char ligne[512];

    // Tableau pour stocker des animaux qui correspondent aux critères de l’utilisateur
    Animal correspondances[MAX_ANIMAUX];

    // Compteur pour savoir combien de correspondances ont été trouvées
    int nb_correspondances = 0;

    // Variable temporaire pour stocker un animal lu ou manipulé temporairement
    Animal temp_animal;

    // Chaîne temporaire pour stocker l’espèce de l’animal 
    char temp_espece_str[50];

    // Chaîne temporaire pour stocker un commentaire sur l’animal
    char temp_comment_str[TAILLE_COMM];
}

    while (!adoption_terminee) {  // Tant que l'adoption n'est pas terminée, on continue la boucle.
    id_a_adopter = -1;  // On réinitialise l'ID de l'animal à adopter à -1
    nb_correspondances = 0;  // On réinitialise le nombre de correspondances trouvées à 0

    printf(BLUE_BOLD "\n=== Adopter un Animal ===\n" RESET);  // Affiche le titre du menu en bleu gras.
    printf("Comment identifier l'animal ?\n1. Par ID\n2. Par Nom\n Tapez 'm' pour menu principal.\n");  // Affiche les options pour identifier l'animal
    printf(CYAN_BOLD "Choix : " RESET);  // Affiche un message pour que l'utilisateur entre son choix.

    // Lit la ligne entrée par l'utilisateur dans 'input_buffer'.
    if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
        return;  // Si la lecture échoue, on quitte la fonction.
    }

    enleverNewline(input_buffer, sizeof(input_buffer));  // Supprime le caractère de nouvelle ligne ('\n') à la fin de l'entrée, si présent

    // Si l'utilisateur tape 'm' et appuie sur 'Entrée', on quitte la fonction pour retourner au menu principal.
    if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
        return;
    }

    // Vérifie si l'utilisateur a bien entré un nombre entier et si ce nombre est soit 1 soit 2.
    if (sscanf(input_buffer, "%d", &choix_methode) != 1 || (choix_methode != 1 && choix_methode != 2)) {
        printf(RED_BOLD "❌ Choix invalide (1 ou 2).\n" RESET);  // Si le choix est invalide, affiche un message d'erreur en rouge gras.
        printf(YELLOW_BOLD "(Rappel: 'm' menu.)\n" RESET);  // Rappelle à l'utilisateur qu'il peut taper 'm' pour revenir au menu.
        continue;  // Continue la boucle pour permettre à l'utilisateur de réessayer.
    }
}


    if (choix_methode == 1) {  // Si l'utilisateur a choisi l'option 1 donc chercher par ID
    printf(YELLOW_BOLD "Entrez l'ID ('r' retour, 'm' menu) : " RESET);  // Demande à l'utilisateur de saisir l'ID de l'animal
    if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {  // Lit l'entrée de l'utilisateur
        return;  // Si la lecture échoue, quitte la fonction
    }
    enleverNewline(input_buffer, sizeof(input_buffer));  // Enlève le caractère de nouvelle ligne à la fin de l'entrée

    if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {  // Si l'utilisateur tape 'm' on retourne au menu
        return;
    }
    if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {  // Si l'utilisateur tape 'r' on retourne à l'étape précédente
        continue;
    }

    // Vérifie si l'utilisateur a saisi un ID valide (positif)
    if (sscanf(input_buffer, "%d", &id_a_adopter) != 1 || id_a_adopter <= 0) {
        printf(RED_BOLD "❌ ID invalide.\n" RESET);  // Si l'ID est invalide, affiche un message d'erreur en rouge
        printf(YELLOW_BOLD "(Rappel: 'r' retour, 'm' menu.)\n" RESET);  // Rappelle à l'utilisateur qu'il peut taper 'r' ou 'm'
        continue;  // Reprend la boucle pour que l'utilisateur réessaie
    }

    // Si l'ID est valide, affiche un message indiquant qu'on va rechercher l'animal avec cet ID
    printf(GREEN_BOLD "Recherche ID %d...\n" RESET, id_a_adopter);
} else {  // Sinon, si l'utilisateur a choisi de chercher par nom
    printf(YELLOW_BOLD "Entrez le Nom ('r' retour, 'm' menu) : " RESET);  // Demande à l'utilisateur de saisir le nom de l'animal
    if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {  // Lit l'entrée de l'utilisateur
        return;  // Si la lecture échoue on quitte la fonction
    }
    enleverNewline(input_buffer, sizeof(input_buffer));  // Enlève le caractère de nouvelle ligne à la fin de l'entrée
 }

            
            if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
                return;
            }
            if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
                continue;
            }
            
            if (input_buffer[0] == '\0') {
                printf(RED_BOLD "❌ Nom vide.\n" RESET);
                printf(YELLOW_BOLD "(Rappel: 'r' retour, 'm' menu.)\n" RESET);
                continue;
            }
            
            char nomRecherche[TAILLE_NOM];
            snprintf(nomRecherche, sizeof(nomRecherche), "%.*s", (int)(sizeof(nomRecherche)-1), input_buffer);

            f_in = fopen("data/animaux/animaux.txt", "r");
            if (!f_in) {
                printf(RED_BOLD "❌ Erreur ouverture fichier.\n" RESET);
                return;
            }
            
            // Recherche des correspondances
            while (fgets(ligne, sizeof(ligne), f_in) && nb_correspondances < MAX_ANIMAUX) {
                if (sscanf(ligne, "%d;%49[^;];", &temp_animal.id, temp_animal.nom) == 2) {
                    if (comparer(temp_animal.nom, nomRecherche)) {
                        temp_comment_str[0] = '\0';
                        int champsLus = sscanf(ligne, "%d;%49[^;];%49[^;];%d;%f;%255[^\n]",
                                              &correspondances[nb_correspondances].id,
                                              correspondances[nb_correspondances].nom,
                                              temp_espece_str,
                                              &correspondances[nb_correspondances].annee_naissance,
                                              &correspondances[nb_correspondances].poids,
                                              temp_comment_str);
                                              
                        if (champsLus >= 5) {
                            correspondances[nb_correspondances].espece = strToEspece(temp_espece_str);
                            temp_comment_str[sizeof(temp_comment_str)-1] = '\0';
                            snprintf(correspondances[nb_correspondances].commentaire, TAILLE_COMM, "%s", temp_comment_str);
                            enleverNewline(correspondances[nb_correspondances].commentaire, TAILLE_COMM);
                            nb_correspondances++;
                        }
                    }
                }
            }
            fclose(f_in);
            f_in = NULL;

            if (nb_correspondances == 0) {
                printf(YELLOW_BOLD "⚠️ Aucun trouvé: '%s'.\n" RESET, nomRecherche);
                printf(YELLOW_BOLD "(Rappel: 'r' retour, 'm' menu.)\n" RESET);
                continue;
            } else if (nb_correspondances == 1) {
                id_a_adopter = correspondances[0].id;
                printf(GREEN_BOLD "✅ Un seul trouvé: '%s' (ID: %d).\n" RESET, correspondances[0].nom, id_a_adopter);
            } else { // > 1
                printf(YELLOW_BOLD "⚠️ Plusieurs trouvés ('%s'):\n" RESET, nomRecherche);
                for (int i = 0; i < nb_correspondances; i++) {
                    Animal *match = &correspondances[i];
                    int age = calculerAgeAdopter(match->annee_naissance);
                    
                    printf(GREEN_BOLD "---\n" RESET);
                    printf(YELLOW_BOLD " ID : %d\n" RESET, match->id);
                    printf(PINK " Nom : %s\n" RESET, match->nom);
                    printf(GREEN " Espèce : %s\n" RESET, especeToStr(match->espece));
                    
                    if (age == -1) {
                        printf(CYAN " Âge : Err\n" RESET);
                    } else if (age == -2) {
                        printf(CYAN " Âge : Inv\n" RESET);
                    } else {
                        printf(CYAN " Âge : %d ans\n" RESET, age);
                    }
                    
                    printf(RED " Poids : %.2f kg\n" RESET, match->poids);
                    printf(WHITE " Commentaire: %s\n" RESET, match->commentaire[0] == '\0' ? "Aucun" : match->commentaire);
                }
                printf(GREEN_BOLD "------------------------------------\n" RESET);

                while (id_a_adopter == -1) {
                    printf(CYAN_BOLD "\nLequel adopter ?\n" RESET);
                    printf(YELLOW_BOLD "Entrez ID exact ('r' retour, 'm' menu) : " RESET);
                    
                    if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
                        return;
                    }
                    enleverNewline(input_buffer, sizeof(input_buffer));
                    
                    if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
                        return;
                    }
                    if (input_buffer[0] == 'r' && input_buffer[1] == '\0') {
                        break;
                    }
                    
                    int id_temp;
                    if (sscanf(input_buffer, "%d", &id_temp) == 1) {
                        int id_valide = 0;
                        for (int i = 0; i < nb_correspondances; i++) {
                            if (correspondances[i].id == id_temp) {
                                id_a_adopter = id_temp;
                                id_valide = 1;
                                break;
                            }
                        }
                        if (!id_valide) {
                            printf(RED_BOLD "❌ ID pas listé.\n" RESET);
                        }
                    } else {
                        printf(RED_BOLD "❌ ID invalide.\n" RESET);
                        printf(YELLOW_BOLD "(Rappel: 'r' retour, 'm' menu.)\n" RESET);
                    }
                }
                if (id_a_adopter == -1) {
                    continue;
                }
            }
        }

        // Logique d'adoption commune
        if (id_a_adopter != -1) {
            int trouve_final = 0;
            char nomTrouveFinal[TAILLE_NOM] = "";
            
            f_in = fopen("data/animaux/animaux.txt", "r");
            f_out = fopen("data/animaux/animaux_temp.txt", "w");
            
            if (!f_in || !f_out) {
                printf(RED_BOLD "❌ Erreur fichiers adoption.\n" RESET);
                if (f_in) fclose(f_in);
                if (f_out) fclose(f_out);
                remove("data/animaux/animaux_temp.txt");
                return;
            }
            
            while (fgets(ligne, sizeof(ligne), f_in)) {
                int idCourant;
                if (sscanf(ligne, "%d;", &idCourant) == 1) {
                    if (idCourant == id_a_adopter) {
                        trouve_final = 1;
                        sscanf(ligne, "%*d;%49[^;];", nomTrouveFinal);
                    } else {
                        fprintf(f_out, "%s", ligne);
                    }
                } else {
                    size_t len = longueurChaine(ligne);
                    if (len > 0) {
                        fprintf(f_out, "%s", ligne);
                        if (ligne[len] != '\n') {
                            fprintf(f_out, "\n");
                        }
                    }
                }
            }
            
            fclose(f_in);
            f_in = NULL;
            fclose(f_out);
            f_out = NULL;

            if (trouve_final) {
                if (remove("data/animaux/animaux.txt") != 0) {
                    printf(RED_BOLD "❌ Erreur remove.\n" RESET);
                    remove("data/animaux/animaux_temp.txt");
                } else if (rename("data/animaux/animaux_temp.txt", "data/animaux/animaux.txt") != 0) {
                    printf(RED_BOLD "❌ Erreur rename.\n" RESET);
                    printf(YELLOW_BOLD " Données dans 'data/animaux/animaux_temp.txt'.\n" RESET);
                } else {
                    printf(GREEN_BOLD "✅ Adoption de %s (ID: %d) réussie !\n" RESET, nomTrouveFinal, id_a_adopter);
                }
            } else {
                printf(YELLOW_BOLD "⚠️ Erreur interne: ID %d non retrouvé.\n" RESET, id_a_adopter);
                remove("data/animaux/animaux_temp.txt");
            }
            adoption_terminee = 1;
            printf("\nAppuyez sur Entrée...");
            nettoyerBuffer();
        }
    }
}
