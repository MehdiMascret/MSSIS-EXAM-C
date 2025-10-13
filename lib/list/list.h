#ifndef LIB_LIST_H
#define LIB_LIST_H

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
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*/
typedef void List_LambdaForEach(int index, void *element);

/*
* Fonctions lambda pour la fonction map de la structure List
*
* Permet à l'utilisateur de facilité son parcours 
* un à un des elements de la liste puis un ajout en
* fin dans une nouvelle liste
* 
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*/
typedef void* List_LambdaMap(int index, void *element);


/*
* Fonctions lambda pour la fonction free de la structure List
*
* Permet à l'utilisateur de facilité la libération de la mémoire
* 
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*/
typedef void List_Lambdafree(int index, void *element);

/*
* Utiliser pour stocker les elements de la list
*
* @Field next {ListElement*} - contient le pointer du prochain elements de la liste
* @Field previous {ListElement*} - contient le pointer du précédent élements de la liste
* @Field value {void*} - Pointeur vers la valeur
* @Field free {List_Lambdafree} - Permet de définir comment supprimer l'element lors de son free
*
* @Version 1.0
* @Author Mascret Mehdi
* @CreatedOn 13/10/2025
* @UpdatedOn 13/10/2025
*
*/
typedef struct ListElement ListElement;
struct ListElement {
    ListElement* next;
    ListElement* previous;
    void* value;
    List_Lambdafree free;
};


/*
* Structure permettant de simplifier l'utilisation des listes
*
* @Field first {ListElement*} - Pointer du première element de la liste
*
* @Field last {ListElement*} - Pointer du dernière element de la liste
*
* @Field sens {ListSens} - Sens de lecture utilisé par les méthodes de la structure
*    que se soit en création, en parcours ou en suppréssion
*
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
typedef struct List List;
struct List {
    ListElement *first;
    ListElement *last;
    ListSens sens;
    int length;

    void forEach(List *this, List_LambdaForEach *lambda);
    List* map(List *this, List_LambdaMap *lambda);
    void add(List *this, void *value, List_Lambdafree *free);
    void* pop(List *this);
    void free(List *this);
};

List* create_List();

#endif // LIB_LIST_H