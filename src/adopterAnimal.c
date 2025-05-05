#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       

#include "animal.h"    
#include "retourmenu.h"
#include "utils.h"      
#include "comparer.h"   

#define RED_BOLD    "\033[1;31m"  
#define GREEN_BOLD  "\033[1;32m"  
#define YELLOW_BOLD "\033[1;33m"  
#define BLUE_BOLD   "\033[1;34m" 
#define CYAN_BOLD   "\033[1;36m"  

#define PINK        "\033[1;35m"  
#define GREEN       "\033[1;32m"  
#define CYAN        "\033[1;36m"  
#define RED         "\033[1;31m"  
#define WHITE       "\033[1;37m"  

#define RESET       "\033[0m"     


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
    FILE *f_in = NULL, *f_out = NULL;
    char input_buffer[TAILLE_NOM + 10];
    int id_a_adopter = -1;
    int choix_methode = 0;
    int adoption_terminee = 0;
    char ligne[512];
    Animal correspondances[MAX_ANIMAUX];
    int nb_correspondances = 0;
    Animal temp_animal;
    char temp_espece_str[50];
    char temp_comment_str[TAILLE_COMM];

    while (!adoption_terminee) {  
        id_a_adopter = -1;
        nb_correspondances = 0;  

        printf(BLUE_BOLD "\n=== Adopter un Animal ===\n" RESET); 
        printf("Comment identifier l'animal ?\n1. Par ID\n2. Par Nom\n Tapez 'm' pour menu principal.\n");  
        printf(CYAN_BOLD "Choix : " RESET); 
        
        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
            return;
        }

        enleverNewline(input_buffer, sizeof(input_buffer)); 
        
        if (input_buffer[0] == 'm' && input_buffer[1] == '\0') {
            return;
        }

        if (sscanf(input_buffer, "%d", &choix_methode) != 1 || (choix_methode != 1 && choix_methode != 2)) {
            printf(RED_BOLD "❌ Choix invalide (1 ou 2).\n" RESET);  
            printf(YELLOW_BOLD "(Rappel: 'm' menu.)\n" RESET);  
            continue;  
        }

        if (choix_methode == 1) { 
            printf(YELLOW_BOLD "Entrez l'ID ('r' retour, 'm' menu) : " RESET); 
            if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {  
                return;
            }
            enleverNewline(input_buffer, sizeof(input_buffer));  
            if (input_buffer[0] == 'm' && input_buffer[1] == '\0') { 
                return;
            }
            if (input_buffer[0] == 'r' && input_buffer[1] == '\0') { 
                continue;
            }

            if (sscanf(input_buffer, "%d", &id_a_adopter) != 1 || id_a_adopter <= 0) {
                printf(RED_BOLD "❌ ID invalide.\n" RESET); 
                printf(YELLOW_BOLD "(Rappel: 'r' retour, 'm' menu.)\n" RESET);  
                continue; 
            }
                
            printf(GREEN_BOLD "Recherche ID %d...\n" RESET, id_a_adopter);
        } else { 
            printf(YELLOW_BOLD "Entrez le Nom ('r' retour, 'm' menu) : " RESET); 
            if (!fgets(input_buffer, sizeof(input_buffer), stdin)) { 
                return;  
            }
            enleverNewline(input_buffer, sizeof(input_buffer)); 

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
            } else {
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
