CC = gcc
CFLAGS = -Wall -Wextra

OBJECTS = adopterAnimal.o affichage.o ajouterAnimal.o animal.o comparer.o id.o inventaire.o main.o nettoyeur.o nourriture.o rechercherAnimaux.o utils.o

all: chenil.exe

chenil.exe: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f chenil.exe
	rm -f *.o
