/*
** malloc.c for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Mon Feb  9 18:34:36 2015 Nicolas Camilli
** Last update Sat Feb 14 22:04:25 2015 Nicolas Camilli
*/

#include "malloc.h"

void		*malloc(size_t size)
{
  t_chunk	*ptr;

  if (size % 8)
    size += (8 - (size % 8));
  ptr = find_free_memory(size);
  if (!ptr)
    {
      create_page(size);
      ptr = find_free_memory(size);
    }
  size_t *ptir = (void *)ptr - SIZE_SZ;
  static int i = 0;
  /* if (i > 0) */
  /*   printf("Taille prev: %d (%p)\n", *ptir, ptir); */
  /* ++i; */
  if (i > 0)
    collapse_memory(start);
  ++i;
  ++ptr;
  if (DEBUG && ptr)
    printf("Malloc return %ld (Ask for %d, given: %d)\n", ptr, size,
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
    printf("PTR TO FREE %ld\n", chunk);
  chunk = ptr;
  --chunk;
  if (inuse(chunk))
    add_bins(chunk);
}

void	*realloc(void *ptr, size_t s)
{
  t_chunk		*chunk;
  size_t		size;
  t_chunk		*new;

  new = malloc(s);
  if (ptr)
    {
      chunk = ptr;
      --chunk;
      size = chunk->size;
      chunk++;
      memcpy(new, chunk, size);
      free(chunk);
    }
  return (new);
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*chunk;
  int		i;
  size_t	addr;

  chunk = malloc(nmemb * size);
  if (chunk)
    memset(chunk, 0, nmemb * size);
  return (chunk);
}
