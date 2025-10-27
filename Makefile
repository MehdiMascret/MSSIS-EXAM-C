# Pour ne pas afficher les commandes
.SILENT:

# Appeler gcc avec toute ses options en un seul mot $(GCC)
ADD_WARNING = -Wall -Wextra
GCC = gcc -std=c11 -g

# Trouver tous les fichiers .c
ALL_CODES := $$(find . -name '*.c' -type f)

# Compiler tous les fichiers .c dans target
compile: clean
	mkdir -p target
	# Pour chaque fichier .c, créer le fichier .o dans target
	for code in $(ALL_CODES); do \
		# Trouver le path de l'output\
		# %.c permet de supprimer l'extension .c\
		output="target/$${code%.c}.o"; \
		# Créer le répertoire du fichier .o dans target à partir du dossier d'output\
		mkdir -p $$(dirname "$$output"); \
		# Compiler le fichier .c en .o\
		echo "Compilation de $$output"; \
		$(GCC) -c "$$code" -o "$$output"; \
	done
	$(GCC) -o target/src/main $$(find target -name '*.o' -type f) -lcrypto\
	
# Supprime tout les fichiers compilés
clean:
	rm -rf target

# Compile, clear le page puis lance l'application
run: compile
	./target/src/main $$RUN_ARGS
