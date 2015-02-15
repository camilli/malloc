/*
** chunk.c for malloc in /home/camill_n/rendu/PSU_2014_malloc2
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Thu Feb 12 18:39:25 2015 Nicolas Camilli
** Last update Sat Feb 14 22:03:27 2015 Nicolas Camilli
*/

#include "malloc.h"

void		fill_chunk(t_chunk *chunk, size_t size_request)
{
  void		*ptr;

  chunk->size = size_request;
  ptr = chunk;
  if (DEBUG)
    printf("SIZE writed at: %ld\n", ptr + MINSIZE + chunk->size - SIZE_SZ);
  memcpy(ptr + MINSIZE + chunk->size - SIZE_SZ, &chunk->size, SIZE_SZ);
}

void		*split_chunk(t_chunk *chunk, size_t size_needle)
{
  size_t	size1;
  size_t	size2;
  size_t	size_tot;
  void		*ptr;
  t_chunk	*new;

  size_tot = chunk->size + MINSIZE;
  if (DEBUG)
    printf("size_tot: %d\n", size_tot);
  size1 = MINSIZE + size_needle;
  size2 = size_tot - size1;
  if (size2 < MINSIZE)
    return (chunk);
  ptr = (void *)chunk + MINSIZE + size_needle;
  new = ptr;
  if (DEBUG)
    printf("chunk1(%d) : %ld / chunk2(%d) : %ld\n", size1, chunk, size2, new);
  fill_chunk(chunk, size_needle);
  fill_chunk(new, size2 - MINSIZE);
  clear_inuse(new);
  add_bins(new);
  return (chunk);
}

void		collapse_list_ptr(t_chunk *chunk)
{
  int		index;

  index = get_index(chunk->size);
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

void		collapse_chunk(t_chunk *chunk)
{
  t_chunk	*next_ptr;
  size_t	new_size;

  next_ptr = (t_chunk *)((void *)chunk + chunk->size + MINSIZE);
  if (!inuse(chunk) && !inuse(next_ptr))
    {
      new_size = chunk->size + next_ptr->size + MINSIZE;
      collapse_list_ptr(chunk);
      collapse_list_ptr(next_ptr);
      fill_chunk(chunk, new_size);
      add_bins(chunk);
    }
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
  if (!start)
    start = sbrk(0);
  if (DEBUG)
    printf("(%ld)\n", sbrk(0));
  if ((void *)chunk == (void *)-1)
    return ;
  fill_chunk(chunk, size_request - MINSIZE);
  add_bins(chunk);
}
