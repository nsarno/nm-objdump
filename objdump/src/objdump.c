/*
** objdump.c for objdump in /home/mesure_a/workspace/c/nm-objdump/objdump
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sun Mar 13 09:45:54 2011 arnaud mesureur
** Last update Sun Mar 13 22:55:07 2011 arnaud mesureur
*/

#include <ctype.h>
#include <elf.h>
#include <stddef.h>
#include <stdio.h>
#include <strings.h>
#include <sys/mman.h>
#include <stdlib.h>

#include "objdump.h"

static char	dump_byte(char b)
{
  b > 0 ? printf("%02x", b) : printf("00");
  return (isprint(b) ? b : '.');
}

static void	dump_section(char *section, Elf64_Shdr *shdr, size_t bpl)
{
  char		buf[BPL + 1];
  size_t	s_off;
  size_t	i;
  size_t	j;

  s_off = 0;
  while (s_off < shdr->sh_size)
    {
      i = 0;
      printf(" %04x", (unsigned)(shdr->sh_addr + s_off));
      while (i < bpl && s_off + i < shdr->sh_size)
	{
	  j = 0;
	  printf(" ");
	  while (j < 4 && s_off + i + j < shdr->sh_size)
	    {
	      buf[i + j] = dump_byte(section[s_off + i + j]);
	      ++j;
	    }
	  i += j;
	}
      buf[BPL] = '\0';
      printf(" %s\n", buf);
      s_off += i;
    }
}

static void	display_sections(t_elf *elf)
{
  void		*section;
  size_t	i;

  i = 0;
  while (i < elf->ehdr->e_shnum)
    {
      section = elf->addr + elf->shtab[i].sh_offset;
      if (section == elf->shstrtab)
	break;
      if (elf->shtab[i].sh_type != SHT_NOBITS
	  && elf->shtab[i].sh_type != SHT_SYMTAB
	  && elf->shstrtab[elf->shtab[i].sh_name])
 	{
	  printf("Contents of section %s:\n",
		 &(elf->shstrtab)[elf->shtab[i].sh_name]);
	  dump_section(section, &(elf->shtab)[i], BPL);
	}
      ++i;
    }
}

int	objdump(const char *filename)
{
  void	*data;
  t_elf	elf;
  int	msize;

  if ((msize = map_file(&data, filename)) == -1)
    return (-1);
  if (init_elf_data(&elf, data) == -1)
    return (-1);
  display_sections(&elf);
  if (elf.ehdr->e_ident[EI_CLASS] == ELFCLASS32)
    {
      free(elf.ehdr);
      free(elf.shtab);
    }
  (void)munmap(data, msize);
  return (0);
}
