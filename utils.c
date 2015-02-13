/*
** utils.c for malloc in /home/camill_n/rendu/PSU_2014_malloc2
**
** Made by Nicolas Camilli
** Login   <camill_n@epitech.net>
**
** Started on  Thu Feb 12 18:39:44 2015 Nicolas Camilli
** Last update Fri Feb 13 17:02:40 2015 Nicolas Camilli
*/

#include "malloc.h"

/*
  Return the correct needle size:
  - Adjust addr in memory with 8 bytes
  - Calculate the correct page size needle
*/

size_t	get_size(size_t needle_size)
{
  int	nb_pages;

  needle_size += (needle_size % 8) + MINSIZE;
  nb_pages = needle_size / getpagesize();
  ++nb_pages;
  return (nb_pages);
}
