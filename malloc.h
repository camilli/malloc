/*
** malloc.h for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Tue Feb 10 17:51:25 2015 Nicolas Camilli
** Last update Wed Feb 11 15:19:30 2015 Nicolas Camilli
*/

#ifndef MALLOC_H_
# define MALLOC_H_
# define FREE 0
# define INUSE 1
# define CHUNKSIZE sizeof(t_chunk)

# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef struct		s_chunk
{
  size_t		size;
  char			status;
  struct s_chunk	*next;
  struct s_chunk	*prev;
}			t_chunk;

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	add_bins(t_chunk **bins_tab, t_chunk *chunk);
t_chunk	*find_bins(t_chunk **bins_tab, size_t size);

#endif
