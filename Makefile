all: bin/chenil

bin/chenil: obj/main.o obj/ajouterAnimal.o obj/affichage.o obj/animal.o obj/inventaire.o obj/nourriture.o obj/rechercherAnimaux.o obj/adopterAnimal.o obj/utils.o obj/retourmenu.o obj/nettoyeur.o obj/id.o obj/comparer.o
	gcc $^ -o bin/chenil

obj/%.o: src/%.c
	@mkdir -p obj
	gcc -Wall -Wextra -Iinclude -c $< -o $@

clean:
	rm -rf obj
	rm -f bin/chenil

cleanfile:
	rm -f data/animaux/animaux.txt
	touch data/animaux/animaux.txt
