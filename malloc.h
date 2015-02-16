/*
** malloc.h for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Tue Feb 10 17:51:25 2015 Nicolas Camilli
** Last update Mon Feb 16 15:20:44 2015 Nicolas Camilli
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# define SIZE_SZ (sizeof(size_t))
# define MINSIZE (sizeof(t_chunk) + SIZE_SZ)
# define MAX_SMALLBIN_OFFSET  18
# define MAX_SMALLBIN_SIZE   144
# define DEBUG 1

# define INUSE 0x01

# define inuse(p)       ((p)->size & INUSE)
# define set_inuse(p)   ((p)->size |= INUSE)
# define clear_inuse(p) ((p)->size &= ~INUSE)

# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>
# include <math.h>

typedef struct		s_chunk
{
  size_t		size;
  struct s_chunk	*next;
  struct s_chunk	*prev;
}			t_chunk;

static t_chunk	*bins[MAX_SMALLBIN_SIZE] = {0};

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t nmemb, size_t size);
void	free(void *ptr);
void	create_page(size_t size_needle);
void	add_bins(t_chunk *chunk);
t_chunk	*find_free_memory(size_t size);
size_t	get_size(size_t);
void	*split_chunk(t_chunk *chunk, size_t size_needle);
int	collapse_chunk(t_chunk *chunk_prev, t_chunk *next_chunk);
size_t	adjust_size(t_chunk *ptr);
void	collapse_memory(t_chunk *chunk, void *start);
int	adjust_brk();

#endif
