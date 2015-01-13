/*
** init_elf_data.c for nm in /home/mesure_a/workspace/c/nm-objdump
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Fri Mar 11 22:29:14 2011 arnaud mesureur
** Last update Sun Mar 13 23:19:19 2011 arnaud mesureur
*/

#include <elf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "nm.h"

static char*	get_shstrtab(Elf64_Shdr *shtab,
			     Elf64_Half strndx,
			     char *addr)
{
  if (strndx == SHN_UNDEF)
    return (fprintf(stderr, "cannot get section header string table index"),
	    NULL);
  return (addr + shtab[strndx].sh_offset);
}

static char*	get_strtab(t_elf *elf)
{
  char		*shstrtab;
  size_t	i;

  i = 0;
  shstrtab = elf->shstrtab;
  while (i < elf->ehdr->e_shnum)
    {
      if (!strcmp(&shstrtab[elf->shtab[i].sh_name], ".strtab"))
	return (elf->addr + elf->shtab[i].sh_offset);
      ++i;
    }
  fprintf(stderr, "no string table\n");
  return (NULL);
}

static void	fit_elf_header(t_elf *elf, Elf32_Ehdr *data)
{
  memcpy(elf->ehdr->e_ident, data->e_ident, EI_NIDENT);
  elf->ehdr->e_type = data->e_type;
  elf->ehdr->e_machine = data->e_machine;
  elf->ehdr->e_version = data->e_version;
  elf->ehdr->e_entry = data->e_entry;
  elf->ehdr->e_phoff = data->e_phoff;
  elf->ehdr->e_shoff = data->e_shoff;
  elf->ehdr->e_flags = data->e_flags;
  elf->ehdr->e_ehsize = data->e_ehsize;
  elf->ehdr->e_phentsize = data->e_phentsize;
  elf->ehdr->e_phnum = data->e_phnum;
  elf->ehdr->e_shentsize = data->e_shentsize;
  elf->ehdr->e_shnum = data->e_shnum;
  elf->ehdr->e_shstrndx = data->e_shstrndx;
}

static void	fit_sh_table(t_elf *elf, Elf32_Shdr *data, size_t len)
{
  size_t	i;

  i = 0;
  while (i < len)
    {
      elf->shtab[i].sh_name = data[i].sh_name;
      elf->shtab[i].sh_type = data[i].sh_type;
      elf->shtab[i].sh_flags = data[i].sh_flags;
      elf->shtab[i].sh_addr = data[i].sh_addr;
      elf->shtab[i].sh_offset = data[i].sh_offset;
      elf->shtab[i].sh_size = data[i].sh_size;
      elf->shtab[i].sh_link = data[i].sh_link;
      elf->shtab[i].sh_info = data[i].sh_info;
      elf->shtab[i].sh_addralign = data[i].sh_addralign;
      elf->shtab[i].sh_entsize = data[i].sh_entsize;
      ++i;
    }
}

int	init_elf_data(t_elf *elf, void *data)
{
  elf->addr = data;
  elf->ehdr = data;
  if (!check_file_format(elf->ehdr->e_ident))
    return (fprintf(stderr, "file format not recognize\n"), -1);
  elf->shtab = (Elf64_Shdr*)(elf->addr + elf->ehdr->e_shoff);
  if (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
    {
      elf->ehdr = malloc(sizeof(*(elf->ehdr)));
      if (NULL == elf->ehdr)
	return (perror("malloc"), -1);
      fit_elf_header(elf, data);
      elf->shtab = malloc(sizeof(*(elf->shtab)) * elf->ehdr->e_shnum);
      if (NULL == elf->shtab)
	return (perror("malloc"), -1);
      fit_sh_table(elf, (Elf32_Shdr*)(elf->addr + elf->ehdr->e_shoff),
		   elf->ehdr->e_shnum);
    }
  if (NULL == (elf->shstrtab = get_shstrtab(elf->shtab,
					    elf->ehdr->e_shstrndx,
					    elf->addr)))
    return (-1);
  if (NULL == (elf->strtab = get_strtab(elf)))
    return (-1);
  return (0);
}
