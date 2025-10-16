# Pour ne pas afficher les commandes
.SILENT:

# Appeler gcc avec toute ses options en un seul mot $(GCC)
GCC = gcc -std=c11 -Wall -Wextra -g

# Trouver tous les fichiers .c
ALL_CODES := $$(find . -name '*.c' -type f)

# Compiler tous les fichiers .c dans target
compile: clean
	mkdir -p target
	# Pour chaque fichier .c, créer le fichier .o dans target
	for code in $(ALL_CODES); do \
		# Trouver le path de l'output\
		# %.c=.o permet de transformer l'extension .c en .o\
		output="target/$${code%.c=.o}"; \
		# Créer le répertoire du fichier .o dans target à partir du dossier d'output\
		mkdir -p $$(dirname "$$output"); \
		# Compiler le fichier .c en .o\
		echo "Compilation de $$output"; \
		$(GCC) -c "$$code" -o "$$output"; \
	done

# Supprime tout les fichiers compilés
