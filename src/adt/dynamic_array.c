#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FN_IN_OUT_
#  define _FN_IN_OUT_
#  define _Fn_In_
#  define _Fn_Out_ 
#endif

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

dynamicarray_ptr_t initialize_dynamic_array(int _Fn_In_ initial_capacity_size);
status insert_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, int _Fn_In_ insert_position, void* _Fn_In_ insert_data);
status delete_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, int _Fn_In_ delete_position, void** _Fn_Out_ reserved);
status print_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, void (*print_func)(void* print_data));

void print_back_call(void* print_data)
{
	printf("%d ", *(int*)print_data);
}

int main()
{
	int v1 = 1;
	int v2 = 2;
	int v3 = 3;
	int v4 = 4;
	int v5 = 5;
	int ve = 100;
	int** re;
	
	dynamicarray_ptr_t array = initialize_dynamic_array(5);
//	insert_array_element(array, 0, &v1);
//	insert_array_element(array, 0, &v2);
//	insert_array_element(array, 0, &v3);
//	insert_array_element(array, 0, &v4);
//	insert_array_element(array, 0, &v5);
//	insert_array_element(array, 0, &ve);
//	insert_array_element(array, 0, &v1);
	insert_array_element(array, 0, &v1);
	insert_array_element(array, 4, &v2);
	insert_array_element(array, 2, &v3);
	delete_array_element(array, 1, (void**)&re);
	print_array_element(array, print_back_call);
	
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
	
	dynamic_array->array_size = 0;
	dynamic_array->array_capacity = initial_capacity_size;
	memset(dynamic_array->dynamic_array, 0, sizeof(void*) * initial_capacity_size);
	
	return dynamic_array;
}

status insert_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, int _Fn_In_ insert_position, void* _Fn_In_ insert_data)
{
	if(dynamic_array == NULL || insert_position < 0 || insert_data == NULL)
	{
		return -1;
	}
	
	if(insert_position > dynamic_array->array_size)
	{
		insert_position = dynamic_array->array_size;
	}
	
	int index;
	
	if(dynamic_array->array_size == dynamic_array->array_capacity)
	{
		dynamic_array->array_capacity *= 2;
		//printf("new size %d", dynamic_array->array_capacity);
		realloc(dynamic_array->dynamic_array,dynamic_array->array_capacity);
		
		for(index = dynamic_array->array_size; index >= insert_position; index--)
		{
			dynamic_array->dynamic_array[index + 1] = dynamic_array->dynamic_array[index];
		}
		dynamic_array->dynamic_array[insert_position] = insert_data;
		dynamic_array->array_size++;
		return 1;
	}
	else
	{
		for(index = dynamic_array->array_size; index >= insert_position; index--)
		{
			dynamic_array->dynamic_array[index + 1] = dynamic_array->dynamic_array[index];
		}
		dynamic_array->dynamic_array[insert_position] = insert_data;
		dynamic_array->array_size++;
		return 1;
		
	}
	
}

status print_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, void (*print_func)(void* print_data))
{
	if(dynamic_array == NULL)
	{
		return -1;
	}
	
	int index;
	
	for(index = 0 ; index < dynamic_array->array_size;index++)
	{
		(*print_func)(dynamic_array->dynamic_array[index]);
	}
	return 1;
}

status delete_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, int _Fn_In_ delete_position, void** _Fn_Out_ reserved)
{
	if(dynamic_array == NULL || delete_position < 0)
	{
		return -1;
	}
	
	if(delete_position >= dynamic_array->array_size)
	{
		return -1;
	}
	
	int index;
	
	if(reserved != NULL)
	{
		*reserved = dynamic_array->dynamic_array[delete_position];
	}
	
	for(index = delete_position; index < dynamic_array->array_size; index++)
	{
		dynamic_array->dynamic_array[index] = dynamic_array->dynamic_array[index + 1];
	}
	dynamic_array->array_size--; 
	return 0;
}
