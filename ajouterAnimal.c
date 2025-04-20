#include "animal.h"
#include "id.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#define PINK    "\033[95m"
#define GREEN   "\033[92m"
#define CYAN    "\033[96m"
#define YELLOW  "\033[93m"
#define RED     "\033[91m"
#define RESET   "\033[0m"

void ajouterAnimal() {
    system("mkdir -p animaux");
    FILE *f = fopen("animaux/animaux.txt", "a");
    if (!f) {
        printf(RED "❌ Erreur : impossible de créer le fichier !\n" RESET);
        return;
    }

    Animal a;
    a.id = genererID();
    
    printf(PINK "\n🎉 --- Ajout d’un nouvel animal --- 🐾\n" RESET);
    
    printf(CYAN "📛 Nom : " RESET);
    scanf("%49s", a.nom);
    nettoyerBuffer();
    
    a.espece = choisirEspece();
    
    do {
        printf(CYAN "📅 Année de naissance : " RESET);
        scanf("%d", &a.annee_naissance);
        nettoyerBuffer();
        
        if (a.annee_naissance < 0) {
            printf(RED "⚠️  L'année ne peut pas être négative !\n" RESET);
        }
        else if (a.annee_naissance < 1900 || a.annee_naissance > 2025) {
            printf(RED "⚠️  L'année doit être entre 1900 et 2025 !\n" RESET);
        }
    } while (a.annee_naissance < 1900 || a.annee_naissance > 2025 || a.annee_naissance < 0);
    
    do {
        printf(CYAN "⚖️  Poids (kg) : " RESET);
        scanf("%f", &a.poids);
        nettoyerBuffer();
        
        if (a.poids <= 0) {
            printf(RED "⚠️  Le poids doit être supérieur à 0 !\n" RESET);
        }
    } while (a.poids <= 0);

    printf(CYAN "🗒️  Commentaire : " RESET);
    fgets(a.commentaire, TAILLE_COMM, stdin);

    fprintf(f, "%d;%s;%s;%d;%.2f;%s\n",
            a.id, 
            a.nom, 
            especeToStr(a.espece),
            a.annee_naissance, 
            a.poids, 
            a.commentaire);
    
    fclose(f);

    printf(GREEN "✅ Animal #%d ajouté avec succès ! 🎊\n" RESET, a.id);
}