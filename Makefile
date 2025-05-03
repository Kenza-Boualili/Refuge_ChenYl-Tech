# Makefile pour structure src/include/obj/bin (OS-Agnostic Target Name)
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
DATADIR = data
SRCS_FILES = main.c animal.c affichage.c ajouterAnimal.c adopterAnimal.c \
             rechercherAnimaux.c inventaire.c nourriture.c retourmenu.c \
             utils.c comparer.c id.c nettoyeur.c
SRCS = $(patsubst %,$(SRCDIR)/%,$(SRCS_FILES))
OBJS = $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS_FILES)))
TARGET_NAME = chenil
TARGET = $(BINDIR)/$(TARGET_NAME)
all: $(TARGET)
$(TARGET): $(OBJS) | $(BINDIR)
	    @echo "Linking $(TARGET)..."
	    $(CC) $(OBJS) $(LDFLAGS) -o $@
	    @echo "Executable $(TARGET) created."
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h) | $(OBJDIR)
	    @echo "Compiling $<..."
	    $(CC) $(CFLAGS) -c $< -o $@
$(BINDIR):
	    mkdir -p $(BINDIR)
$(OBJDIR):
	    mkdir -p $(OBJDIR)
clean:
	    @echo "Cleaning build files..."
	    rm -rf $(OBJDIR)
	    rm -rf $(BINDIR)
	    @echo "Clean finished."
.PHONY: all clean
