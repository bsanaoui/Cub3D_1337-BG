/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 14:34:52 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/12/27 14:34:54 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void		create_player2d()
{
	int x;
	int y;

	x = 0;
	while (x < TILE_SIZE_P)
	{
		y = 0;
		while (y < TILE_SIZE_P)
			put_pixel_in_img(player_img, x * MINIMAP_SCALE_FACTOR, MINIMAP_SCALE_FACTOR * y++, COLOR_PLAYER);
		x++;
	}
}

void		display_player()
{
	int x;
	int y;

	x = player.x - (TILE_SIZE_P / 2);
	y = player.y - (TILE_SIZE_P / 2);
	mlx_put_image_to_window(mlx.ptr, mlx.win, player_img.img, x * MINIMAP_SCALE_FACTOR, y * MINIMAP_SCALE_FACTOR);
}