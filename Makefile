##
## Makefile for malloc in /home/camill_n/rendu/PSU_2014_malloc
##
## Made by Nicolas Camilli
## Login   <camill_n@epitech.net>
##
## Started on  Mon Feb  9 18:32:06 2015 Nicolas Camilli
## Last update Mon Feb  9 19:14:50 2015 hirt_r
##

ifndef HOSTTYPE
	HOSTTYPE=i386-linux
endif

SRCS = malloc.c \

RM	= rm -f

NAME = libmy_malloc_$(HOSTTYPE).so

CC	= cc -fPIC -shared

OBJS	= $(SRCS:.c=.o)

LN	= ln -sf libmy_malloc_$(HOSTTYPE).so libmy_malloc.so

all:	 $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):$(OBJS)
	  $(CC) $(OBJS) -o $(NAME)
	  $(LN)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
	$(RM) libmy_malloc.so

re: fclean all

