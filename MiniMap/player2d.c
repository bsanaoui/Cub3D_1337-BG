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

#include "cub3d.h"

void		create_player2d(void)
{
	int x;
	int y;

	x = 0;
	while (x < g_tile_p)
	{
		y = 0;
		while (y < g_tile_p)
			put_pixel_in_img(g_pl_img, x * MAP_SC, MAP_SC * y++, PLAYER_COLOR);
		x++;
	}
}

void		display_player(void)
{
	int x;
	int y;

	x = g_player.x - (g_tile_p / 2);
	y = g_player.y - (g_tile_p / 2);
	mlx_put_image_to_window(g_cub.ptr, g_cub.win, g_pl_img.img,
		x * MAP_SC, y * MAP_SC);
}
