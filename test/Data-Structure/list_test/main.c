#include "adt/list.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    list_t *list = list_create(NULL, NULL);
    for (int i = 0;i < 10;++i) {
        int *data = (int *)malloc(sizeof(int));
        *data = i*2;
        list_push_back(list, data);
    }

    list_node_t *cur;
    list_for_each(list, cur) {
        printf("%d ", *(int *)cur->data);
    }
    list_destroy(list);

    return 0;
}