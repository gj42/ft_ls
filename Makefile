# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjensen <gjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/26 10:48:25 by gjensen           #+#    #+#              #
#    Updated: 2014/12/24 15:34:02 by gjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c main.c tool.c long.c

OBJ = ft_ls.o main.o tool.o long.o

CFLAGS = -Werror -Wall -Wextra

LIB = -I ./libft/includes

$(NAME):
	make -C libft/ fclean
	make -C libft/
	gcc $(CFLAGS) -c $(SRC) $(LIB)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft

all: $(NAME)

.PHONY: clean fclean re

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
