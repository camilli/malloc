/*
** malloc.c for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Mon Feb  9 18:34:36 2015 Nicolas Camilli
** Last update Thu Feb 19 22:39:18 2015 Nicolas Camilli
*/

#include "malloc.h"

static void		*start = NULL;
static pthread_mutex_t	mutex;

void			*malloc(size_t size)
{
  t_chunk		*ptr;

  pthread_mutex_lock(&mutex);
  (size % 8) ? size += (8 - (size % 8)) : 0;
  if (!start)
    {
      pthread_mutex_init(&mutex, NULL);
      start = sbrk(0);
    }
  ptr = find_free_memory(size);
  if (!ptr)
    {
      create_page(size);
      ptr = find_free_memory(size);
    }
  ptr ? set_inuse(ptr) : 0;
  ++ptr;
  if (DEBUG && ptr)
    printf("Malloc return %ld (Ask for %d, given: %ld)\n", ptr, size,
	   (ptr - 1)->size);
  else if (DEBUG && !ptr)
    printf("return NULL\n");
  pthread_mutex_unlock(&mutex);
  return (ptr);
}


void			free(void *ptr)
{
  t_chunk		*chunk;
  t_chunk		*next_chunk;

  if (!ptr)
    return ;
  pthread_mutex_lock(&mutex);
  chunk = ptr;
  --chunk;
  next_chunk = (void *)chunk + adjust_size(chunk) + MINSIZE;
  if (DEBUG)
    printf("PTR TO FREE %ld\n", chunk);
  if (inuse(chunk))
    {
      //      if (!adjust_brk())
      /* if (chunk != start && next_chunk != sbrk(0) && !inuse(next_chunk)) */
      /* 	collapse_chunk(chunk, next_chunk); */
      /* else */
      add_bins(chunk);
    }
  pthread_mutex_unlock(&mutex);
}

void			*realloc(void *ptr, size_t s)
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

void			*calloc(size_t nmemb, size_t size)
{
  void			*chunk;

  chunk = malloc(nmemb * size);
  if (chunk)
    memset(chunk, 0, nmemb * size);
  return (chunk);
}
