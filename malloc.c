/*
** malloc.c for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Mon Feb  9 18:34:36 2015 Nicolas Camilli
** Last update Fri Feb 13 15:44:02 2015 Nicolas Camilli
*/

#include "malloc.h"

void		*malloc(size_t size)
{
  t_chunk	*ptr;

  if (size <= 0)
    return (NULL);
  ptr = find_free_memory(size);
  if (!ptr)
    {
      create_page(size);
      ptr = find_free_memory(size);
    }
  if (ptr)
    printf("ptr: %d\n", ptr->size);
  if (ptr)
    ++ptr;
  return (ptr);
}

void		free(void *ptr)
{
  t_chunk	*chunk;

  chunk = ptr;
  --chunk;
  add_bins(chunk);
}
