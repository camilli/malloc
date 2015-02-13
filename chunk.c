/*
** chunk.c for malloc in /home/camill_n/rendu/PSU_2014_malloc2
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Thu Feb 12 18:39:25 2015 Nicolas Camilli
** Last update Fri Feb 13 14:41:42 2015 Nicolas Camilli
*/

#include "malloc.h"

void		fill_chunk(t_chunk *chunk, size_t size_request)
{
  void		*ptr;


  chunk->size = size_request;
  printf("sr: %d\n", size_request);
  ptr = chunk;
  memcpy((ptr + size_request - SIZE_SZ), &chunk->size, SIZE_SZ);
}

void		*create_page(size_t size_needle)
{
  void		*p;
  size_t	size_request;
  t_chunk	*chunk;

  size_request = get_size(size_needle);
  printf("Création de %d pages", size_request);
  size_request *= getpagesize();
  printf(" pour une size totale de: %d\n", size_request);
  chunk = sbrk(size_request);
  fill_chunk(chunk, size_request);
  add_bins(chunk);
}
