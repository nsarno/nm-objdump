/* -*- C -*-
** list.h for list in /home/mesure_a/workspace/c/modules/list
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sat Mar 12 13:51:17 2011 arnaud mesureur
** Last update Sun Mar 13 19:41:01 2011 arnaud mesureur
*/

#ifndef		LIST_H_
# define	LIST_H_

/*
** The List
** --------
*/

struct			list
{
  int			len;
  int			empty;
  struct item *		head;
  struct item *		tail;
};

/*
** Prototypes
** ----------
*/

/* ** Internal module functions ** */

struct list	*alloc_list(void);
struct list	*init_list_by_default(struct list * the_list);
struct list	*new_list_by_default(void);

/* ** External module functions ** */

void	delete_list(struct list *list);

void	list_add_front(struct list *list, void *data, int len);
void	list_add_back(struct list *list, void *data, int len);

void	list_iter(struct list *list, void (*f)(void *, int));
void	list_sort(struct list *list, int (*f)(void*, void*));

#endif		/* LIST_H_ */
