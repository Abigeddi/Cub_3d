# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iel-bakk < iel-bakk@student.1337.ma>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 17:45:50 by abigeddi          #+#    #+#              #
#    Updated: 2023/02/05 19:08:55 by iel-bakk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc 
MLXE = libmlx.a
MLX = -lmlx -framework OpenGL -framework AppKit
CFLAGS =  -Wall -Wextra -Werror
SRC = 	main.c \
		checkmap.c \
		check_map.c \
		check_tab.c \
		ft_func.c \
		ft_split.c \
		get_next_line_utils.c \
		get_next_line.c \
		hooks.c \
		v_intersect.c \
		h_intersect.c \
		drawheight.c \
		texture_check.c \
		free_functions.c \
		angle_and_distance.c \
		check_tab_and_vertical.c \
		key.c \
		data_init.c	\
		drawing_tools.c \
		texture_helper.c \
		get_param_function_file.c \
		get_param_extra_file.c \
		checkmap_helper.c \
		check_colors.c \
		play_game.c 

OBJ = $(SRC:%.c=%.o)

LIB = cub.h

all : $(NAME)

$(NAME) : $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

%.o : %.c $(LIB)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re :fclean all