/*
 *This project is mainly used to write data structures
 *This file mainly contains singly linked lists, circular linked lists, and double-linked lists
 *We've defined some new types that are commonly used
 *The project is written on the platform it runs on windows 11
 *C language version used c99
 *This document was written at the same time 2024/3/15/00:12
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <assert.h>

typedef int status;                   //Defined new type status
#ifndef STATUS_DEF                    //If not defined status macro
#  define STATUS_DEF                  //Define status macro
#  define STATUS_SUCCESS (0x00000001) //Success return the status value 1
#  define STATUS_FAILED  (0x00000000) //Fail return the status value 0
#  define STATUS_ERROR   (0xffffffff) //Error return the status value -1
#endif                                //End definition

#ifndef _INSERTPOS
#  define _INSERTPOS
#  define _HEADINSERT (0x01000000)    //insert function head insert
#  define _TAILINSERT (0x10000000)    //insert function tail insert
#endif

#ifndef LISTNODE_T                    //If There is no definition list node type 
#  define LISTNODE_T                  //define list node type

typedef struct list_node_t            //link list source data structures
{
	void* list_data;                  //reserve data
	struct list_node_t* next;         //reserve next node pointer
}list_node_t, * list_ptr_t, * ptr_list_t;            //defined tow types 

#endif                                //end definition

/*
 *function name:create_link_list
 *Function parameters:
 *function functions:
 *return type and Return to Description:
*/

list_ptr_t __cdecl create_link_list(void);

/*
 *function name:insert_list_node
 *Function parameters:
 *function functions:
 *return type and Return to Description:
*/

status insert_list_node(list_ptr_t list_head, int insert_position, void* insert_new_data);

/*
 *function name:
 *Function parameters:
 *function functions:
 *return type and Return to Description:
*/

int print_link_list(list_ptr_t list_head, void (*back_call_function)(void* print_data));

void back_call_print(void* print_data)
{
	printf("%d \n", *(int*)print_data);
}

_Bool back_call_change(void* data1, void* data2)
{
	*((int*)data1) = *((int*)data2);
	return 1;
}

/*
 *function name:
 *Function parameters:
 *function functions:
 *return type and Return to Description:
*/

status delete_list_node(list_ptr_t list_head, int delete_position, void** reserved_data);

/*
 *function name:
 *Function parameters:
 *function functions:
 *return type and Return to Description:
*/

//status change_node_data(list_ptr_t list_head, int change_position, void* new_data, _Bool(*change_data_func)(void* source, void* new_data), void** reserved_source_data);

/*
 *function name:
 *Function parameters:
 *function functions:
 *return type and Return to Description:
*/

//list_ptr_t find_node_data(list_ptr_t list_head, _Bool (*compare_data_func)(void* value1, void* value2), void* compare_value);

/*
 *function name:
 *Function parameters:
 *function functions:
 *return type and Return to Description:
*/

status free_list_space(list_ptr_t* list_head);

int main()
{
	int new_data = 2222;
	int value1 = 10;
	int value2 = 20;
	int value3 = 30;
	int value4 = 40;
	int values = 1000;
	//void* reserve;

	list_ptr_t list_head = create_link_list();
	if (!list_head)
	{
		puts("create link list failed");
		return 1;
	}
	printf("link list size is %d\n", *(int*)list_head->list_data);
	printf("link list next node is %p\n", list_head->next);

	insert_list_node(list_head, 1 , &value1); //插入从1开始
	insert_list_node(list_head, _TAILINSERT, &value2);
	insert_list_node(list_head, _TAILINSERT, &value3);
	insert_list_node(list_head, _TAILINSERT, &value4);

	delete_list_node(list_head, 0, NULL);
	free_list_space(&list_head);
	print_link_list(list_head, back_call_print);

	free(list_head);
	return 0;
}

list_ptr_t __cdecl create_link_list(void) //创建头节点
{
	list_ptr_t list_head = (list_ptr_t)malloc(sizeof(list_node_t)); //为头节点分配空间
	int* list_length = (int*)malloc(sizeof(int)); //头节点的数据域指向一个int 存储链表的长度

	if (!list_head || !list_length) //create link list fail
	{
		return NULL;
	}
	//init
	*list_length = 0; //init link list length 0
	list_head->list_data = list_length; //pointer list_length
	list_head->next = NULL; //下一个节点为空
	return list_head; //返回创建好的头节点
}

status insert_list_node(list_ptr_t list_head, int insert_position, void* insert_new_data) //插入节点到链表
{
	int list_index; //链表的位置下表
	list_ptr_t move_node = list_head; //使用临时节点移动

	if (list_head == NULL || insert_new_data == NULL || insert_position <= 0) //如果传入参数有误
	{
		return STATUS_ERROR;
	}

	list_ptr_t new_node = (list_ptr_t)malloc(sizeof(list_node_t)); //申请内存创建一个新结点

	if (new_node == NULL) //新节点内存分配失败
	{
		return STATUS_FAILED;
	}

	new_node->list_data = insert_new_data; //新节点的数据域指向新的数据
	new_node->next = NULL; //新节点的指针域指向空

	if (insert_position == _HEADINSERT || insert_position == _TAILINSERT) //判断是否使用了宏
	{
		if (insert_position == _HEADINSERT)  //头插
		{
			new_node->next = move_node->next;
			move_node->next = new_node;
			(*(int*)list_head->list_data)++;

			return STATUS_SUCCESS;
		}
		else                                 //尾插
		{
			int tail_index;
			for (tail_index = 0; tail_index < *(int*)list_head->list_data && move_node->next != NULL; tail_index ++)
			{
				move_node = move_node->next;
			}
			new_node->next = NULL;
			move_node->next = new_node;
			(*(int*)list_head->list_data)++;

			return STATUS_SUCCESS;
		}
	}
	else                                     //按用户给的随机位置插入
	{
		for (list_index = 0; list_index < *(int*)list_head->list_data && list_index < insert_position && move_node != NULL; list_index ++)
		{
			move_node = move_node->next;
		}
		new_node->next = move_node->next;
		move_node->next = new_node;
		(*(int*)list_head->list_data)++;

		return STATUS_SUCCESS;
	}

}

int print_link_list(list_ptr_t list_head, void (*back_call_function)(void* print_data)) //打印链表数据
{
	if (list_head == NULL) //如果链表为NULL
	{
		return STATUS_ERROR;
	}

	int list_index; //链表下表
	list_ptr_t move_node = list_head->next;

	for (list_index = 0; list_index < *(int*)list_head->list_data && move_node != NULL; list_index++)
	{
		(*back_call_function)(move_node->list_data); //使用用户提供的回调函数打印数据
		move_node = move_node->next; //遍历
	}
	return list_index; //打印成功返回打印结点的个数 失败返回-1
}

status delete_list_node(list_ptr_t list_head, int delete_position, void** reserved_data) //按位置删除节点
{
	int list_index; //节点下表
	int get_list_length = *(int*)list_head->list_data; //获取链表长度

	list_ptr_t prev_node = list_head; //前一个节点
	list_ptr_t current_node = list_head->next;  //当前节点

	if (list_head == NULL || delete_position < 0 || delete_position >= get_list_length/* || reserved_data == NULL */)   //如果是0删除头节点的下一个节点
	{
		return STATUS_ERROR;
	}

	for (list_index = 0; list_index < delete_position && list_index < *(int*)list_head->list_data; list_index++)  //foreach link list found delete
	{
		prev_node = current_node; //遍历链表
		current_node = current_node->next;
	}

	if (reserved_data != NULL) //如果保留数据指针不为空则将要删除的数据返回回去
	{
		*reserved_data = current_node->list_data;
	}
	
	prev_node->next = current_node->next; //前一个结点指向当前节点的下一个节点
	current_node->list_data = NULL; //当前节点数据域置空
	free(current_node); //释放空间
	(*(int*)list_head->list_data)--; //链表长度-1

	return STATUS_SUCCESS;
}


status free_list_space(list_ptr_t* list_head)
{
	if (list_head == NULL) //判断参数合法性
	{
		return STATUS_ERROR;
	}

	int index;
	int* list_size_ptr = (*list_head)->list_data;

	for (index = 0; index < --(*list_size_ptr); index++)  //清空链表节点
	{
		delete_list_node(*list_head, 0, NULL);
	}

	(*list_head)->next = NULL;
	free(list_size_ptr); //释放最初创建的存储链表长度空间

	return STATUS_SUCCESS;
}

/*status change_node_data(list_ptr_t list_head, int change_position, void* new_data, _Bool(*change_data_func)(void* source, void* new_data), void** reserved_source_data)
{

	if (list_head == NULL || change_position < 0 || change_data_func == NULL) //判断传入参数是否无误
	{
		return STATUS_ERROR;
	}

	int list_index;
	list_ptr_t move_node = list_head;

	for (list_index = 0; list_index < change_position && list_index < *(int*)list_head->list_data; list_index++)
	{
		printf("%d\n", list_index);
		move_node = move_node->next;
	}
	_Bool change_ret_status = (*change_data_func)(move_node->list_data, new_data); //有逻辑问题

	return ((status)change_ret_status);
}

list_ptr_t find_node_data(list_ptr_t list_head, _Bool (*compare_data_func)(void* value1, void* value2), void* compare_value)
{
	if (list_head == NULL || compare_data_func == NULL || compare_value == NULL) //检查参数合法
	{
		return NULL;
	}

	int list_index;
	list_ptr_t move_node = list_head;

	for (list_index = 0; list_index < *(int*)list_head->list_data && move_node != NULL; list_index++) //遍历链表
	{
		_Bool compare_ret_val = compare_data_func(compare_value, move_node->list_data);
		if (compare_ret_val) //对比节点数据如果相同
		{
			return move_node; //返回当前节点
		}
		move_node = move_node->next;
	}
	//not found
	return NULL; //如果遍历结束未找到 返回空
}
*/