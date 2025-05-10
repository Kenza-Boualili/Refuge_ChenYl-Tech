all: bin/chenil
obj/utils.o: src/utils.c include/utils.h
	gcc -c src/utils.c -o obj/utils.o
obj/retourmenu.o: src/retourmenu.c include/retourmenu.h include/utils.h
	gcc -c src/retourmenu.c -o obj/retourmenu.o
obj/rechercherAnimaux.o: src/rechercherAnimaux.c include/animal.h include/comparer.h include/utils.h include/affichage.h
	gcc -c src/rechercherAnimaux.c -o obj/rechercherAnimaux.o
obj/nourriture.o: src/nourriture.c include/animal.h include/comparer.h include/utils.h include/retourmenu.h
	gcc -c src/nourriture.c -o obj/nourriture.o
obj/nettoyeur.o: src/nettoyeur.c include/comparer.h include/utils.h include/animal.h include/retourmenu.h include/nourriture.h
	gcc -c src/nettoyeur.c -o obj/nettoyeur.o
obj/inventaire.o: src/inventaire.c include/inventaire.h include/animal.h include/comparer.h include/utils.h include/retourmenu.h
	gcc -c src/inventaire.c -o obj/inventaire.o
obj/id.o: src/id.c
	gcc -c src/id.c -o obj/id.o
obj/comparer.o: src/comparer.c include/comparer.h include/animal.h
	gcc -c src/comparer.c -o obj/comparer.o
obj/ajouterAnimal.o: src/ajouterAnimal.c include/retourmenu.h include/utils.h include/animal.h include/id.h
	gcc -c src/ajouterAnimal.c -o obj/ajouterAnimal.o
obj/animal.o: src/animal.c include/animal.h
	gcc -c src/animal.c -o obj/animal.o
obj/affichage.o: src/affichage.c include/animal.h
	gcc -c src/affichage.c -o obj/affichage.o
obj/adopterAnimal.o: src/adopterAnimal.c include/comparer.h include/utils.h include/animal.h include/retourmenu.h
	gcc -c src/adopterAnimal.c -o obj/adopterAnimal.o
obj/main.o: src/main.c include/ajouterAnimal.h include/affichage.h include/rechercherAnimaux.h include/nettoyeur.h include/adopterAnimal.h include/nourriture.h include/inventaire.h include/utils.h
	gcc -c src/main.c -o obj/main.o
bin/chenil: obj/main.o obj/ajouterAnimal.o obj/affichage.o obj/animal.o obj/inventaire.o obj/nourriture.o obj/rechercherAnimaux.o obj/adopterAnimal.o obj/utils.o obj/retourmenu.o obj/nettoyeur.o obj/id.o obj/comparer.o
	gcc obj/main.o obj/ajouterAnimal.o obj/affichage.o obj/animal.o obj/inventaire.o obj/nourriture.o obj/rechercherAnimaux.o obj/adopterAnimal.o obj/utils.o obj/retourmenu.o obj/nettoyeur.o obj/id.o obj/comparer.o -o bin/chenil

clean:
	rm obj/main.o obj/ajouterAnimal.o obj/affichage.o obj/animal.o obj/inventaire.o obj/nourriture.o obj/rechercherAnimaux.o obj/adopterAnimal.o obj/utils.o obj/retourmenu.o obj/nettoyeur.o obj/id.o obj/comparer.o
	rm bin/chenil

cleanfile:
	rm -f data/animaux/animaux.txt
	touch data/animaux/animaux.txt
