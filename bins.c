/*
** bins.c for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Tue Feb 10 20:05:09 2015 Nicolas Camilli
** Last update Thu Feb 12 14:59:10 2015 Nicolas Camilli
*/

#include "malloc.h"

void		*split_chunk(t_chunk **bins_tab, t_chunk *chunk, size_t size)
{
  int		size_tot;
  t_chunk	*next_chunk;
  void		*next_ptr;

  if (chunk->size - (CHUNKSIZE + size) <= 0)
    return (NULL);
  size_tot = chunk->size;
  chunk->size = size;
  next_chunk = chunk;
  ++next_chunk;
  next_ptr = next_chunk;
  next_ptr += size + 1;
  next_chunk = next_ptr;
  next_chunk->size = size_tot - CHUNKSIZE - size;
  next_chunk->status = FREE;
  if (next_chunk->size > 0)
    add_bins(bins_tab, next_chunk);
  printf("CHUNK size at start: %d, CHUNKSIZE %d\n", size_tot, size);
  printf("CHUNK size after at start: %d, CHUNKSIZE %d\n",
	 next_chunk->size, size);
  return (chunk);
}

void		add_bins(t_chunk **bins_tab, t_chunk *chunk)
{
  t_chunk	*tmp;
  int		index;

  index = get_index(chunk->size);
  if (index >= MAX_SMALLBIN_SIZE)
    index = MAX_SMALLBIN_SIZE - 1;
  tmp = bins_tab[index];
  if (tmp == NULL)
    {
      bins_tab[index] = chunk;
      chunk->next = NULL;
      chunk->prev = NULL;
    }
  else
    {
      if (tmp->next)
	tmp->next->prev = chunk;
      chunk->next = tmp;
      chunk->prev = NULL;
    }
  //printf("add free chunk at addr: %d\n", index);
}

int		get_index(size_t size)
{
  size_t	ifb;
  size_t	sfb;

  sfb = size;
  if (sfb < MAX_SMALLBIN_SIZE)
    return (sfb / 8);
  else
    {
      ifb = MAX_SMALLBIN_OFFSET;
      sfb >>= 3;
      while (sfb >= (MINSIZE * 2))
	{
	  ifb += 4;
	  sfb >>= 1;
	}
      ifb += (sfb - MINSIZE) >> 2;
      return (ifb);
    }
}

t_chunk		*find_bins(t_chunk **bins_tab, size_t size)
{
 t_chunk	*tmp;
 t_chunk	*tmp2;
 int		index;

 index = get_index(size);
 while (index < MAX_SMALLBIN_SIZE)
   {
     //     printf("try (%d)\n", index);
     tmp = bins_tab[index];
     if (tmp)
       {
	 bins_tab[index] = tmp->next;
	 if (tmp->next)
	   tmp->next->prev = NULL;
	 tmp2 = split_chunk(bins_tab, tmp, size + (size % 8));
	 tmp2 ? tmp = tmp2 : 0;
	 printf ("request: %d, given: %d\n", size, tmp->size);
	 return (tmp);
       }
     ++index;
   }
 return (NULL);
}
