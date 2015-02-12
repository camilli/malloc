/*
** malloc.c for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Mon Feb  9 18:34:36 2015 Nicolas Camilli
** Last update Thu Feb 12 14:45:04 2015 Nicolas Camilli
*/

#include "malloc.h"

static t_chunk	*bins[MAX_SMALLBIN_SIZE] = {0};
static void	*start = NULL;

void		*malloc(size_t size)
{
  t_chunk	*chunk;
  t_chunk	*chunk_next;
  void		*next_ptr;
  size_t	nb_pg_to_alloc;

  size += (size % 8);
  chunk = find_bins(bins, size);
  if (chunk)
    chunk->status = INUSE;
  else
    {
      nb_pg_to_alloc = (size / getpagesize());
      !nb_pg_to_alloc ? ++nb_pg_to_alloc : 0;
      ++nb_pg_to_alloc;
      chunk = sbrk(nb_pg_to_alloc * getpagesize());
      if (start == NULL)
	start = chunk;
      chunk->size = size;
      chunk->status = INUSE;
      next_ptr = chunk + 1;
      next_ptr += size + 1;
      chunk_next = next_ptr;
      chunk_next->size = (nb_pg_to_alloc * getpagesize())
      - CHUNKSIZE - size - 1;
      chunk_next->status = FREE;
      add_bins(bins, chunk_next);
      printf("alloc\n");
      //printf("test %ld", ((double)(chunk + 1)) % 8);
    }
  return (chunk + 1);
}


/* void		*realloc(void *ptr, size_t size) */
/* { */
/*   void		*new_ptr; */
/*   t_chunk	*previous_chunk; */

/*   printf("size de %d oc\n", size); */
/*   new_ptr = malloc(size); */
/*   previous_chunk = ptr; */
/*   --previous_chunk; */
/*   printf("size de %d oc\n", previous_chunk->size); */
/*   memcpy(new_ptr, ptr, previous_chunk->size); */
/*   free(ptr); */
/*   return (new_ptr); */
/* } */

void		free(void *ptr)
{
  t_chunk	*chunk;

  if (!ptr)
    return ;
  chunk = ptr;
  --chunk;
  chunk->status = FREE;
  add_bins(bins, chunk);
}
