/* -*- C -*-
** nm.h for nm in /home/mesure_a/workspace/c/nm-objdump
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Fri Mar 11 22:26:58 2011 arnaud mesureur
** Last update Sun Mar 13 20:39:52 2011 arnaud mesureur
*/

#ifndef NM_H_
# define NM_H_

# include <elf.h>

# include "list.h"

typedef struct list t_sym_list;

/*
** Elf structure content
** ---------------------
**
** addr		: starting addr of file
** ehdr		: elf header
** shtab	: section header table
** shstrtab	: section header string table
** strtab	: symbols string table
*/

typedef struct	s_elf
{
  char		*addr;
  Elf64_Ehdr	*ehdr;
  Elf64_Shdr	*shtab;
  char		*shstrtab;
  char		*strtab;
}		t_elf;

typedef struct	s_sym
{
  Elf64_Addr	value;
  char		*name;
  char		type;
}		t_sym;

/*
** prototypes
*/

int		nm(const char *filename);
int		map_file(void **data, const char *filename);
int		init_elf_data(t_elf *elf, void *data);
int		check_file_format(unsigned char *e);
t_sym_list	*extract_symbols(t_elf *elf);
t_sym_list	*symbols_table_to_list(t_sym_list *list,
				       Elf64_Shdr *symhdr,
				       Elf64_Sym *symtab,
				       t_elf *elf);

#endif /* NM_H_ */

