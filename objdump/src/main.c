/*
** objdump.c for objdump in /home/mesure_a/workspace/c/nm-objdump/objdump
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sun Mar 13 09:43:24 2011 arnaud mesureur
** Last update Sun Mar 13 22:39:16 2011 arnaud mesureur
*/

#include <stdio.h>
#include <stdlib.h>

#include "objdump.h"

int	main(int argc, char **argv)
{
  int	status;
  int	i;

  if (argc <= 2)
    return (objdump(argc == 1 ? DEFAULT_BIN : argv[1]));
  status = EXIT_SUCCESS;
  i = 1;
  while (argc-- > 1)
    {
      printf("\n%s:\n\n", argv[i]);
      if (objdump(argv[i++]) == 1)
	status = EXIT_FAILURE;
    }
  return (status);
}
