/*
** utils.c for malloc in /home/camill_n/rendu/PSU_2014_malloc2
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Thu Feb 12 18:39:44 2015 Nicolas Camilli
** Last update Mon Feb 16 14:55:59 2015 Nicolas Camilli
*/

#include "malloc.h"

/*
  Return the correct needle size:
  - Adjust addr in memory with 8 bytes
  - Calculate the correct page size needle
*/

size_t		get_size(size_t needle_size)
{
  int	nb_pages;

  needle_size += MINSIZE;
  nb_pages = needle_size / getpagesize();
  ++nb_pages;
  return (nb_pages);
}

size_t		adjust_size(t_chunk *ptr)
{
  size_t	adjust;

  adjust = ptr->size;
  inuse(ptr) ? adjust &= ~INUSE : 0;
  return (adjust);
}

int		adjust_brk()
{
  void		*end;
  size_t	last_size;

  end = sbrk(0);
  last_size = *((size_t *)(end - SIZE_SZ));
  last_size & INUSE ? last_size &= ~INUSE : 0;
  printf("BRK last_size: %d\n", last_size);
  if (last_size + MINSIZE == getpagesize())
    {
      if (DEBUG)
	printf("BRK Adjust\n");
      brk(end - last_size - MINSIZE);
      return (1);
    }
  return (0);
}
