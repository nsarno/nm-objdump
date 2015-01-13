/*
** symbols_table_to_list.c for nm  in /home/mesure_a/workspace/c/nm-objdump/nm
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sun Mar 13 17:36:13 2011 arnaud mesureur
** Last update Sun Mar 13 23:11:09 2011 arnaud mesureur
*/

#include <elf.h>
#include <stddef.h>
#include <string.h>

#include "nm.h"

/*
** no comments for you
** it was hard to write
** so it should be hard to read
*/
static int	is_from_section(Elf64_Sym *symtab, t_elf *elf, const char *s)
{
  return (!strcmp(&(elf->shstrtab)[elf->shtab[symtab->st_shndx].sh_name], s));
}

static char	determine_st_flag_roftb(Elf64_Sym *symtab, Elf64_Addr value,
					t_elf *elf)
{
  if (ELF64_ST_BIND(symtab->st_info) == STB_WEAK)
    {
      if (!value)
	return (ELF64_ST_TYPE(symtab->st_info) == STT_OBJECT ? 'v' : 'w');
      return (ELF64_ST_TYPE(symtab->st_info) == STT_OBJECT ? 'V' : 'W');
    }
  else if (symtab->st_shndx == SHN_COMMON)
    return ('C');
  else if (symtab->st_shndx == SHN_UNDEF)
    return ('U');
  else if (is_from_section(symtab, elf, ".debug"))
    return ('N');
  return (0);
}

static char	determine_st_flag(char *t, Elf64_Sym *symtab,
				  Elf64_Addr value, t_elf *elf)
{
  if (symtab->st_shndx == SHN_ABS)
    *t = 'a';
  else if ((*t = determine_st_flag_roftb(symtab, value, elf)))
    return (*t);
  else if (is_from_section(symtab, elf, ".bss"))
    *t = 'b';
  else if (is_from_section(symtab, elf, ".text")
	   || ELF64_ST_TYPE(symtab->st_info) == STT_FUNC)
    *t = 't';
  else if (is_from_section(symtab, elf, ".rodata"))
    *t = 'r';
  else if (ELF64_ST_TYPE(symtab->st_info) == STT_OBJECT
	   || ELF64_ST_TYPE(symtab->st_info) == STT_NOTYPE
	   || is_from_section(symtab, elf, ".data")
	   || is_from_section(symtab, elf, ".data1"))
    *t = 'd';
  else
    return ('?');
  return (ELF64_ST_BIND(symtab->st_info) == STB_LOCAL ? *t : *t - 32);
}

static int	isprintable(t_elf *elf, Elf64_Sym *st)
{
  return (elf->strtab[st->st_name] && ELF64_ST_TYPE(st->st_info) != STT_FILE);
}

t_sym_list	*symbols_table_to_list(t_sym_list *list,
				       Elf64_Shdr *symhdr,
				       Elf64_Sym *symtab,
				       t_elf *elf)
{
  t_sym		symbol;
  size_t	nentries;
  size_t	i;

  i = 0;
  nentries = symhdr->sh_size / symhdr->sh_entsize;
  while (i < nentries)
    {
      if (isprintable(elf, &symtab[i]))
	{
	  symbol.value = symtab[i].st_value;
	  symbol.name = &(elf->strtab[symtab[i].st_name]);
	  symbol.type = determine_st_flag(&symbol.type, &symtab[i],
					  symbol.value, elf);
	  list_add_front(list, &symbol, sizeof(symbol));
	}
      ++i;
    }
  return (list);
}
