/**
 * @file dynamic_array.h 
 * @brief dynamic array implementation
 * @author inrootshell
 * @category data-structure
 * @date 2024-3-25
 */

#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

//#include "adt_pre_init.h"
#include <stdlib.h>
#include <stdio.h>
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


/*
*@function name:initialize_dynamic_array
*@arguments:initialize dynamic array size
*@return type:dynamicarray_ptr_t
*@return value:success return a pointer failed return NULL
*/
extern dynamicarray_ptr_t initialize_dynamic_array(int _Fn_In_ initial_capacity_size);

/*
*@function name:insert_array_element
*@arguments:dynamic array pointer, insert position and insert data
*@return type:status
*@return value:success return 1 failed return -1
*/
extern status insert_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, int _Fn_In_ insert_position, void* _Fn_In_ insert_data);

/*
*@function name:delete_array_element
*@arguments:dynamic array pointer, delete position and reseved data pointer
*@return type:status
*@return value:success return 1 failed return -1
*/
extern status delete_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, int _Fn_In_ delete_position, void** _Fn_Out_ reserved);

/*
*@function name:print_array_element
*@arguments:dynamic array pointer, back call function print_func
*@return type:void
*@return value:void
*/
extern status print_array_element(dynamicarray_ptr_t _Fn_In_ dynamic_array, void (*print_func)(void* print_data));

/*
*@function name:free_dynamic_array
*@arguments:dynamic array pointer
*@return type:status
*@return value:success return 1 failed return -1
*/
extern status free_dynamic_array(dynamicarray_ptr_t _Fn_In_ dynamic_array);

#endif
