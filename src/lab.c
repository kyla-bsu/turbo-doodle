#include "lab.h"

list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)) {
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (!list) {
        return NULL;
    }
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;
    list->head = (node_t *)malloc(sizeof(node_t));
    if (!list->head) {
        free(list);
        return NULL;
    }
    list->head->data = NULL;
    list->head->next = list->head;
    list->head->prev = list->head;
    return list;
}


void list_destroy(list_t **list) {
    if (list == NULL || *list == NULL) {
        return;
    }

    node_t *current = (*list)->head->next; // Start from the first actual node
    node_t *next;

    while (current != (*list)->head) { // Loop until we reach the sentinel node
        next = current->next;
        (*list)->destroy_data(current->data); // Free the data using the provided function
        free(current); // Free the node
        current = next;
    }

    free((*list)->head); // Free the sentinel node
    free(*list); // Free the list structure
    *list = NULL;
}

list_t *list_add(list_t *list, void *data)
{
    if (list == NULL || data == NULL)
    {
        return NULL;
    }

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->data = data;

  
    node_t *first = list->head->next;  // Get the current first node

    new_node->next = first;            // New node points to the current first node
    new_node->prev = list->head;       // New node points to the sentinel

    first->prev = new_node;            // Current first node now points back to the new node
    list->head->next = new_node;       // Sentinel's next is now the new node


    list->size++;

    return list;
}


void *list_remove_index(list_t *list, size_t index) {
    if (list == NULL || list->head == NULL || index >= list->size) {
        return NULL;
    }

    node_t *current = list->head->next; // Start from the first actual node
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    void *data = current->data;

    current->prev->next = current->next;
    current->next->prev = current->prev;

    free(current);
    list->size--;

    return data;
}

int list_indexof(list_t *list, void *data)
{
    if (list == NULL || data == NULL)
    {
        return -1;
    }

    node_t *current = list->head->next;
    int index = 0;

    do
    {
        if (list->compare_to(current->data, data) == 0)
        {
            return index;
        }
        current = current->next;
        index++;
    } while (current != list->head);

    return -1;
}
