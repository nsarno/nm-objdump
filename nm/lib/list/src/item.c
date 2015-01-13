/*
** item.c for module list in /home/mesure_a/workspace/c/modules/list
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sat Mar 12 16:58:27 2011 arnaud mesureur
** Last update Sat Mar 12 17:41:27 2011 arnaud mesureur
*/

#include <stdlib.h>
#include <string.h>

#include "item.h"

struct item	*alloc_item(void)
{
  struct item	*item;

  item = malloc(sizeof(*item));
  return (item);
}

struct item	*init_item_by_default(struct item *item)
{
  if (NULL == item)
    return (NULL);
  item->content = NULL;
  item->len = -1;
  item->prev = NULL;
  item->next = NULL;
  return (item);
}

struct item	*init_item_by_param(struct item * item,
				    void *content, int len)
{
  if (NULL == item)
    return (NULL);
  item = init_item_by_default(item);
  if (NULL == content || len < 0)
    return (item);
  item->content = malloc(len);
  if (item->content != NULL)
    {
      item->content = memcpy(item->content, content, len);
      item->len = len;
    }
  return (item);
}

struct item	*new_item_by_default(void)
{
  struct item	*item;

  item = alloc_item();
  if (NULL != item)
    item = init_item_by_default(item);
  return (item);
}

struct item	*new_item_by_param(void *content, int len)
{
  struct item	*item;

  item = alloc_item();
  if (NULL != item)
    item = init_item_by_param(item, content, len);
  return item;
}

void	delete_item(struct item *item)
{
  if (NULL == item)
    return;
  if (NULL != item->content)
    free(item->content);
  free(item);
}
