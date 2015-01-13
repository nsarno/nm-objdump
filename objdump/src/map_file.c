/*
** map_file.c for nm in /home/mesure_a/workspace/c/nm-objdump
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Sat Mar 12 10:34:35 2011 arnaud mesureur
** Last update Sun Mar 13 21:27:05 2011 arnaud mesureur
*/

#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int		map_file(void **map, const char *filename)
{
  int		fd;
  struct stat	sb;
  void		*addr;

  fd = open(filename, O_RDONLY);
  if (fd == -1)
    return (perror(filename), -1);
  if (fstat(fd, &sb) == -1)
    return (perror(filename), -1);
  addr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (addr == MAP_FAILED)
    return (perror("mmap"), -1);
  (void)close(fd);
  *map = addr;
  return (sb.st_size);
}
