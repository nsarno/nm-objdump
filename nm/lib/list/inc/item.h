/* -*- C -*-
** item.h for module list in /home/mesure_a/workspace/c/modules/list
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sat Mar 12 13:59:28 2011 arnaud mesureur
** Last update Sat Mar 12 17:34:37 2011 arnaud mesureur
*/

#ifndef		ITEM_H_
# define	ITEM_H_

/*
** The item
** --------
*/

struct			item
{
  void *		content;
  int			len;
  struct item *		prev;
  struct item *		next;
};


/*
** Prototypes
** ----------
*/

struct item *	alloc_item(void);
struct item *	init_item_by_default(struct item *the_item);
struct item *	init_item_by_param(struct item * the_item, void * content, int len);
struct item *	new_item_by_default(void);
struct item *	new_item_by_param(void * src_content, int src_len);

void		delete_item(struct item * the_item);

#endif		/* ITEM_H_ */
