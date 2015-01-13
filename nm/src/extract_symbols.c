/*
** extract_symbols.c for extract symbols in /home/mesure_a/workspace/c/nm-objdump
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sat Mar 12 10:42:22 2011 arnaud mesureur
** Last update Sun Mar 13 21:19:45 2011 arnaud mesureur
*/

#include <stdlib.h>
#include <stddef.h>
#include <elf.h>
#include <string.h>
#include <stdio.h>

#include "list.h"
#include "nm.h"

static void	fit_symbol(Elf64_Sym *st, Elf32_Sym *addr)
{
  st->st_name = addr->st_name;
  st->st_value = addr->st_value;
  st->st_size = addr->st_size;
  st->st_info = addr->st_info;
  st->st_other = addr->st_other;
  st->st_shndx = addr->st_shndx;
}

static Elf64_Sym	*fit_symbol_table(void *addr, Elf64_Shdr *shdr,
					  t_elf *elf)
{
  Elf64_Sym		*st;
  Elf32_Sym		*data;
  size_t		nmemb;
  size_t		i;

  if (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS64)
    st = (Elf64_Sym*)addr;
  else
    {
      i = 0;
      data = addr;
      nmemb = shdr->sh_size / shdr->sh_entsize;
      st = malloc(sizeof(*st) * nmemb);
      if (NULL == st)
	return (perror("malloc"), NULL);
      while (i < nmemb)
	{
	  fit_symbol(&(st[i]), &(data[i]));
	  ++i;
	}
    }
  return (st);
}

static Elf64_Sym	*get_next_symtab(Elf64_Shdr **shdr,
					 t_elf *elf)
{
  static size_t		i = 0;
  Elf64_Ehdr		*ehdr;
  Elf64_Shdr		*shtab;

  ehdr = elf->ehdr;
  shtab = elf->shtab;
  while (i < ehdr->e_shnum)
    {
      if (shtab[i].sh_type == SHT_SYMTAB)
	{
	  *shdr = &shtab[i++];
	  return (fit_symbol_table(elf->addr + (*shdr)->sh_offset,
				   *shdr, elf));
	}
      ++i;
    }
  i = 0;
  return (NULL);
}

t_sym_list	*extract_symbols(t_elf *elf)
{
  t_sym_list	*list;
  Elf64_Shdr	*symhdr;
  Elf64_Sym	*symtab;

  list = new_list_by_default();
  while ((symtab = get_next_symtab(&symhdr, elf)))
    {
      list = symbols_table_to_list(list, symhdr, symtab, elf);
      if (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
	free(symtab);
    }
  return (list);
}
