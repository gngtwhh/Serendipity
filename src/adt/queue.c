/**
* @file queue.c
* @brief queue
* @author inrootshell
* @category data-structure
* @date 2024-4-11
*/

//#include "queue.h"
//#include <stdio.h> //include standard c header file
//#include <stdlib.h>
//#include <string.h>
//#include <assert.h>
//
//#ifndef SEQQUEUE_T //If There is no definition SEQQUEUE_T type
//
//#define SEQQUEUE_T 1 //definition SEQQUEUE_T type
//
//typedef int status; //define status type
//
//typedef struct _seqqueue_t //defien linear queue type structrue
//{
//	void** queue_array; //queue array
//	int queue_max_size; //queue max size
//	int queue_header;   //queue header
//	int queue_tail;     //queue tail
//}seqqueue_t, *seqqueue_ptr_t; //type alias
//
//#endif //end definition
//
//seqqueue_ptr_t initialize_queue(unsigned int initialize_queue_size);
//
//status enter_queue(seqqueue_ptr_t queue, void* new_data);
//
//status out_queue(seqqueue_ptr_t queue, void** reserved_data);
//
//status print_queue(seqqueue_ptr_t queue, void (*print_back)(void* print_data));
//
//void print_back(void* print_data);
//
//void* get_queue_header(seqqueue_ptr_t queue);
//
//void* get_queue_tail(seqqueue_ptr_t queue);
//
//int get_queue_current_size(seqqueue_ptr_t queue); 

/*
*@function name:initialize_queue
*@arguments:initialize queue size
*@return type:seqqueue_ptr_t
*@return value:success return a pointer failed return NULL
*/

seqqueue_ptr_t initialize_queue(unsigned int initialize_queue_size)
{
	if(!initialize_queue_size) //If the initialization size is 0
	{
		return NULL;           //return a null pointer
	}
	
	seqqueue_ptr_t queue = (seqqueue_ptr_t)malloc(sizeof(seqqueue_t)); //Allocate a piece of memory
	
	if(!queue)       //Memory allocation failed
		return NULL; //return null
		
	queue->queue_array = (void**)malloc(sizeof(void*) * initialize_queue_size); //Allocate a piece of memory
	
	if(!queue->queue_array) //Memory allocation failed
		return NULL;        //return null
		
	memset(queue->queue_array, 0, sizeof(void*) * initialize_queue_size); //The value of the initialized array memory is 0
	
	queue->queue_header = 0; //queue header index initialize is 0
	queue->queue_tail = queue->queue_header; //queue tail index initialize is 0
	queue->queue_max_size = initialize_queue_size; //The queue size is assigned to the initialization size
	
	return queue; //return queue pointer
}

/*
*@function name:enter_queue
*@arguments:Queue pointers and data pointers
*@return type:status
*@return value:success return 1 argments error return -1 function error return 0
*/

status enter_queue(seqqueue_ptr_t queue, void* new_data)
{
	if(queue == NULL || new_data == NULL) //If the queue pointer is empty or the data pointer is empty
		return -1; //return error code
	
	if(queue->queue_tail == queue->queue_max_size) //If the tail of the queue is equal to the queue size
		return 0;  //queue full return error code
		
	queue->queue_array[queue->queue_tail] = new_data; //element enter queue
	queue->queue_tail++; //queue tail auto increment
	
	return 1; //return success code
}

/*
*@function name:out_queue
*@arguments:Queue pointers and reserved pointers
*@return type:status
*@return value:success return 1 argments error return -1 function error return 0
*/


status out_queue(seqqueue_ptr_t queue, void** reserved_data)
{
	if(queue == NULL) //If the queue pointer is empty
		return -1; //return error code
		
	if(queue->queue_tail == -1) //If the queue is null
		return 0;  //return error queue
		
	if(reserved_data) //If the pointer is valid
		*reserved_data = queue->queue_array[queue->queue_header]; //Save the elements to be dequeued to this variable
		
	int queue_index; //queue index
	
	for(queue_index = 0;queue_index < queue->queue_tail; queue_index++) //Traverse the queue
	{
		queue->queue_array[queue_index] = queue->queue_array[queue_index + 1]; //Move the element
	}
	
	queue->queue_tail--; //queue tail auto degression
	
	return 1; //return success code
}

/*
*@function name:print_queue
*@arguments:Queue pointer and callback function pointer
*@return type:status
*@return value:success print return 1 fail return 0
*/


status print_queue(seqqueue_ptr_t queue, void (*print_back)(void* print_data))
{
	if(queue == NULL || print_back == NULL) //The queue pointer is empty or the callback function pointer is empty
		return -1;  //reurn error code
		
	int queue_index; //foreach queue index
	
	for(queue_index = queue->queue_header; queue_index < queue->queue_tail; queue_index++) //foreach queue
	{	
		print_back(queue->queue_array[queue_index]); //print queue elements
	}
	
	return 1; //return success code
}

/*
*@function name:print_back
*@arguments:print data
*@return type:void
*@return value:void
*/

void print_back(void* print_data) //callback function
{
	printf("%d ", *(int*)print_data); 
}

/*
*@function name:get_queue_header
*@arguments:queue pointer
*@return type:void*
*@return value:queue pointer is null return null else return queue head element
*/

void* get_queue_header(seqqueue_ptr_t queue)
{
	if(!queue) //if the queue is null pointer
		return NULL; //return null pointer
	
	return queue->queue_array[queue->queue_header]; //return queue header element
}

/*
*@function name:get_queue_tail
*@arguments:queue pointer
*@return type:void*
*@return value:queue pointer is null return null else return queue tail element
*/


void* get_queue_tail(seqqueue_ptr_t queue)
{
	if(!queue) //if the queue is null pointer
		return NULL; //return pointer null
		
	return queue->queue_array[queue->queue_tail - 1]; //return queue tail element
}

/*
*@function name:
*@arguments:queue pointer
*@return type:int
*@return value:queue pointer is null return 0 else return queue current size
*/


int get_queue_current_size(seqqueue_ptr_t queue)
{
	if(!queue) //if the queue is null pointer
		return -1; //return error code
		
	return queue->queue_tail; //return queue current size
}
