/*
** malloc.c for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Mon Feb  9 18:34:36 2015 Nicolas Camilli
** Last update Mon Feb 16 15:18:31 2015 Nicolas Camilli
*/

#include "malloc.h"

static void	*start = NULL;

void		*malloc(size_t size)
{
  t_chunk	*ptr;

  (size % 8) ? size += (8 - (size % 8)) : 0;
  if (start)
    collapse_memory(sbrk(0), start);
  else
    start = sbrk(0);
  ptr = find_free_memory(size);
  if (!ptr)
    {
      create_page(size);
      ptr = find_free_memory(size);
    }
  ++ptr;
  if (DEBUG && ptr)
    printf("Malloc return %ld (Ask for %d, given: %ld)\n", ptr, size,
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
  chunk = ptr;
  --chunk;
  if (DEBUG)
    printf("PTR TO FREE %ld\n", chunk);
  if (inuse(chunk))
    {
      //      if (!adjust_brk())
      add_bins(chunk);
      //collapse_chunk(chunk);
    }
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
      ++chunk;
      size & INUSE ? size &= ~INUSE : 0;
      memcpy(new, chunk, size);
      free(chunk);
    }
  return (new);
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*chunk;

  chunk = malloc(nmemb * size);
  if (chunk)
    memset(chunk, 0, nmemb * size);
  return (chunk);
}
