CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o ajouterAnimal.o animal.o id.o affichage.o rechercherAnimaux.o comparer.o nettoyeur.o adopterAnimal.o nourriture.o inventaire.o utils.o

chenil: $(OBJ)
	$(CC) $(CFLAGS) -o chenil $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o chenil