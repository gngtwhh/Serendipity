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

	insert_list_node(list_head, 1 , &value1); //�����1��ʼ
	insert_list_node(list_head, _TAILINSERT, &value2);
	insert_list_node(list_head, _TAILINSERT, &value3);
	insert_list_node(list_head, _TAILINSERT, &value4);

	delete_list_node(list_head, 0, NULL);
	free_list_space(&list_head);
	print_link_list(list_head, back_call_print);

	free(list_head);
	return 0;
}

list_ptr_t __cdecl create_link_list(void) //����ͷ�ڵ�
{
	list_ptr_t list_head = (list_ptr_t)malloc(sizeof(list_node_t)); //Ϊͷ�ڵ����ռ�
	int* list_length = (int*)malloc(sizeof(int)); //ͷ�ڵ��������ָ��һ��int �洢����ĳ���

	if (!list_head || !list_length) //create link list fail
	{
		return NULL;
	}
	//init
	*list_length = 0; //init link list length 0
	list_head->list_data = list_length; //pointer list_length
	list_head->next = NULL; //��һ���ڵ�Ϊ��
	return list_head; //���ش����õ�ͷ�ڵ�
}

status insert_list_node(list_ptr_t list_head, int insert_position, void* insert_new_data) //����ڵ㵽����
{
	int list_index; //�����λ���±�
	list_ptr_t move_node = list_head; //ʹ����ʱ�ڵ��ƶ�

	if (list_head == NULL || insert_new_data == NULL || insert_position <= 0) //��������������
	{
		return STATUS_ERROR;
	}

	list_ptr_t new_node = (list_ptr_t)malloc(sizeof(list_node_t)); //�����ڴ洴��һ���½��

	if (new_node == NULL) //�½ڵ��ڴ����ʧ��
	{
		return STATUS_FAILED;
	}

	new_node->list_data = insert_new_data; //�½ڵ��������ָ���µ�����
	new_node->next = NULL; //�½ڵ��ָ����ָ���

	if (insert_position == _HEADINSERT || insert_position == _TAILINSERT) //�ж��Ƿ�ʹ���˺�
	{
		if (insert_position == _HEADINSERT)  //ͷ��
		{
			new_node->next = move_node->next;
			move_node->next = new_node;
			(*(int*)list_head->list_data)++;

			return STATUS_SUCCESS;
		}
		else                                 //β��
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
	else                                     //���û��������λ�ò���
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

int print_link_list(list_ptr_t list_head, void (*back_call_function)(void* print_data)) //��ӡ��������
{
	if (list_head == NULL) //�������ΪNULL
	{
		return STATUS_ERROR;
	}

	int list_index; //�����±�
	list_ptr_t move_node = list_head->next;

	for (list_index = 0; list_index < *(int*)list_head->list_data && move_node != NULL; list_index++)
	{
		(*back_call_function)(move_node->list_data); //ʹ���û��ṩ�Ļص�������ӡ����
		move_node = move_node->next; //����
	}
	return list_index; //��ӡ�ɹ����ش�ӡ���ĸ��� ʧ�ܷ���-1
}

status delete_list_node(list_ptr_t list_head, int delete_position, void** reserved_data) //��λ��ɾ���ڵ�
{
	int list_index; //�ڵ��±�
	int get_list_length = *(int*)list_head->list_data; //��ȡ������

	list_ptr_t prev_node = list_head; //ǰһ���ڵ�
	list_ptr_t current_node = list_head->next;  //��ǰ�ڵ�

	if (list_head == NULL || delete_position < 0 || delete_position >= get_list_length/* || reserved_data == NULL */)   //�����0ɾ��ͷ�ڵ����һ���ڵ�
	{
		return STATUS_ERROR;
	}

	for (list_index = 0; list_index < delete_position && list_index < *(int*)list_head->list_data; list_index++)  //foreach link list found delete
	{
		prev_node = current_node; //��������
		current_node = current_node->next;
	}

	if (reserved_data != NULL) //�����������ָ�벻Ϊ����Ҫɾ�������ݷ��ػ�ȥ
	{
		*reserved_data = current_node->list_data;
	}
	
	prev_node->next = current_node->next; //ǰһ�����ָ��ǰ�ڵ����һ���ڵ�
	current_node->list_data = NULL; //��ǰ�ڵ��������ÿ�
	free(current_node); //�ͷſռ�
	(*(int*)list_head->list_data)--; //������-1

	return STATUS_SUCCESS;
}


status free_list_space(list_ptr_t* list_head)
{
	if (list_head == NULL) //�жϲ����Ϸ���
	{
		return STATUS_ERROR;
	}

	int index;
	int* list_size_ptr = (*list_head)->list_data;

	for (index = 0; index < --(*list_size_ptr); index++)  //�������ڵ�
	{
		delete_list_node(*list_head, 0, NULL);
	}

	(*list_head)->next = NULL;
	free(list_size_ptr); //�ͷ���������Ĵ洢�����ȿռ�

	return STATUS_SUCCESS;
}

/*status change_node_data(list_ptr_t list_head, int change_position, void* new_data, _Bool(*change_data_func)(void* source, void* new_data), void** reserved_source_data)
{

	if (list_head == NULL || change_position < 0 || change_data_func == NULL) //�жϴ�������Ƿ�����
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
	_Bool change_ret_status = (*change_data_func)(move_node->list_data, new_data); //���߼�����

	return ((status)change_ret_status);
}

list_ptr_t find_node_data(list_ptr_t list_head, _Bool (*compare_data_func)(void* value1, void* value2), void* compare_value)
{
	if (list_head == NULL || compare_data_func == NULL || compare_value == NULL) //�������Ϸ�
	{
		return NULL;
	}

	int list_index;
	list_ptr_t move_node = list_head;

	for (list_index = 0; list_index < *(int*)list_head->list_data && move_node != NULL; list_index++) //��������
	{
		_Bool compare_ret_val = compare_data_func(compare_value, move_node->list_data);
		if (compare_ret_val) //�ԱȽڵ����������ͬ
		{
			return move_node; //���ص�ǰ�ڵ�
		}
		move_node = move_node->next;
	}
	//not found
	return NULL; //�����������δ�ҵ� ���ؿ�
}
*/