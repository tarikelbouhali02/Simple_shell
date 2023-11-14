#include "shell.h"

/**
 * taprint_list - Print the lists
 * @h: list with format list_t
 * Return: number of nodes of the list
 */
size_t taprint_list(const list_t *h)
{
	unsigned int tnumber_nodes = 0;

	while (h != NULL)
	{
		if (h->str)
		{
			ta_puts(tanum_to_str(h->len));
			ta_puts(" ");
			ta_puts(h->str);
			ta_puts("\n");
		}
		else
			ta_puts("[0] (nil)\n");
		h = h->next;
		tnumber_nodes++;
	}
	return (tnumber_nodes);
}

/**
 * taadd_node_end - add a new node at the end of the linked list
 * @head: pointer to the first node
 * @str: content of the string for the first node
 * Return: pointer to the first node
 */
list_t *taadd_node_end(list_t **head, const char *str)
{
	list_t *end_node, *tmp;

	end_node = malloc(sizeof(list_t));

	if (end_node == NULL)
		return (NULL);

	end_node->str = ta_strdup(str);
	end_node->len = ta_strlen(str);
	end_node->next = NULL;

	if (*head == NULL)
	{
		*head = end_node;
		return (*head);
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = end_node;
	return (end_node);

}

/**
 * tafree_list - functions that  to free a linkedlist
 * @head: head in first node
 * Return: void -> free this linked list
 */
void tafree_list(list_t *head)
{
	if (head == NULL)
		return;
	tafree_list(head->next);
	free(head->str);
	free(head);
}
