# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra

# Liste des fichiers objets nécessaires pour l'exécutable
# (Utilisation de \ pour séparer sur plusieurs lignes pour la lisibilité)
OBJECTS = adopterAnimal.o affichage.o ajouterAnimal.o \
          animal.o comparer.o id.o inventaire.o main.o \
          nettoyeur.o nourriture.o rechercherAnimaux.o \
          utils.o retourmenu.o 

# Nom de l'exécutable final
TARGET = chenil.exe

# Règle par défaut (celle exécutée si on tape juste "make")
# Dépend de l'exécutable final.
all: $(TARGET)

# Règle pour créer l'exécutable final à partir des fichiers objets
# La ligne de commande DOIT commencer par une TABULATION
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Règle générique pour compiler un fichier .c en .o
# Compile si le .c correspondant est plus récent que le .o
# La ligne de commande DOIT commencer par une TABULATION
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
# Les lignes de commande DOIVENT commencer par une TABULATION
clean:
	rm -f $(TARGET)
	rm -f *.o

# Déclarer les cibles qui ne sont pas des fichiers (bonne pratique)
.PHONY: all clean
