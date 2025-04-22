#include <stdio.h> //Pour utiliser les fonctions standard d’entrée/sortie comme `printf`, `scanf`, `fopen`, `fclose`, `remove`, `rename`.
#include <stdlib.h> //Pour pouvoir utiliser les fonctions remove() et rename() qui sont dans cette bibliothèque.
#include "animal.h" //C’est le fichier `.h` qui contient la **structure `Animal`** utilisée ici.

void adopterAnimal() {
    FILE *f = fopen("animaux/animaux.txt", "r"); //On ouvre le fichier en mode `"r"` (**lecture**) pour lire tous les animaux.
    if (!f) { //Pour vérifier que le fichier a bien été ouvert. !f est équivalent à f == NULL.

        printf("\033[38;5;196mFichier animaux.txt introuvable.\033[0m 🚫\n"); //Pour afficher une **erreur en rouge vif** avec un emoji. Le code `\033[38;5;196m` donne du style au terminal (ici, rouge vif).  
                                                                              //`[0m` remet la couleur par défaut.
        return;//On arrête la fonction tout de suite si le fichier est introuvable.
    }

    int idRecherche; //On prépare une variable pour stocker l'ID que l'utilisateur va entrer.
    printf("\033[38;5;45mEntrez l'ID de l'animal à adopter : \033[0m");   //Invite à l’utilisateur, en bleu clair pour la lisibilité.
    scanf("%d", &idRecherche); //Pour lire un **entier** entré par l'utilisateur.  

    FILE *temp = fopen("animaux/animaux_temp.txt", "w"); //On ouvre un fichier temporaire pour y écrire tous les animaux sauf celui à adopter. Cette méthode est plus fiable et propre.
    if (!temp) { //Encore une vérification pour éviter de travailler avec un fichier mal ouvert.
        printf("\033[38;5;196mErreur lors de la création du fichier temporaire.\033[0m ❌\n");  
        fclose(f); //On ferme proprement le fichier original et on quitte si le fichier temporaire n'a pas pu être ouvert.
        return;
    }

    int trouve = 0; //C’est un **booléen** (0 ou 1) pour indiquer si on a trouvé l'animal ou pas.
    Animal a; //On crée une variable de type Animal pour stocker les données lues.
    char especeStr[20]; //L’espèce est stockée en texte dans le fichier, donc on a besoin d’un tableau temporaire pour la lire.
    //On ne stocke pas encore dans `a.espece` directement ici, peut-être car `espece` est un `enum` dans `animal.h`.

    while (fscanf(f, "%d;%49[^;];%14[^;];%d;%f;%255[^\n]",
                  &a.id, a.nom, especeStr, &a.annee_naissance, &a.poids, a.commentaire) == 6) { //On lit chaque ligne du fichier avec fscanf et on extrait chaque champ
        if (a.id == idRecherche) {
            trouve = 1; // Si on a trouvé l’animal, on le **saute** → on ne veut **pas l’écrire dans le fichier temporaire**.
        } else { 
            fprintf(temp, "%d;%s;%s;%d;%.2f;%s\n", a.id, a.nom, especeStr,
                    a.annee_naissance, a.poids, a.commentaire);
        } //On écrit tous les autres animaux dans le fichier temporaire. On garde le même format CSV que dans le fichier original.
    }

    fclose(f);
    fclose(temp); //On ferme les fichiers dès qu’on a fini d’écrire/traiter.

    if (trouve) {
        remove("animaux/animaux.txt");
        rename("animaux/animaux_temp.txt", "animaux/animaux.txt"); //Si on a trouvé l’animal, on supprime l'ancien fichier et on remplace par le nouveau.
        // Correction : Ajout de l'argument idRecherche
        printf("\033[38;5;40mL'animal avec l'ID %d a été adopté et retiré du refuge !\033[0m 🐾💖\n", idRecherche); //Message de succès, en **vert**
    } else {
        remove("animaux/animaux_temp.txt"); //Si l’animal n’est pas trouvé, on supprime le fichier temporaire (inutile).
        printf("\033[38;5;226mAucun animal trouvé avec l'ID %d.\033[0m 🛑\n", idRecherche); //Message d’échec en **jaune** pour dire que l’ID n’existe pas.
    }
}
