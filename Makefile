CC = gcc //définit le compilateur à utiliser
CFLAGS = -Wall -Wextra -std=c99  //Ce sont les options de compilation
OBJ = main.o ajouterAnimal.o animal.o id.o affichage.o rechercherAnimaux.o comparer.o nettoyeur.o adopterAnimal.o nourriture.o inventaire.o utils.o //Liste de tous les fichiers objets

chenil: $(OBJ) //C’est la règle principale
	$(CC) $(CFLAGS) -o chenil $(OBJ) //Cette ligne compile tous les .o pour créer l’exécutable chenil

%.o: %.c //Règle générique : pour chaque fichier .c, comment créer le .o correspondant
	$(CC) $(CFLAGS) -c $< //Cette ligne compile un fichier .c en .o. et  $< représente le fichier source (le .c)

clean:  //Une règle spéciale pour nettoyer le projet
	rm -f *.o chenil //Supprime tous les fichiers .o et l’exécutable chenil

//Ce Makefile sert à compiler un projet C dont le programme principal s’appelle chenil. Il :
//Compile chaque fichier .c en .o
//Assemble tous les .o pour créer chenil
//Permet de faire le ménage avec make clean
