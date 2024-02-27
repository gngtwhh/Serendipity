/**
 * @file list.c
 * @brief List implementation
 * @author WAHAHA
 * @category data-structure
 * @date 2024
 */

#include <adt/list.h>
#include <stdlib.h>


 /* typedef struct list_node_s {
     void *data;
     struct list_node_s *next;
 } list_node_t;

 typedef struct list_s {
     list_node_t *head;
     list_node_t *tail;
     size_t size;
     int (*compare)(const void *, const void *);
     void (*destroy)(void *);
 } list_t; */


 /* list operations */
list_t *list_create(int (*compare)(const void *, const void *),
    void (*destructor)(void *)) {
    list_t *new_list = (list_t *)malloc(sizeof(list_t));
    if (new_list == NULL)
        return NULL;
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;
    /* @warning the two function pointer should be checked in other functions */
    new_list->compare = compare;
    new_list->destructor = destructor;
    return new_list;
}

status list_destroy(list_t *list) {
    // if (list == NULL)
        // return error;
    ASSERT(list != NULL, error);
    list_node_t *temp = list->head;
    list_node_t *next = NULL;
    /**
     * Dispute! Whether list_destroy() should fail if destructor equals to NULL
     * current implementation: just free every data of the nodes
    */
    if (list->destructor == NULL) {
        while (temp != NULL) {
            next = temp->next;
            free(temp->data);
            free(temp);
            temp = next;
        }
    } else {
        while (temp != NULL) {
            next = temp->next;
            list->destructor(temp->data);
            free(temp);
            temp = next;
        }
    }
    free(list);
    return true;
}

status list_insert(list_t *list, size_t index, void *data) {
    /* if the list is NULL, return error */
    // if (list == NULL)
        // return error;
    ASSERT(list != NULL, error);
    list_node_t *new_node = (list_node_t *)malloc(sizeof(list_node_t));
    /* check if malloc failed */
    // if (new_node == NULL)
        // return failed;
    ASSERT(new_node != NULL, failed);

    new_node->data = data;
    new_node->next = NULL;

    /* check if index out of range */
    ASSERT(index <= list->size, error);

    /* insert to the head */
    if (index == 0) {
        new_node->next = list->head;
        list->head = new_node;
        if (list->size == 0)
            list->tail = new_node;
    }
    /* insert to the tail */
    else if (index == list->size) {
        list->tail->next = new_node;
        list->tail = new_node;
        // no need to check if list->size == 0
    }
    /* insert to the middle */
    else {
        list_node_t *prev = list->head;
        for (size_t i = 0; i < index - 1; i++)
            prev = prev->next;
        new_node->next = prev->next;
        prev->next = new_node;
    }
    list->size++;
    return true;
}

status list_remove(list_t *list, size_t index, void **data) {
    /* if the list is NULL or empty, return error */
    // if (list == NULL || list->size == 0)
        // return error;
    ASSERT(list != NULL && list->size != 0, error);

    /* check if index out of range */
    ASSERT(index < list->size, error);

    list_node_t *temp = list->head;
    list_node_t *prev = NULL;

    /* remove the head */
    if (index == 0) {
        list->head = temp->next;
        *data = temp->data;
        free(temp);
        if (list->size == 1)
            list->tail = NULL;
    }
    /* remove the tail */
    else if (index == list->size - 1) {
        for (size_t i = 0; i < index - 1; i++)
            temp = temp->next;
        *data = temp->next->data;
        free(temp->next);
        temp->next = NULL;
        list->tail = temp;
    }
    /* remove the middle */
    else {
        for (size_t i = 0; i < index; i++) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        *data = temp->data;
        free(temp);
    }
    list->size--;
    return true;
}

status list_push_front(list_t *list, void *data) {
    return list_insert(list, 0, data);
}

status list_push_back(list_t *list, void *data) {
    return list_insert(list, list->size, data);
}

/* get the status of list */

/**
 * this function has rewritten as a macro in list.h 
size_t list_size(list_t *list) {
    if (list == NULL) {
        fprintf(stderr, "[%s]:%s:%d is failed! error code: %d\r\n",
            __FILE__, __FUNCTION__, __LINE__, error);
        return 0;
    }
    return list->size;
}
*/

/**
 * this function has rewritten as a macro in list.h
status list_empty(list_t *list) {
    ASSERT(list != NULL, error);
    return list->size == 0 ? true : false;
}
*/

/* get the data of list */

/**
 * this function has rewritten as a macro in list.h
void *list_front(list_t *list) {
    if (list == NULL || list->size == 0)
        return NULL;
    return list->head->data;
}
 */

 /**
  * this function has rewritten as a macro in list.h
 void *list_back(list_t *list) {
     if (list == NULL || list->size == 0)
         return NULL;
     return list->tail->data;
 }
  */

void *list_get(list_t *list, size_t index) {
    if (list == NULL || list->size == 0 || index >= list->size)
        return NULL;
    list_node_t *temp = list->head;
    for (size_t i = 0; i < index; i++)
        temp = temp->next;
    return temp->data;
}