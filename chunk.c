/*
** chunk.c for malloc in /home/camill_n/rendu/PSU_2014_malloc2
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Thu Feb 12 18:39:25 2015 Nicolas Camilli
** Last update Fri Feb 13 20:58:03 2015 Nicolas Camilli
*/

#include "malloc.h"

void		fill_chunk(t_chunk *chunk, size_t size_request)
{
  void		*ptr;

  chunk->size = size_request - MINSIZE;
  ptr = chunk;
  if (DEBUG)
    printf("SIZE writed at: %p\n", ptr + MINSIZE + chunk->size - SIZE_SZ);
  memcpy(ptr + MINSIZE + chunk->size - SIZE_SZ, &chunk->size, SIZE_SZ);
}

void		split_chunk(t_chunk *chunk, size_t size_needle)
{
  int		current_size;

  current_size = chunk->size;
}

void		*create_page(size_t size_needle)
{
  void		*p;
  size_t	size_request;
  t_chunk	*chunk;

  size_request = get_size(size_needle);
  size_request *= getpagesize();
  if (DEBUG)
    printf("Allocation de (%d octets) : (%p) - ", size_request, sbrk(0));
  chunk = sbrk(size_request);
  if (DEBUG)
    printf("(%p)\n", sbrk(0));
  if ((void *)chunk == (void *)-1)
    {
      return (NULL);
    }
  fill_chunk(chunk, size_request);
  add_bins(chunk);
}
