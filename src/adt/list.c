/**
 * @file: list.c
 * @description: List implementation
 * @author: WAHAHA
 * @Date: 2024-02-28 11:06:35
 * @LastEditTime: 2024-03-04 12:44:43
 * @FilePath: \Serendipity\src\adt\list.c
 * @category: data-structure
 */

#include <adt/list.h>
#include <stdlib.h>


 /**
 typedef struct list_node_s {
     void *data;
     struct list_node_s *next;
 } list_node_t;

 typedef struct list_s {
     list_node_t *head;
     list_node_t *tail;
     size_t size;
     int (*compare)(const void *, const void *);
     void (*destroy)(void *);
 } list_t;
 */


 /* list operations */
 /**
  * @Funticon name: list_create
  * @description: create a new list
  * @Author: WAHAHA
  * @Date: 2024-03-04 12:31:04
  * @Note: the 2 param are allowed to be NULL
  * @param {void} *
  * @param {void} *
  * @return {list_t *}
  */
list_t *list_create(int (*compare)(const void *, const void *),
    void (*destructor)(void *))
{
    list_t *new_list = (list_t *)malloc(sizeof(list_t));
    if (new_list == NULL)
        return NULL;
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;
    /* @warning: the two function pointer should be checked in other functions */
    /* @todo: the compare function is not used in the current implementation */
    new_list->compare = compare;
    new_list->destructor = destructor;
    return new_list;
}

/**
 * @Funticon name: list_destroy
 * @description: destroy the list
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:33:52
 * @Note: None
 * @param {list_t} *list
 * @return {status}
 */
status list_destroy(list_t *list)
{
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

/**
 * @Funticon name: list_insert
 * @description: insert data to the list
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:35:29
 * @Note: None
 * @param {list_t} *list
 * @param {size_t} index
 * @param {void} *data
 * @return {status}
 */
status list_insert(list_t *list, size_t index, void *data)
{
    /* if the list is NULL, return error */
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

/**
 * @Funticon name: list_remove
 * @description: remove data from the list
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:36:29
 * @Note: the removed data pointer will be stored
 * @param {list_t} *list
 * @param {size_t} index
 * @param {void *} *data
 * @return {status}
 */
status list_remove(list_t *list, size_t index, void **data)
{
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


/**
 * @Funticon name: list_push_front
 * @description: push data to the front of the list
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:38:10
 * @Note: call list_insert(list, 0, data)
 * @param {list_t} *list
 * @param {void} *data
 * @return {status}
 */
status list_push_front(list_t *list, void *data)
{
    return list_insert(list, 0, data);
}

/**
 * @Funticon name: list_push_back
 * @description: push data to the back of the list
 * @Author: WAHAHA
 * @Date: 2024-03-04 12:39:37
 * @Note: call list_insert(list, list->size, data)
 * @param {list_t} *list
 * @param {void} *data
 * @return {status}
 */
status list_push_back(list_t *list, void *data)
{
    return list_insert(list, list->size, data);
}

/* @note: these functions has rewritten as macros in list.h */


/* get the status of list */

/**
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
status list_empty(list_t *list) {
    ASSERT(list != NULL, error);
    return list->size == 0 ? true : false;
}
*/

/* get the data of list */

/**
void *list_front(list_t *list) {
    if (list == NULL || list->size == 0)
        return NULL;
    return list->head->data;
}
*/

/**
void *list_back(list_t *list) {
    if (list == NULL || list->size == 0)
        return NULL;
    return list->tail->data;
}
*/

/**
* @Funticon name: list_get
* @description: get the data of the list
* @Author: WAHAHA
* @Date: 2024-03-04 12:40:08
* @Note: return NULL if the list is NULL or empty
* @param {list_t} *list
* @param {size_t} index
* @return {void *}
*/
void *list_get(list_t *list, size_t index)
{
    if (list == NULL || list->size == 0 || index >= list->size)
        return NULL;
    list_node_t *temp = list->head;
    for (size_t i = 0; i < index; i++)
        temp = temp->next;
    return temp->data;
}