/*
** nm.c for nm in /home/mesure_a/workspace/c/nm-objdump
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Thu Mar 10 21:44:55 2011 arnaud mesureur
** Last update Sun Mar 13 21:29:25 2011 arnaud mesureur
*/

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <string.h>
#include <sys/mman.h>

#include "list.h"
#include "nm.h"

static void	print_symbol(void *content, int len)
{
  t_sym		*sym;

  (void)len;
  sym = (t_sym*)content;
  if (sym->value)
    printf("%08x %c %s\n", (unsigned)sym->value, sym->type, sym->name);
  else
    printf("%10c %s\n", sym->type, sym->name);
}

static int	symcmp(void *c1, void *c2)
{
  t_sym		*s1;
  t_sym		*s2;

  s1 = (t_sym*)c1;
  s2 = (t_sym*)c2;
  return (strcmp(s1->name, s2->name) > 0);
}

int		nm(const char * filename)
{
  void		*data;
  t_elf		elf;
  t_sym_list	*list;
  int		msize;

  if ((msize = map_file(&data, filename)) == -1)
    return (1);
  if (init_elf_data(&elf, data) == -1)
    return (1);
  list = extract_symbols(&elf);
  list_sort(list, symcmp);
  list_iter(list, print_symbol);
  delete_list(list);
  if (elf.ehdr->e_ident[EI_CLASS] == ELFCLASS32)
    {
      free(elf.ehdr);
      free(elf.shtab);
    }
  (void)munmap(data, msize);
  return (0);
}
