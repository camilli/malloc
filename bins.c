/*
** bins.c for malloc in /home/camill_n/rendu/PSU_2014_malloc2
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Thu Feb 12 18:39:17 2015 Nicolas Camilli
** Last update Fri Feb 13 15:43:16 2015 Nicolas Camilli
*/

#include "malloc.h"

int	get_index(int size)
{
  size_t	ifb;
  size_t	sfb;

  sfb = size;
  if (sfb < MAX_SMALLBIN_SIZE)
    ifb = sfb / 8;
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
    }
  return (ifb);
}

void	add_bins(t_chunk *chunk)
{
  int	index;

  index = get_index(chunk->size);
  clear_inuse(chunk);
  if (!bins[index])
    {
      chunk->next = NULL;
      chunk->prev = NULL;
      bins[index] = chunk;
    }
  else
    {
      chunk->prev = NULL;
      chunk->next = bins[index];
      bins[index] = chunk;
    }
}


t_chunk		*find_free_memory(size_t size)
{
  int		index;
  t_chunk	*chunk;

  index = get_index(size);
  while (index < MAX_SMALLBIN_SIZE)
    {
      if (bins[index])
	{
	  printf("dd\n");
	  chunk = bins[index];
	  bins[index] = chunk->next;
	  if (chunk->next)
	    chunk->next->prev = NULL;
	  set_inuse(chunk);
	  if (chunk)
	    printf("-> %d\n", chunk->size);
	  return (chunk);
	}
      ++index;
    }
  return (NULL);
}
