#include "dynamic_array.h"
/**
* @file dynamic_array.c
* @brief dynamic array implementation
* @author inrootshell
* @category data-structure
* @date 2024-3-25
*/

/*
*@function name:initialize_dynamic_array
*@arguments:initialize dynamic array size
*@return type:dynamicarray_ptr_t
*@return value:success return a pointer failed return NULL
*/
dynamicarray_ptr_t initialize_dynamic_array(int initial_capacity_size)
{
	if(initial_capacity_size <= 0)  //if initialize size Less than or equal to zero
	{
		return NULL;  //return a null pointer
	}
	
	dynamicarray_ptr_t dynamic_array = (dynamicarray_ptr_t)malloc(sizeof(dynamic_array_t)); //allocate memory space
	
	if(dynamic_array == NULL)  //allocate fail
	{
		return NULL;           //return null 
	}
	
	dynamic_array->dynamic_array = (void**)malloc(sizeof(void*) * initial_capacity_size); //allocate array space
	if(dynamic_array->dynamic_array == NULL)  //allocate fail
	{
		return NULL;  //return null
	}
	
	//init array
	dynamic_array->array_size = 0; //array size zero
	dynamic_array->array_capacity = initial_capacity_size; //array capacity size = initial capacity size
	memset(dynamic_array->dynamic_array, 0, sizeof(void*) * initial_capacity_size);  //set memory space initial 0
	
	return dynamic_array;  //return dynamic array pointer
}

/*
*@function name:insert_array_element
*@arguments:dynamic array pointer, insert position and insert data
*@return type:status
*@return value:success return 1 failed return -1
*/
status insert_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, int _Fn_In_ insert_position, void* _Fn_In_ insert_data)
{
	if(dynamic_array == NULL || insert_position < 0 || insert_data == NULL) //pointer is null or position illegal or data pointer is null
	{
		return -1;  //return error code
	}
	
	if(insert_position > dynamic_array->array_size)  //if position The length of the array is exceeded
	{
		insert_position = dynamic_array->array_size; //tail insert
	}
	
	int index;
	
	if(dynamic_array->array_size == dynamic_array->array_capacity)  //If the array is already full
	{
		dynamic_array->array_capacity *= 2;                         //Expand the array
		realloc(dynamic_array->dynamic_array,dynamic_array->array_capacity);       //Reallocate memory size
		
		for(index = dynamic_array->array_size; index >= insert_position; index--)  //Move back one place from the specified position 
		{
			dynamic_array->dynamic_array[index + 1] = dynamic_array->dynamic_array[index];  //Move back element
		}
		dynamic_array->dynamic_array[insert_position] = insert_data;  //insert new data
		dynamic_array->array_size++;                                  //array length increment 
		return 1;                                                     //return success code
	}
	else
	{
		for(index = dynamic_array->array_size; index >= insert_position; index--)  //If there is enough space in the array
		{
			dynamic_array->dynamic_array[index + 1] = dynamic_array->dynamic_array[index]; //move back element
		}
		dynamic_array->dynamic_array[insert_position] = insert_data;                       //insert new data
		dynamic_array->array_size++;                                                       //array length increment
		return 1;   //return success code
		
	}
	
}

/*
*@function name:print_array_element
*@arguments:dynamic array pointer, back call function print_func
*@return type:void
*@return value:void
*/
status print_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, void (*print_func)(void* print_data))
{
	if(dynamic_array == NULL || print_func == NULL) //if pointer null
	{
		return -1;            //return error code
	}
	
	int index;                //defined array index
	
	for(index = 0 ; index < dynamic_array->array_size;index++)  //foreach array
	{
		(*print_func)(dynamic_array->dynamic_array[index]);     //print array element
	}
	return 1;
}

/*
*@function name:delete_array_element
*@arguments:dynamic array pointer, delete position and reseved data pointer
*@return type:status
*@return value:success return 1 failed return -1
*/
status delete_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, int _Fn_In_ delete_position, void** _Fn_Out_ reserved)
{
	if(dynamic_array == NULL || delete_position < 0)                 //poiner is null or position illegal
	{
		return -1;                                                   //return error code
	}
	
	if(delete_position >= dynamic_array->array_size)                 //position exceed array length
	{
		return -1;                                                   //return error code
	}
	
	int index;                                                       //defined array index
	
	if(reserved != NULL)                                             //If the pointer to retain data is not empty
	{
		*reserved = dynamic_array->dynamic_array[delete_position];   //Dereference the pointer and save the data
	}
	
	for(index = delete_position; index < dynamic_array->array_size; index++)          //Override starts from the incoming location
	{
		dynamic_array->dynamic_array[index] = dynamic_array->dynamic_array[index + 1];//Overwrite the data from back to front
	}
	dynamic_array->array_size--;          //array size degression
	return 0;                             //return 0 
} 

/*
*@function name:free_dynamic_array
*@arguments:dynamic array pointer
*@return type:status
*@return value:success return 1 failed return -1
*/
status free_dynamic_array(dynamicarray_ptr_t _Fn_In_ dynamic_array)
{
	if(dynamic_array == NULL)            //if pointer null
	{
		return -1;                       //return error code
	}
	
	free(dynamic_array->dynamic_array);  //free dynamic array array space
	free(dynamic_array);                 //free dynamic array struct type space
	
	return 1;                            //success free return success code
}
