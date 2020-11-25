# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 15:57:20 by bsanaoui          #+#    #+#              #
#    Updated: 2019/12/18 15:57:40 by bsanaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all fclean clean re bonus
NAME = Cub3D.a
CC = gcc #-fsanitize=address -g
FLAGS =	-Werror -Wextra -Wall
 
# *************************** SRC && OBJ ******************************* #

SRC = 	libft/ft_atoi.c \
		key_event.c \
		create_2d_map.c \
		player2d.c \
		Ray.c \
		line.c \
		put_pixel_in_img.c \
		utils.c \
		horizontal_intersections.c \
		vertical_intersections.c \
		projection_3d.c \
		render_mini_map.c \
		import_data.c \
		import_data_utils.c \
		import_map.c \
		sprites.c \
		check_map.c \
		import_texture.c \
		import_resol_color.c

OBJ = 	ft_atoi.o \
		key_event.o \
		create_2d_map.o \
		player2d.o \
		Ray.o \
		line.o \
		put_pixel_in_img.o \
		utils.o \
		horizontal_intersections.o \
		vertical_intersections.o \
		projection_3d.o \
		render_mini_map.o \
		import_data.o \
		import_data_utils.o \
		import_map.o \
		sprites.o \
		check_map.o \
		import_texture.o \
		import_resol_color.o

all : $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -c $(SRC) -I.
	@ar -rc $(NAME) $(OBJ)
	@ranlib	$(NAME)

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f *.o

re: fclean all

main:
	@make re
	@$(CC) -I /usr/local/include main.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework Appkit get_next_line.a Cub3D.a libft.a
	@./a.out
	@make fclean