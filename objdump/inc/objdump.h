/* -*- C -*-
** objdump.h for objdump in /home/mesure_a/workspace/c/nm-objdump/objdump
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sun Mar 13 09:44:37 2011 arnaud mesureur
** Last update Sun Mar 13 22:46:19 2011 arnaud mesureur
*/

#ifndef		OBJDUMP_H_
# define	OBJDUMP_H_

#include <elf.h>

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


#define	DEFAULT_BIN "a.out"

/* byte per line for output format */
#define	BPL 16


/*
** Prototypes
** ----------
*/

int	objdump(const char *filename);
int	map_file(void **data, const char *filename);
int	init_elf_data(t_elf *elf, void *data);
int	check_file_format(unsigned char *e);

#endif		/* OBJDUMP_H_ */
