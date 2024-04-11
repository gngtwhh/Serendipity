/**
 * @file dynamic_array.h 
 * @brief dynamic array implementation
 * @author inrootshell
 * @category data-structure
 * @date 2024-4-11
 */

#ifndef QUEUE_H_ //If no queue header file is defined

#define QUEUE_H_ //definition queue header file flag 

//#include "adt_pre_init.h"
#include <stdio.h> //include standard c header file
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef SEQQUEUE_T //If the linear queue type is not defined

#define SEQQUEUE_T 1 //defined flag

typedef int status;

typedef struct _seqqueue_t //define linaer queue structure
{
	void** queue_array; //An array that stores queue data
	int queue_max_size; //The maximum size of the queue
	int queue_header;   //The head of the line
	int queue_tail;     //Tail pointer
}seqqueue_t, *seqqueue_ptr_t; //structure type alias

#endif //end define

/*
*@function name:initialize_queue
*@arguments:initialize queue size
*@return type:seqqueue_ptr_t
*@return value:success return a pointer failed return NULL
*/

extern seqqueue_ptr_t initialize_queue(unsigned int initialize_queue_size);

/*
*@function name:enter_queue
*@arguments:Queue pointers and data pointers
*@return type:status
*@return value:success return 1 argments error return -1 function error return 0
*/

extern status enter_queue(seqqueue_ptr_t queue, void* new_data);

/*
*@function name:out_queue
*@arguments:Queue pointers and reserved pointers
*@return type:status
*@return value:success return 1 argments error return -1 function error return 0
*/
extern status out_queue(seqqueue_ptr_t queue, void** reserved_data);

/*
*@function name:print_queue
*@arguments:Queue pointer and callback function pointer
*@return type:status
*@return value:success print return 1 fail return 0
*/
extern status print_queue(seqqueue_ptr_t queue, void (*print_back)(void* print_data));

/*
*@function name:print_back
*@arguments:print data
*@return type:void
*@return value:void
*/

extern void print_back(void* print_data);

/*
*@function name:get_queue_header
*@arguments:queue pointer
*@return type:void*
*@return value:queue pointer is null return null else return queue head element
*/

extern void* get_queue_header(seqqueue_ptr_t queue);

/*
*@function name:get_queue_tail
*@arguments:queue pointer
*@return type:void*
*@return value:queue pointer is null return null else return queue tail element
*/

extern void* get_queue_tail(seqqueue_ptr_t queue);

/*
*@function name:
*@arguments:queue pointer
*@return type:int
*@return value:queue pointer is null return 0 else return queue current size
*/

extern int get_queue_current_size(seqqueue_ptr_t queue); 

#endif
