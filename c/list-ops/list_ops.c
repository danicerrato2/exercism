#include "list_ops.h"

list_t *new_list(size_t length, list_element_t elements[])
{
    list_t *list = (list_t *)malloc(sizeof(list_t) + length * sizeof(list_element_t));

    if (!list)
        return 0;

    list->length = length;
    for (size_t i = 0; i < length && elements[i] != 0; i++)
        list->elements[i] = elements[i];

    return list;
}


list_t *append_list(list_t *list1, list_t *list2)
{    
    if (!list1 || !list2)
        return 0;

    size_t new_length = list1->length + list2->length;
    list_element_t new_elements[new_length];

    for (size_t i = 0; i < list1->length; i++)
        new_elements[i] = list1->elements[i];
    for (size_t i = 0; i < list2->length; i++)
        new_elements[list1->length + i] = list2->elements[i];
    
    return new_list(new_length, new_elements);
}


list_t *filter_list(list_t *list, bool (*filter)(list_element_t))
{    
    if (!list || !filter)
        return 0;

    list_element_t filtered_elements[list->length];
    size_t new_length = 0;
    
    for (size_t i = 0; i < list->length; i++){
        if (filter(list->elements[i]) == true)
            filtered_elements[new_length++] = list->elements[i];
    }

    return new_list(new_length, filtered_elements);
}


size_t length_list(list_t *list)
{
    if (!list)
        return 0;
    return list->length;
}


list_t *map_list(list_t *list, list_element_t (*map)(list_element_t))
{    
    if (!list || !map)
        return 0;

    list_element_t mapped_elements[list->length];
    
    for (size_t i = 0; i < list->length; i++)
        mapped_elements[i] = map(list->elements[i]);

    return new_list(list->length, mapped_elements);
}


list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t,
                                                  list_element_t))
{
    if (!list || !foldl)
        return 0;

    for (size_t i = 0; i < list->length; i++)
        initial = foldl(list->elements[i], initial);

    return initial;
}


list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t,
                                                  list_element_t))
{
    if (!list || !foldr)
        return 0;

    for (size_t i = list->length; i > 0; i--)
        initial = foldr(list->elements[i - 1], initial);

    return initial;
}


list_t *reverse_list(list_t *list)
{
    if (!list)
        return 0;

    list_element_t reversed_elements[list->length];
    
    for (size_t i = 0; i < list->length; i++)
        reversed_elements[i] = list->elements[list->length - 1 - i];

    return new_list(list->length, reversed_elements);
}


void delete_list(list_t *list)
{
    if (list)
        free(list);
}