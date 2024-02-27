/**
 * @file list.h
 * @brief This is a header file that contains the declaration of list data structure.
 * @author WAHAHA
 * @category data-structure
 * @date 2024
 */

#ifndef _LIST_H_
#define _LIST_H_

 /* pre-initialization of ADT */
#include "adt_pre_init.h"

/* list node structure */
typedef struct list_node_s {
    void *data;
    struct list_node_s *next;
} list_node_t;

/* list structure */
typedef struct list_s {
    list_node_t *head;
    list_node_t *tail;
    size_t size;
    int (*compare)(const void *, const void *);
    void (*destructor)(void *);
} list_t;

/* macro for list operations */
#define list_size(list) ((list)->size)
#define list_empty(list) ((list)->size == 0)
#define list_front(list) ((list)->head->data)
#define list_back(list) ((list)->tail->data)


/* list operations */
list_t *list_create(int (*compare)(const void *, const void *),
    void (*destroy)(void *));
status list_destroy(list_t *list);
status list_insert(list_t *list, size_t index, void *data);
status list_remove(list_t *list, size_t index, void **data);
status list_push_front(list_t *list, void *data);
status list_push_back(list_t *list, void *data);

/* get the status of list */
// size_t list_size(list_t *list);
// status list_empty(list_t *list);

/* get the data of list */
// void *list_front(list_t *list);
// void *list_back(list_t *list);
void *list_get(list_t *list, size_t index);

#endif