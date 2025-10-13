#include "list.h"
#include <stdbool.h> 
#include <stdlib.h> 

List* List_map(
    List *this, 
    List_LambdaMap lambda
) {
    List* list = create_List();

    ListElement *current;
    int index;
    
    if (this->sens == ListSens_NORMAL) {
        current = this->first;
        index = 0;
    } else {
        current = this->last;
        index = this->length - 1;
    }
    
    while (current) {
        void *valueTransformed = lambda(index, current->value);
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

void List_forEach(
    List *this, 
    List_LambdaForEach lambda
) {
    ListElement *current;
    int index;

    if (this->sens == ListSens_NORMAL) {
        current = this->first;
        index = 0;
    } else {
        current = this->last;
        index = this->length - 1;
    }

    while (current) {
        lambda(index, current->value);

        if (this->sens == ListSens_NORMAL) {
            current = current->next;
            index++;
        } else {
            current = current->previous;
            index--;
        }
    }
}

void List_add(
    List *this, 
    void *value,  
    List_Lambdafree *free
) {
    ListElement* element = (ListElement*) malloc(sizeof(ListElement));

    element->value = value;
    element->previous = NULL;
    element->next = NULL;
    element->free = free;

    if (this->length == 0) {
        this->first = element;
        this->last = element;
    } else if (this->sens == ListSens_NORMAL) {
        this->last->next = element;
        element->previous = this->last;
        this->last = element;
    } else {
        this->first->previous = element;
        element->next = this->first;
        this->first = element;
    }
    this->length = this->length+1;
}

void List_free(List* this) {
    ListElement *current;
    int index;

    if (this->sens == ListSens_NORMAL) {
        current = this->first;
        index = 0;
    } else {
        current = this->last;
        index = this->length - 1;
    }

    ListElement *toBeFree;

    while (current) {
        current->free(index, current->value);
        toBeFree = current;

        if (this->sens == ListSens_NORMAL) {
            current = current->next;
            index++;
        } else {
            current = current->previous;
            index--;
        }
        free(toBeFree);
    }
    free(this);
}

void* List_pop(List *this) {
    if (this->length == 0) return NULL;

    ListElement *current = this->sens == ListSens_NORMAL
        ? this->first
        : this->last;
    void* value = current->value;

    if (this->length == 1) {
        this->first = NULL;
        this->last = NULL;
    }

    if (this->sens == ListSens_NORMAL) {
        this->last = current->previous;
        this->last->next = NULL;
    } else {
        this->first = current->next;
        this->first->previous = NULL;
    }

    free(current);
    this->length = this->length - 1;
    return value;
}

List* create_List() {
    List* list = (List*) malloc(sizeof(List));
    
    list->first = NULL;
    list->last = NULL;
    list->sens = ListSens_NORMAL;

    list->forEach = List_forEach;
    list->map = List_map;
    list->add = List_add;
    list->free = List_free;

    return list;
}
