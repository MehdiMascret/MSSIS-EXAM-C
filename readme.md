# Sur windows
- Pour ne pas devoir taper `mingw32-make` mais `make` faire : 
  - Windows : `Set-Alias make mingw32-make`
  - Git bash : `alias make='mingw32-make'`
# Conventions
## Repertoires
```
|
+-> dict: 
+-> main: Dossier qui contient les code en `c` du programme
+--> main.c: Fichier pour lancer le programme
+--> G: Dossier qui gère l'option G
+--> L: Dossier qui gère l'option L
+-> lib: Ensemble des librairies nécessaire dans le programme sans correspondance avec les options
+--> arg: Regroupe les valeurs des arguments dans l'options 
+-> Makefile: Fichier permettant de lancer des commandes make
```

- Les fichiers dit `main` sont les fichiers qui ont le même nom que leurs repertoires
- Les fichier `main` peuvent être appeller en exterrieur de son repertoire.
- Par contre les fichiers qui ne sont pas `main` servent uniquement au fichier `main` donc de leurs rerpertoire.

### Signification des symbole
- `|` repertoire projets
- `+->` fichier ou dossier

**Remarque** : 
- On commence par `+->` (par example: `+-> lib`) pour une meuilleur lisibilité
- S'il y a un `-` en plus que celui du son prédécesseur, cela signifie qu'il est dans son repertoire

## Documentation du code
### Base
Ces lignes de commentaires sont utilisés par les structures et les fonctions afin de décrire leurs foncitonnements :

```c
/* -- Ligne vide pour plus de lisibilité  --
 - Explications toujours au début
 - /!\ Message de warning
 - `code en c`
 - 
 - ` code en c
 -  sur plusieurs
 -  ligne !
 - `
 -- Remarque: Ceci est une remarque dont les informations
 -- se suivent afin de ne pas avoir de long texte sous
 -- une seul ligne, il sont toujours après les explications
 -  
 -- Remarque: Ceci est une autre remarque assez longue
 -- qui n'a pas aucun rapport avec la précedente
 -- remarque !
 -
 - @Version X.Y
 - @Author Mascret Mehdi
 - @CreatedOn date
 - @UpdatedOn date
*/
```
- `@Version` est la version du code
  - `X` represente une nouvelle version
  - `Y` represente une sous version
- `@Author` est uniquement pour me référencer 😉
- `@CreateOn` est la date de création
- `@UpdatedOn` est la date de modification
- Les longues remarques sont représenter par un `--`
  - Ils sont séparer par un commentaire vide
  - Ils sont a la fin de l'explication

### Structures
- Les elements sont rajouter avant `@Version`
- Les structures inclurons des des méthodes comme en Orienté Objet.
- Pour accéder aux données de la structures il include un pointeur qui pointe sur la structure en elle même
```c
/*
 * @Lambda lambdaName {type} - Fonction lambda
 * @Field fieldName {type} - Explication du field
 * @Method methodName {type}	- Explication de la méthode
 * @Method:Arg{methodName} argumentName {type} - Explication de l'argument de la fonction
*/
```
**Explications**
- `@Lambda`, `@Field`, `@Method` et `@Method:Arg` peuvent utilisé le même format pour les remarques et les explications. 
  - Ceux ci servent à donner plus d'explication
- `{type}` est le type utilisé
  - Retourner pour les méthodes
  - Utilisé pour les champs des structures ou arguments des fonctions
- `lambdaName` est le nom du champ de la fonction lambda
- `fieldName` est le nom du champ
- `methodName` est le nom de la méthod
- `argumentName` est le nom de l'argument


**On mettra toujours** un pointeur, en première position des méthodes de structure, qui seront du même type que la structure qui la possède, **afin** de pouvoir accéder aux champs de la structure.


### Fonctions
- Les elements sont rajouter avant `@Version`
```c
/*
 - @Return {type}	- Explication du retour
 - @Param paramName {type}	- Explication de l'argument de la fonction
/*
```
**Explications**
- `{type}` est le type utilisé (types primitif [char, int, float, ...])
  - Retourner pour les méthodes
  - Utilisé pour les arguments des fonctions

## Nommages
- Le nom des structures sont aux format `UpperCamelCase`
- Le nom des fonction dans les structures sont en format `camelCase`
- Les variables et les champs de structures sont en `camelCase`
- Pour create une structure ont la définit par `create_StructureName`

## Méthodes dans une structures
- Le code des méthodes dans les structures seront définit dans le fichier **code** qui leur sont associés.
- Leurs définition auront ce format : `${StructureName_methodName}`
  - On remarquera que ceux qui n'ont pas le nom de la structure seront des fonctions utilisé par autres méthodes nécessaire au `header`

# Programme
## Fonctionnement
Deux fonctionnalités principales existes :
- G, pour générer un 
## Listes des erreurs de retour
- 1 : Argv ne contient pas d'options attendu. Options attendu :
  - -L
  - -G
