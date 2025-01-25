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

void list_destroy(list_t **list)
{
    if (list == NULL || *list == NULL)
        return;

        node_t *current = (*list)->head;
        node_t *next;

        for (size_t i = 0; i < (*list)->size; i++)
        {
            next = current->next;
            (*list)->destroy_data(current->data);
            free(current);
            current = next;
        }

        free(*list);
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

    if (list->head == NULL)
    {
        // Initialize the sentinel node
        list->head = (node_t *)malloc(sizeof(node_t));
        if (list->head == NULL)
        {
            free(new_node);
            return NULL;
        }
        list->head->next = list->head;
        list->head->prev = list->head;
    }

    // Insert new_node before the sentinel node
    new_node->next = list->head;
    new_node->prev = list->head->prev;
    list->head->prev->next = new_node;
    list->head->prev = new_node;

    list->size++;

    return list;
}

void *list_remove_index(list_t *list, size_t index) {
        if (list == NULL || list->head == NULL || index >= list->size) {
            return NULL;
        }

        node_t *current = list->head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        void *data = current->data;

        if (current->next == current) {
            list->head = NULL;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            if (current == list->head) {
                list->head = current->next;
            }
        }

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

        node_t *current = list->head;
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
