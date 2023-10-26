#include "linked_list.h"

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
};


struct list *list_create(void)
{
    struct list *l = (struct list *)malloc(sizeof(struct list));   

    l->first = 0;
    l->last = 0;
    
    return l;
}


size_t list_count(const struct list *list)
{
    size_t num_nodes = 1;
    struct list_node *aux_node;

    if (!list || !list->first)
        return 0;

    aux_node = list->first;    
    while (aux_node != list->last){
        aux_node = aux_node->next;
        num_nodes++;
    }

    return num_nodes;
}


void list_push(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node;
    
    if (!list)
        return;

    new_node = (struct list_node *)malloc(sizeof(struct list_node));
    if (!new_node)
        return;
    new_node->data = item_data;
    new_node->next = 0;

    if (!list->first){
        list->first = new_node;
        list->last = new_node;
        new_node->prev = 0;
    }
    else {
        new_node->prev = list->last;
        list->last->next = new_node;
        list->last = new_node;
    }
}


ll_data_t list_pop(struct list *list)
{
    ll_data_t data;

    if (!list || !list->first)
        return 0;

    data = list->last->data;

    if (list->last == list->first){
        free(list->last);
        list->first = 0;
        list->last = 0;
    }
    else {
        list->last = list->last->prev;
        free(list->last->next);
        list->last->next = 0;
    }

    return data;
}


void list_unshift(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node;
    
    if (!list)
        return;

    if (!list->first){
        list_push(list, item_data);
        return;
    }
    
    new_node = (struct list_node *)malloc(sizeof(struct list_node));
    if (!new_node)
        return;
    new_node->data = item_data;
    new_node->prev = 0;
    
    new_node->next = list->first;
    list->first = new_node;
}


ll_data_t list_shift(struct list *list)
{
    ll_data_t data;
    
    if (!list || !list->first)
        return 0;

    if (list->last == list->first)
        return list_pop(list);

    data = list->first->data;

    list->first = list->first->next;
    free(list->first->prev);
    list->first->prev = 0;

    return data;
}


void list_delete(struct list *list, ll_data_t data)
{
    struct list_node *aux_node;

    if (!list || !list->first)
        return;

    if (list->first->data == data){
        list_shift(list);
        return;
    }

    if (list->last->data == data){
        list_pop(list);
        return;
    }

    aux_node = list->first;
    for (int founded = 0; founded == 0 && aux_node != 0; aux_node = aux_node->next){
        if (aux_node->data == data){
            aux_node->prev->next = aux_node->next;
            aux_node->next->prev = aux_node->prev;
            free(aux_node);
            founded = 1;
        }
    }
}


void list_destroy(struct list *list)
{
    struct list_node *aux_node;

    if (!list)
        return;

    if (list->first){
        for (aux_node = list->first->next; aux_node != 0; aux_node = aux_node->next)
            free(aux_node->prev);
        free(list->last);
    }

    free(list);
}
