PROG = projet

SRC = main.c

all : $(PROG)
	./$(PROG)

$(PROG) : $(SRC) //fichier.h
		gcc -Wall -o $(PROG) $(SRC)

clean :
	rm -f $(PROG)
