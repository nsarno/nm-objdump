/*
** main.c for nm in /home/mesure_a/workspace/c/nm-objdump
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Fri Mar 11 22:34:33 2011 arnaud mesureur
** Last update Sun Mar 13 20:06:27 2011 arnaud mesureur
*/

#include <stdio.h>
#include <stdlib.h>

#include "nm.h"

int	main(int argc, char **argv)
{
  int	status;
  int	i;

  if (argc <= 2)
    return (nm(argc == 1 ? "a.out" : argv[1]));
  status = EXIT_SUCCESS;
  i = 1;
  while (argc-- > 1)
    {
      printf("\n%s:\n", argv[i]);
      if (nm(argv[i++]) == 1)
	status = EXIT_FAILURE;
    }
  return (status);
}
