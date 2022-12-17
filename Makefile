# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 17:45:50 by abigeddi          #+#    #+#              #
#    Updated: 2022/12/16 02:16:56 by abigeddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub
CC = gcc
MLX = -lmlx -framework OpenGL -framework AppKit
CFLAGS =  -Wall -Wextra -Werror 
SRC = 	main.c \
		checkmap.c \
		check_map.c \
		check_tab.c \
		draw.c \
		ft_func.c \
		ft_split.c \
		get_next_line_utils.c \
		get_next_line.c \
		hooks.c \
		intersection.c


OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(CFLAGS) $(OBJ)  $(MLX) -o $(NAME)

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re :fclean all