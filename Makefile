##
## Makefile for malloc in /home/camill_n/rendu/PSU_2014_malloc
##
## Made by Nicolas Camilli
## Login   <camill_n@epitech.net>
##
## Started on  Mon Feb  9 18:32:06 2015 Nicolas Camilli
## Last update Mon Feb  9 18:39:20 2015 Nicolas Camilli
##

SRCS = malloc.c \

RM	= rm -f

NAME = malloc

CC	= cc -fPIC -shared

OBJS	= $(SRCS:.c=.o)


all:	 $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):$(OBJS)
	  $(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
