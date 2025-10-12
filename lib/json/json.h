#ifndef JSON_H
#define JSON_H


/**
* Permet de définir les différents types d'elements utiliser dans le json scalaire
* - JSON_STRING: Scalaire chaîne de caractère [char*]
* - JSON_NUMBER: Scalaire nombre entier [int]
* - JSON_FLOAT: Scalaire nombre flottant [float]
* - JSON_DOUBLE: Scalaire nombre double [double]
* - JSON_BOOLEAN: Scalaire boolean [boolean]
*
* Remarque: Un conteneur est un objet ou un tableau
* Remarque: Json est un conteneur
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
typedef enum JsonScalarType {
  JSON_STRING,
  JSON_NUMBER,
  JSON_FLOAT,
  JSON_DOUBLE,
  JSON_BOOLEAN,
};

/**
* Permet de définir les différents types d'elements utiliser dans le json conteneur
* - JSON_OBJECT: Objet json
* - JSON_ARRAY: Tableau json
* 
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
typedef enum JsonContainerType {
  JSON_OBJECT,
  JSON_ARRAY,
};

/**
* Permet de définir les différents types d'elements utiliser dans le json
* Utiliser pour transformer le json en tableau de caractères
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
typedef enum JsonElementType = JsonScalarType | JsonContainerType;

/**
* Définit les champs et méthodes utiliser par les containeurs et scalaires
* 
* @Field key {char*} - Clé de l'élément
* @Field value {void*} - Valeur de l'élément (char*, int, float, double, boolean)
* @Field next {void*} - Pointeur sur le prochain élément du containeur
* @Field previous {void*} - Pointeur sur le précédent élément du containeur
* 
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
typedef struct JsonElement JsonElement {
  char *key;
  void *value;
  void *next;
  void* previous;
};

/**
* Permet de rajouter un scalaire
* 
* @Field type {JsonScalarType} - Type de l'élément scalaire
* @Method toCharArray {char*} - Transforme la structure en tableau de caractères
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
struct JsonScalar union JsonElement {
  JsonScalarType type;
};

/**
* Permet de rajouter un conteneur
* @Field type {JsonContainerType} - Type de l'élément conteneur
* @Field length {int} - Nombre d'éléments du conteneur
* @Field first {void*} - Pointeur sur le premier élément que cette instance contient
* @Field last {void*} - Pointeur sur le dernier élément que cette instance contient
* @Method addJsonElement {void} - Ajoute un élément au conteneur [à first]
* @Method toCharArray {char*} - Transforme la structure en chaine de caractères
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
struct JsonContainer union JsonElement {
  JsonContainerType type;
  int length;
  void *first;
  void *last;

  void (*addJsonElement)(JsonElement *this, void *add);
  char* (*toCharArray)(JsonElement *this);
};

/**
* Point de départ du json, permet de contenir tout le json dans une seul instance
* @Field node {JsonContainer*} - Pointeur sur le premier élément du json
* @Method addJsonElement {void} - Ajoute un élément au json [à node]
* @
* @Method toCharArray {char*} - Transforme le json en chaine de caractères
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
struct Json {
  // Première elements du json
  JsonContainer *node;

  void (*addJsonElement)(Json *this, void *add);
  char* (*toCharArray)(Json *this);
};

/**
* Permet de créer un json
*
* @Return {Json*} - Pointeur sur le json créé
* @Params node {JsonContainer*} - Pointeur sur le premier élément du json
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
Json* create_Json(JsonContainer *node);

/**
* Permet de créer un conteneur json
* L'utilisateur modifiera par la suite les elements suivant dans le conteneur via la méthode addJsonElement de l'instance :
* - next
* - previous
* - first
* - last
* - length
*
* @Return {JsonContainer*} - Pointeur sur le json créé
* @Params node {JsonContainerType*} - Type de conteneur
* @Params key {char*} - Clé de l'élément
* @Params value {void*} - Valeur de l'élément
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
JsonContainer* create_JsonContainer(JsonContainerType type, char *key, void *value);

/**
* Permet de créer un scalaire json
*
* @Return {Json*} - Pointeur sur le json créé
* @Params node {JsonContainer*} - Pointeur sur le premier élément du json
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 12/10/2025
* @UpdatedOn 12/10/2025
*/
JsonScalar* create_JsonScalar(JsonScalarType type, char *key, void *value);

# endif // JSON_H