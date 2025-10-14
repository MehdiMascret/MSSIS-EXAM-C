# Pour ne pas afficher les commandes
.SILENT:

# Appeler gcc avec toute ses options en un seul mot $(GCC)
GCC = gcc -std=c11 -Wall -Wextra -g
# Transformer le **.o sans son origin dans target en src/**.c
# Example : lib/list/list.o => src/lib/list/list.c
define getSrcFile
	$(eval tmp = $(addprefix src/, $1))
	$2 = $(tmp:o=c)
endef

# Appeler par make en premier car c'est la première dépendance
# Créer l'executable
# Clean l'arborescence
compile: main.exe clean

# Trouver tous les fichiers .o et .a et les supprimer
clean:
	echo "Listes des fichiers creer lors de la compilation et qui seront supprimer:"
	find . -type f \( -name '*.o' -o -name '*.a' \) -print -delete


main.exe: main.o L/main.a G/main.a
	$(GCC) main.o L/main.a G/main.a -o main.exe

L/main.a: L/main.o
	ar rcs L/main.a L/main.o

G/main.a: G/main.o
	ar rcs G/main.a G/main.o

# Compilation des fichiers .c en .o, example: L/main.c -> L/main.o
# $< est le premier prérequis de la cible
# $@ est la cible
%.o:
	$(eval $(call getSrcFile,$@,src))
	$(info src is : $(src))
	mkdir -p target/$(dir $@)
	$(GCC) -c $(src) -o target/$@	