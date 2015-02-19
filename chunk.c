/*
** chunk.c for malloc in /home/camill_n/rendu/PSU_2014_malloc2
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Thu Feb 12 18:39:25 2015 Nicolas Camilli
** Last update Thu Feb 19 22:24:04 2015 Nicolas Camilli
*/

#include "malloc.h"

void		fill_chunk(t_chunk *chunk, size_t size_request)
{
  void		*ptr;
  size_t	adjust;

  size_request & INUSE ? size_request &= ~INUSE : 0;
  chunk->size = size_request;
  ptr = chunk;
  adjust = adjust_size(chunk);
  bzero((void *)chunk + sizeof(t_chunk), chunk->size);
  if (DEBUG)
    printf("SIZE writed at: %ld\n",
	   ptr + MINSIZE + adjust - SIZE_SZ);
  memcpy(ptr + MINSIZE + adjust - SIZE_SZ, &adjust, SIZE_SZ);
}

void		collapse_list_ptr(t_chunk *chunk)
{
  int		index;

  index = get_index(adjust_size(chunk));
  if (!chunk->next && !chunk->prev)
    {
      bins[index] = NULL;
      return ;
    }
  if (!chunk->prev && chunk->next)
    {
      bins[index] = chunk->next;
      return ;
    }
  if (chunk->prev && !chunk->next)
    {
      chunk->prev->next = NULL;
      return ;
    }
  chunk->prev->next = chunk->next;
  chunk->next->prev = chunk->prev;
}

void		*split_chunk(t_chunk *chunk, size_t size_needle)
{
  size_t	size1;
  size_t	size2;
  size_t	size_tot;
  void		*ptr;
  t_chunk	*new;

  size_tot = adjust_size(chunk) + MINSIZE;
  size_needle & INUSE ? size_needle &= ~INUSE : 0;
  size1 = MINSIZE + size_needle;
  size2 = size_tot - size1;
  if (size1 < (8 + MINSIZE) || size2 < MINSIZE)
    return (chunk);
  ptr = (void *)chunk + MINSIZE + size_needle;
  new = ptr;
  if (DEBUG)
    printf("chunk1(%d) : %ld / chunk2(%d) : %ld\n", size1, chunk, size2, new);
  fill_chunk(chunk, size_needle);
  fill_chunk(new, size2 - MINSIZE);
  add_bins(new);
  return (chunk);
}

int		collapse_chunk(t_chunk *chunk_prev, t_chunk *chunk_next)
{
  size_t	new_size;

  if (adjust_size(chunk_next) == 0 || adjust_size(chunk_prev) == 0)
    return (0);
  new_size = adjust_size(chunk_prev) + adjust_size(chunk_next) + MINSIZE;
  printf("PUTIN DE SIZE: chunk_next->size %ld\n", chunk_next->size);

  printf("Chunk collapsed %ld (%ld o) - %ld (%ld o) for a new size of %ld\n",
	 chunk_prev, chunk_prev->size, chunk_next, chunk_next->size, new_size);
  collapse_list_ptr(chunk_next);
  //  collapse_list_ptr(chunk_prev);
  fill_chunk(chunk_prev, new_size);
  add_bins(chunk_prev);
  return (0);
}

void		create_page(size_t size_needle)
{
  void		*p;
  size_t	size_request;
  t_chunk	*chunk;

  size_request = get_size(size_needle);
  size_request *= getpagesize();
  if (DEBUG)
    printf("Allocation de (%d octets) : (%ld) - ", size_request, sbrk(0));
  chunk = sbrk(size_request);
  if (DEBUG)
    printf("(%ld)\n", sbrk(0));
  if ((void *)chunk == (void *)-1)
    return ;
  fill_chunk(chunk, size_request - MINSIZE);
  add_bins(chunk);
}
