#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DYNAMICARRAY_T
#  define DYNAMICARRAY_T
typedef struct dynamic_array
{
	void** dynamic_array;
	int array_capacity;
	int array_size;
}dynamic_array_t, *dynamicarray_ptr_t;
#endif

typedef int status;

dynamicarray_ptr_t initialize_dynamic_array(int initial_capacity_size);
status insert_array_element(dynamicarray_ptr_t dynamic_array, int insert_position, void* insert_data);
status delete_array_element(dynamicarray_ptr_t dynamic_array, int insert_position, void** reserved);
status print_array_element(dynamicarray_ptr_t dynamic_array);

int main()
{
	dynamicarray_ptr_t array = initialize_dynamic_array(20);
	return 0;
}

dynamicarray_ptr_t initialize_dynamic_array(int initial_capacity_size)
{
	if(initial_capacity_size <= 0)
	{
		return NULL;
	}
	
	dynamicarray_ptr_t dynamic_array = (dynamicarray_ptr_t)malloc(sizeof(dynamic_array_t));
	
	if(dynamic_array == NULL)
	{
		return NULL;
	}
	
	dynamic_array->dynamic_array = (void**)malloc(sizeof(void*) * initial_capacity_size);
	if(dynamic_array->dynamic_array == NULL)
	{
		return NULL;
	}
	
	memset(dynamic_array->dynamic_array, 0, sizeof(void*) * initial_capacity_size);
	
	return dynamic_array;
}
