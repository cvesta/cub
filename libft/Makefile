# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvesta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/06 16:32:48 by cvesta            #+#    #+#              #
#    Updated: 2020/11/18 18:29:56 by cvesta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memcpy.c ft_memset.c  ft_strlen.c ft_tolower.c ft_toupper.c ft_strlcpy.c ft_memmove.c ft_memchr.c ft_strncmp.c ft_memcmp.c ft_strdup.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_strnstr.c ft_split.c 
OBJS = $(SRCS:.c=.o)

ARCH = ar rc

HEADER = libft.h

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(HEADER)

$(NAME):	$(OBJS)
			$(ARCH) $(NAME) $(OBJS) 

all: 		$(NAME)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re

