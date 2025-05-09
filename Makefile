all: chenil.exe

animal.o: animal.c animal.h
	gcc -c animal.c -o animal.o

affichage.o: affichage.c affichage.h
	gcc -c affichage.c -o affichage.o

ajouterAnimal.o: ajouterAnimal.c ajouterAnimal.h
	gcc -c ajouterAnimal.c -o ajouterAnimal.o

adopterAnimal.o: adopterAnimal.c adopterAnimal.h
	gcc -c adopterAnimal.c -o adopterAnimal.o

inventaire.o: inventaire.c inventaire.h
	gcc -c inventaire.c -o inventaire.o

nourriture.o: nourriture.c nourriture.h
	gcc -c nourriture.c -o nourriture.o

rechercherAnimaux.o: rechercherAnimaux.c rechercherAnimaux.h
	gcc -c rechercherAnimaux.c -o rechercherAnimaux.o

retourmenu.o: retourmenu.c retourmenu.h
	gcc -c retourmenu.c -o retourmenu.o

utils.o: utils.c utils.h
	gcc -c utils.c -o utils.o

nettoyeur.o: nettoyeur.c nettoyeur.h
	gcc -c nettoyeur.c -o nettoyeur.o

main.o: main.c animal.h ajouterAnimal.h adopterAnimal.h inventaire.h nourriture.h rechercherAnimaux.h retourmenu.h utils.h affichage.h nettoyeur.h
	gcc -c main.c -o main.o

chenil.exe: main.o animal.o ajouterAnimal.o adopterAnimal.o inventaire.o nourriture.o rechercherAnimaux.o retourmenu.o utils.o affichage.o nettoyeur.o
	gcc main.o animal.o ajouterAnimal.o adopterAnimal.o inventaire.o nourriture.o rechercherAnimaux.o retourmenu.o utils.o affichage.o nettoyeur.o -o chenil.exe

clean:
	rm -f *.o chenil.exe

cleanfile:
	rm -f data/animaux/animaux.txt
	touch data/animaux/animaux.txt
