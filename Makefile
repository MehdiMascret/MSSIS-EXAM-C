# Pour ne pas afficher les commandes
.SILENT:

# Appeler gcc avec toute ses options en un seul mot $(GCC)
GCC = gcc -std=c11 -Wall -Wextra -g


# Appeler par make en premier car c'est la première dépendance
# Créer l'executable
# Clean l'arborescence
compile: main.exe clean

# Trouver tous les fichiers .o et .a et les supprimer
clean:
	echo "Listes des fichiers creer lors de la compilation et qui seront supprimer:"
	find . -type f \( -name '*.o' -o -name '*.a' \)
	rm -rf target


main.exe: main.o L/main.a G/main.a
	$(GCC) main.o L/main.a G/main.a -o main.exe

L/main.a: L/main.o
	ar rcs L/main.a L/main.o

G/main.a: G/main.o
	ar rcs G/main.a G/main.o

# Compilation des fichiers .c en .o, example: L/main.c -> L/main.o
# $< est le premier prérequis de la cible
# $@ est la cible
%.o: %.c
# Créer le dossier dans target
	mkdir -p target/$(dir $@)
# Compiler le code
	$(GCC) -c $< -o target/$@

test: test/lib/test.o 
