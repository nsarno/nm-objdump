/*
** list.c for module list in /home/mesure_a/workspace/c/modules/list
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sat Mar 12 14:01:39 2011 arnaud mesureur
** Last update Sat Mar 12 19:57:53 2011 arnaud mesureur
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "item.h"
#include "list.h"

struct list	*alloc_list(void)
{
  struct list	*list;

  list = malloc(sizeof(*list));
  return (list);
}

struct list	*init_list_by_default(struct list *list)
{
  if (NULL == list)
    return (NULL);
  list->len = 0;
  list->empty = 1;
  list->head = NULL;
  list->tail = NULL;
  return (list);
}

struct list	*new_list_by_default(void)
{
  struct list	*list;

  list = alloc_list();
  if (NULL != list)
    list = init_list_by_default(list);
  return (list);
}

static void	delete_list_items(struct item *item)
{
  if (NULL == item)
    return;
  if (NULL != item->next)
    delete_list_items(item->next);
  delete_item(item);
}

void	delete_list(struct list *list)
{
  if (NULL == list)
    return;
  if (!list->empty)
    delete_list_items(list->head);
  free(list);
  list = NULL;
}

static void	list_add_front_real(struct list *list,
				    struct item *item)
{
  if (NULL == list || NULL == item)
    return;
  item->prev = NULL;
  item->next = list->head;
  if (NULL != list->head)
    list->head->prev = item;
  if (NULL == list->tail)
    list->tail = item;
  list->head = item;
  list->len += 1;
  list->empty = 0;
}

static void	list_add_back_real(struct list *list,
				   struct item *item)
{
  if (NULL == list || NULL == item)
    return;
  item->prev = list->tail;
  item->next = NULL;
  if (NULL != list->tail)
    list->tail->next = item;
  if (NULL == list->head)
    list->head = item;
  list->tail = item;
  list->len += 1;
  list->empty = 0;
}

void	list_add_front(struct list *list, void *data, int len)
{
  list_add_front_real(list, new_item_by_param(data, len));
}

void	list_add_back(struct list *list, void *data, int len)
{
  list_add_back_real(list, new_item_by_param(data, len));
}

void		list_iter(struct list *list, void (*f)(void*, int))
{
  struct item	*current;

  if (NULL == list || f == NULL)
    return;
  current = list->head;
  while (NULL != current)
    {
      f(current->content, current->len);
      current = current->next;
    }
}

static void	item_swap(struct item *ptr1, struct item *ptr2)
{
  struct item	tmp;

  tmp = *ptr1;
  ptr1->content = ptr2->content;
  ptr1->len = ptr2->len;
  ptr2->content = tmp.content;
  ptr2->len = tmp.len;
}

void		list_sort(struct list *list, int (*f)(void*, void*))
{
  struct item	*current;
  int		sorted;

  if (NULL == list || NULL == f)
    return;
  current = list->head;
  do
    {
      sorted = 1;
      while (NULL != current && NULL != current->next)
	{
	  if (f(current->content, current->next->content))
	    {
	      sorted = 0;
	      item_swap(current, current->next);
	    }
	  current = current->next;
	}
      current = list->head;
    }
  while (!sorted);
}
