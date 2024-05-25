/* td.c */

#include <stdio.h>
#include <stdlib.h>

#include "td.h"

static void td_list_decrement(td_list_T *, size_t);

td_T *new_td(char *name, size_t index, bool status)
{
	td_T *td = malloc(sizeof(td_T));

	td->name = name;
	td->index = index;
	td->status = status;

	return td;
}

void td_list_insert(td_list_T **head, td_T *td)
{
	if(!(*head)) {
		(*head) = malloc(sizeof(td_list_T));
		(*head)->td = td;
		(*head)->next = NULL;
		(*head)->prev = NULL;
		return;
	}

	td_list_T *new_node = malloc(sizeof(td_list_T));

	td_list_T *i;
	
	for(i = *head; i->next != NULL; i = i->next);

	new_node->td = td;
	new_node->next = NULL;
	new_node->prev = i;
		
	i->next = new_node;
}

td_list_T *td_list_index(td_list_T *head, size_t index)
{
	for(td_list_T *i = head; i != NULL; i = i->next)
		if(i->td->index == index)
			return i;
	return NULL;
}

static void td_list_decrement(td_list_T *head, size_t index)
{
	for(td_list_T *i = td_list_index(head, index); i != NULL; i = i->next)
		i->td->index--;
}

void td_list_delete(td_list_T **head, size_t index)
{
	td_list_T *node_to_delete;

	if(index == 1) {
		if((*head)->next)
			td_list_decrement(*head, 2);
		node_to_delete = *head;

		(*head) = (*head)->next;
		(*head)->prev = NULL;
		free(node_to_delete);
		return;
	}

	node_to_delete = td_list_index(*head, index);

	if(!node_to_delete->next)
		node_to_delete->prev->next = NULL;
	else {
		node_to_delete->prev->next = node_to_delete->next; 
		td_list_decrement(*head, index+1);
	}

	free(node_to_delete);	
}
