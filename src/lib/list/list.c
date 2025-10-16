#include "list.h"
#include <stdbool.h> 
#include <stdlib.h> 

/* 
* Permet de libérer le pointeur sur :
*   - La valeur via la fonction lambda free
*   - Le conteneur de la valeur
*   - Le conteneur de l'element
*
* @Param container {ListContainer*} - Pointer à libérer et son ensemble
*/
void free_ListContainer(ListContainer* container) {
    ListElement* element = container->element;
    element->free(element->value);
    free(element);
    free(container);
}

/*
*   Créer une nouvelle liste à partir des elements da la liste actuelle.
*   Ses élements sont transformer via la fonciton lambda
*
*   @Param lambda {List_LambdaMap*} - Fonction lambda qui permet de la transformation d'un element en un autre
*/
List* List_map(
    List *this, 
    List_LambdaMap lambda
) {
    List* list = create_List();

    ListContainer *current;
    int index;
    
    if (this->sens == ListSens_NORMAL) {
        current = this->first;
        index = 0;
    } else {
        current = this->last;
        index = this->length - 1;
    }
    
    while (current) {
        void *valueTransformed = lambda(index, current->element);
        list->add(list, valueTransformed);

        if (this->sens == ListSens_NORMAL) {
            current = current->next;
            index++;
        } else {
            current = current->previous;
            index--;
        }
    }

    return list;    
}

/**
 * Permet de parcourir les elements de la liste
 * 
 * @Param lambda {List_LambdaForEach} - Fonction lambda qui permet de transformer l'element
 */
void List_forEach(
    List *this, 
    List_LambdaForEach lambda
) {
    ListContainer *current;
    int index;

    if (this->sens == ListSens_NORMAL) {
        current = this->first;
        index = 0;
    } else {
        current = this->last;
        index = this->length - 1;
    }

    while (current) {
        lambda(index, current->element->value);

        if (this->sens == ListSens_NORMAL) {
            current = current->next;
            index++;
        } else {
            current = current->previous;
            index--;
        }
    }
}

/*
* Permet de rajoute un elements de la liste.
* Si le sens de la liste est normal alors l'element sera rajouter à la fin
* Si le sens de la liste est inversé alors l'element sera rajouter au début
*
* @Param element {ListElement*} - Element à rajouter à la liste
*/
void List_add(
    List *this, 
    ListElement *element
) {
    ListContainer* container = (ListContainer*) malloc(sizeof(ListContainer));

    container->element = element;
    container->previous = NULL;
    container->next = NULL;

    if (this->length == 0) {
        this->first = container;
        this->last = container;
    } else if (this->sens == ListSens_NORMAL) {
        this->last->next = container;
        container->previous = this->last;
        this->last = container;
    } else {
        this->first->previous = container;
        container->next = this->first;
        this->first = container;
    }
    this->length = this->length+1;
}

/*
* Permet de libérer la mémoire pointeur sur la liste de facon récursive
* Si le sens de la liste est normal alors on supprime en FILO
* Si le sens de la liste est inversé alors on supprime en FIFO
*
*/

void List_free(List* this) {
    ListContainer *current;
    int index;

    if (this->sens == ListSens_REVERSE) {
        current = this->first;
        index = 0;
    } else {
        current = this->last;
        index = this->length - 1;
    }

    ListContainer *toBeFree;

    while (current) {

        // Je met un tempo de ma position actuel via toBeFree
        // puis je passe à l'element suivant
        toBeFree = current;
        if (this->sens == ListSens_REVERSE) {
            current = current->next;
            index++;
        } else {
            current = current->previous;
            index--;
        }
        // Et enfin je libère l'element tempo
        free_ListContainer(toBeFree);
        
    }
    free(this);
}

void* List_pop(List *this) {
    if (this->length == 0) return NULL;

    ListContainer *current = this->sens == ListSens_NORMAL
        ? this->last
        : this->first;
    void* value = current->element;

    if (this->length == 1) {
        this->first = NULL;
        this->last = NULL;
    } else if (this->sens == ListSens_NORMAL) {
        this->last = current->previous;
        this->last->next = NULL;
    } else {
        this->first = current->next;
        this->first->previous = NULL;
    }

    free_ListContainer(current);
    this->length = this->length - 1;
    return value;
}

List* create_List() {
    List* list = (List*) malloc(sizeof(List));
    
    list->first = NULL;
    list->last = NULL;
    list->sens = ListSens_NORMAL;

    // list->forEach = List_forEach;
    // list->map = List_map;
    // list->add = List_add;
    // list->free = List_free;

    return list;
}
ListElement* create_ListElement(void* value, List_Lambdafree free) {
    ListElement* creator = (ListElement*) malloc(sizeof(ListElement));

    creator->value = value;
    creator->free = free;

    return creator;
}