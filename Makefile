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

.PHONY: all fclean clean re
NAME = cub3D
CC = gcc -Werror -Wextra -Wall #-fsanitize=address -g
FLAGS =	 -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework Appkit
 
# *************************** SRC && OBJ ******************************* #

SRC = 	main.c \
		ImportConfig/ft_atoi_parse.c \
		ImportConfig/check_map.c \
		ImportConfig/import_texture.c \
		ImportConfig/import_resol_color.c \
		ImportConfig/import_data.c \
		ImportConfig/import_data_utils.c \
		ImportConfig/import_map.c \
		RayCasting/inter_horiz.c \
		RayCasting/inter_vert.c \
		RayCasting/ray_casting.c \
		Utils/utils.c \
		Utils/screen_bmp.c \
		Utils/line.c \
		Utils/get_args.c \
		Utils/put_pixel_in_img.c \
		Renders/render_3d.c \
		Renders/render_mini_map.c \
		Renders/render_3d_utils.c \
		MiniMap/create_2d_map.c \
		MiniMap/player2d.c \
		sprites.c \
		move_player.c \
		key_event.c \

all : $(NAME)

$(NAME):
	@$(CC) $(SRC) -I. $(FLAGS) get_next_line.a libft.a  -o $(NAME)

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f *.o

re: fclean all