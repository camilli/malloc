/*
** chunk.c for malloc in /home/camill_n/rendu/PSU_2014_malloc2
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Thu Feb 12 18:39:25 2015 Nicolas Camilli
** Last update Sat Feb 14 14:33:27 2015 Nicolas Camilli
*/

#include "malloc.h"

void		fill_chunk(t_chunk *chunk, size_t size_request)
{
  void		*ptr;

  chunk->size = size_request;
  ptr = chunk;
  if (DEBUG)
    printf("SIZE writed at: %p\n", ptr + MINSIZE + chunk->size - SIZE_SZ);
  memcpy(ptr + MINSIZE + chunk->size - SIZE_SZ, &chunk->size, SIZE_SZ);
}

void		*split_chunk(t_chunk *chunk, size_t size_needle)
{
  /* int		offset; */
  /* void		*ptr; */
  /* int		size; */

  /* size_needle += size_needle % 8; */
  /* if (DEBUG) */
  /*   printf("Bloc de %d (addr: %p), a découper en %d\n", */
  /* 	   chunk->size, chunk, size_needle); */
  /* offset = size_needle + MINSIZE; */
  /* size = chunk->size; */
  /* ptr = chunk; */
  /* if (chunk->size - offset <= 0) */
  /*   return (NULL); */
  /* ptr += offset; */
  /* if (DEBUG) */
  /*   printf("Nouveau bloc addr: %p\n", ptr); */
  /* fill_chunk(chunk, size_needle); */
  /* fill_chunk(ptr, size - offset); */
  /* add_bins(ptr); */
   return (chunk);
}

void		create_page(size_t size_needle)
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
    return ;
  fill_chunk(chunk, size_request - MINSIZE);
  add_bins(chunk);
}
