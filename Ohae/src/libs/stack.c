#include"stack.h"

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

double pop_n(links_for_stacks *link)
{
	double lastNum = 0.0;
	if (link->head_n == NULL)
	{
		return lastNum;
	}
	if (link->head_n->next == NULL)
	{
		lastNum = link->head_n->num;
		free(link->head_n);
		link->head_n = NULL;
		return lastNum;
	}
	numbers *current = link->head_n;
	while (current->next->next != NULL)
	{
		current = current->next;
	}
	lastNum = current->next->num;
	free(current->next);
	current->next = NULL;
	return lastNum;
}

char pop_o(links_for_stacks *link)
{
	char lastOperation = ' ';
	if (link->head_o == NULL)
	{
		return lastOperation;
	}
	if (link->head_o->next == NULL)
	{
		lastOperation = link->head_o->operation;
		free(link->head_o);
		link->head_o = NULL;
		return lastOperation;
	}
	operations *current = link->head_o;
	while (current->next->next != NULL)
	{
		current = current->next;
	}
	lastOperation = current->next->operation;
	free(current->next);
	current->next = NULL;
	return lastOperation;
}

void delete_n(links_for_stacks *link)
{
	while (link->head_n != NULL)
	{
		pop_n(link);
	}
}

void delete_o(links_for_stacks *link)
{
	while (link->head_o != NULL)
	{
		pop_o(link);
	}
}

void push_back_n(double data, links_for_stacks *link)
{
	if (link->head_n == NULL)
	{
		link->head_n = malloc(sizeof(numbers));
		link->head_n->next = NULL;
		link->head_n->num = data;
		return;
	}
	numbers *current = link->head_n;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = malloc(sizeof(numbers));
	current->next->num = data;
	current->next->next = NULL;
}

void push_back_o(char data, links_for_stacks *link)
{
	if (link->head_o == NULL)
	{
		link->head_o = malloc(sizeof(operations));
		link->head_o->operation = data;
		link->head_o->next = NULL;
		return;
	}
	operations *current = link->head_o;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = malloc(sizeof(operations));
	current->next->operation = data;
	current->next->next = NULL;
}
