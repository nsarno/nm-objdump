/*
** check_file_format.c for nm in /home/mesure_a/workspace/c/nm-objdump/nm
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sun Mar 13 20:38:55 2011 arnaud mesureur
** Last update Sun Mar 13 20:56:10 2011 arnaud mesureur
*/

#include <elf.h>

int	check_file_format(unsigned char *e)
{
  return (e[EI_MAG0] == 0x7f
 	  && e[EI_MAG1] == 'E'
  	  && e[EI_MAG2] == 'L'
  	  && e[EI_MAG3] == 'F');
}
