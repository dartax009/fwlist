#include "fwlist.h"

void push (s_mas **head, const void *val, const size_t el)
{
	s_mas *tmp = (s_mas *) malloc(sizeof(s_mas));
	tmp->value = malloc(el);

	memcpy(tmp->value, val, el);

	tmp->next	= (*head);
	(*head)		= tmp;

	return;
}

uint8_t pop (s_mas **head, void *val, const size_t el)
{
	if((*head) == NULL)
		return 1;

	s_mas *tmp = NULL;

	tmp = (*head);

	if (val != 0)
		memcpy(val, tmp->value, el);

	(*head) = (*head)->next;

	free(tmp->value);
	free(tmp);

	return 0;
}

s_mas *findN (s_mas *head, const uint64_t n)
{
	if (head == NULL)
		return NULL;

	for (uint64_t i=0; i<n; i++)
	{
		head = head->next;
		if (head == NULL)
			return NULL;
	}
	return head;
}

uint8_t setN (s_mas *head, const uint64_t n, const void *val, const size_t el)
{
	head = findN(head, n);
	if (head == NULL)
		return 1;
	else
		memcpy(head->value, val, el);

	return 0;
}

s_mas *findLast (s_mas *head)
{
	if (head==NULL)
		return NULL;

	while (head->next != NULL)
		head = head->next;

	return head;
}

void pushBack (s_mas **head, const void *val, const size_t el)
{
	s_mas *last = findLast((*head));

	s_mas *tmp = (s_mas *) malloc(sizeof(s_mas));
	tmp->value = malloc(el);

	memcpy(tmp->value, val, el);
	tmp->next = NULL;

	if (last == NULL)
		(*head) = tmp;
	else
		last->next = tmp;

	return;
}

uint8_t popBack (s_mas **head, void *val, const size_t el)
{
	if((*head) == NULL)
		return 1;

	if ((*head)->next == NULL)
	{
		memcpy(val, (*head)->value, el);
		free((*head)->value);
		free(*head);
		*head = NULL;
		return 0;
	}

	s_mas *tmp = NULL;

	tmp = (*head);

	while (tmp->next->next != NULL)
		tmp = tmp->next;

	if (val != 0)
		memcpy(val, tmp->next->value, el);

	free(tmp->next->value);
	free(tmp->next);
	tmp->next = NULL;
	return 0;
}

uint8_t pushN (s_mas *head, const uint64_t n, const void *val, const size_t el)
{
	head = findN(head, n);

	if (head == NULL)
		return 1;

	s_mas *tmp = (s_mas *) malloc(sizeof(s_mas));
	tmp->value = malloc(el);
	memcpy(tmp->value, val, el);

	tmp->next = head->next;

	head->next = tmp;

	return 0;
}

uint8_t popN (s_mas **head, const uint64_t n, void *val, const size_t el)
{
	if (n == 0)
		return pop(head, val, el);

	s_mas *ahead = findN( (*head), n-1);
	if (ahead == NULL || ahead->next == NULL)
		return 1;

	s_mas *tmp = ahead->next;

	if (val != 0)
		memcpy(val, tmp->value, el);

	ahead->next = tmp->next;
	free(tmp->value);
	free(tmp);

	return 0;
}