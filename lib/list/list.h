#ifndef LIB_LIST_H
#define LIB_LIST_H

typedef struct ListElement ListElement;
typedef struct ListContainer ListContainer;
typedef struct List List;
typedef enum ListSens ListSens;

/*
* Utilisé par la structure List pour le sens de lecture de ses elements
* lors de l'appelle de ses méthodes
*
* @Key NORMAL  : FIFO Première élement entrer, Première element sorti
* @Key REVERSE : FILO Première élement entrer, Dernière element sorti
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*
*/
enum ListSens {
    ListSens_NORMAL,
    ListSens_REVERSE,
};

/*
* Fonctions lambda pour la fonction forEach de la structure List
* Permet à l'utilisateur de facilité son parcours un à un des elements de la liste
*
* @Param index {int} - Position dans la liste
* @Param value {void*} - Pointeur vers la position de la valeur
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*/
typedef void List_LambdaForEach(int index, void *value);

/*
* Fonctions lambda pour la fonction map de la structure List
*
* Permet à l'utilisateur de facilité son parcours 
* un à un des elements de la liste puis un ajout en
* fin dans une nouvelle liste
*
* @Param index {int} - Position dans la liste
* @Param value {void*} - Pointeur vers la position de la valeur
*
* 
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*/
typedef ListElement* List_LambdaMap(int index, void *value);
/*
* Fonctions lambda pour la fonction free de la structure List
* Permet à l'utilisateur de facilité la libération de la mémoire
* 
* @Param value {void*} - Pointeur vers la position de la valeur
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*/
typedef void List_Lambdafree(void *value);

/*
* Utiliser pour stocker la valeur et comment la free
*
* @Field value {void*} - Pointeur vers la valeur
* @Field free {List_Lambdafree} - Permet de définir comment supprimer l'element lors de son free
*/
struct ListElement {
    void* value;
    List_Lambdafree (*free);
};

/*
* Utiliser pour stocker les elements de la list
* Et comments pointers sur son prochain et précédent
*
* @Field next {ListContainer*} - contient le pointer du prochain elements de la liste
* @Field previous {ListContainer*} - contient le pointer du précédent élements de la liste
* @Field element {ListElement*} - Contient le pointeur vers la structure de la valeur et comment la détruire
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*
*/
struct ListContainer {
    ListContainer* next;
    ListContainer* previous;
    ListElement* element;
};


/*
* Structure permettant de simplifier l'utilisation des listes
*
* @Field first {ListElement*} - Pointer du première element de la liste
* @Field last {ListElement*} - Pointer du dernière element de la liste
* @Field sens {ListSens} - Sens de lecture utilisé par les méthodes de la structure
*    que se soit en création, en parcours ou en suppréssion
* @Field length {int} - Nombre d'element dans la liste
*
* @Method forEach - Apelle une fonction lambda pour chaque elements de la liste
* @Method:Arg{forEach} lambda - Fonction lambda définit par l'appelleur
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*
*/
struct List {
    ListContainer *first;
    ListContainer *last;
    ListSens sens;
    int length;

    void (*forEach)(List *this, List_LambdaForEach *lambda);
    List* (*map)(List *this, List_LambdaMap *lambda);
    void (*add)(List *this, ListElement *element);
    void* (*pop)(List *this);
    void (*free)(List *this);
};

List* create_List();
ListElement* create_ListElement(void* element, List_Lambdafree free);

#endif // LIB_LIST_H