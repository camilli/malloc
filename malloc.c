/*
** malloc.c for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Mon Feb  9 18:34:36 2015 Nicolas Camilli
** Last update Sat Feb 14 13:55:55 2015 Nicolas Camilli
*/

#include "malloc.h"

void		*malloc(size_t size)
{
  t_chunk	*ptr;

  ptr = find_free_memory(size);
  if (!ptr)
    {
      create_page(size);
      ptr = find_free_memory(size);
    }
  size_t *ptir = (void *)ptr - SIZE_SZ;
  static int i = 0;
  if (i > 0)
    printf("Taille prev: %d (%p)\n", *ptir, ptir);
  ++i;
  ++ptr;
  if (DEBUG && ptr)
    printf("Malloc return %p (Ask for %d, given: %d)\n", ptr, size,
	   (ptr - 1)->size);
  else if (DEBUG && !ptr)
    printf("return NULL\n");
  return (ptr);
}

void		free(void *ptr)
{
  t_chunk	*chunk;

  if (!ptr)
    return ;
  if (DEBUG)
    printf("PTR TO FREE %p\n", ptr);
  chunk = ptr;
  --ptr;
  if (inuse(chunk))
    add_bins(ptr);
}
