/*
** bins.c for malloc in /home/camill_n/rendu/PSU_2014_malloc
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Tue Feb 10 20:05:09 2015 Nicolas Camilli
** Last update Wed Feb 11 15:03:19 2015 Nicolas Camilli
*/

#include "malloc.h"

void		add_bins(t_chunk **bins_tab, t_chunk *chunk)
{
  t_chunk	*tmp;
  int		index;

  index = (int)(chunk->size / 8) > 127 ? 127 : (int)(chunk->size / 8);
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

t_chunk		*find_bins(t_chunk **bins_tab, size_t size)
{
 t_chunk	*tmp;
 int		index;

 index = (int)(size / 8) > 127 ? 127 : (int)(size / 8);
 while (index < 128)
   {
     //     printf("try (%d)\n", index);
     tmp = bins_tab[index];
     if (tmp)
       {
	 bins_tab[index] = tmp->next;
	 if (tmp->next)
	   tmp->next->prev = NULL;
	 //	 printf("recuperation de l'espace memoire(%do) a l'index: %d\n",
	 //	tmp->size, index);
	 return (tmp);
       }
     ++index;
   }
 return (NULL);
}
