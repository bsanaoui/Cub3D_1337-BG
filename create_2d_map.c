/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Creat_2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:34:52 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/12/19 18:34:57 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			create_grid(int i, int j)
{
	int x;
	int y;

	x = i;
	while (x < g_tile + i)
	{
		y = j;
		while (y < g_tile + j)
			put_pixel_in_img(g_map_img, MAP_SC * x, MAP_SC * y++,
				g_floor_color);
		x++;
	}
}

static	void	create_2d_sprite(int i, int j)
{
	int x;
	int y;

	x = i;
	while (x < (g_tile - 2 + i))
	{
		y = j;
		while (y < (g_tile - 2 + j))
			put_pixel_in_img(g_map_img, MAP_SC * x, MAP_SC * y++, SPRITE_COLOR);
		x++;
	}
}

void			create_2d_map(void)
{
	int	i;
	int	j;
	int w;
	int h;

	i = 0;
	w = 0;
	while (w < g_m.w)
	{
		h = 0;
		j = 0;
		while (h < g_m.h)
		{
			if (g_m.map[h][w] == '1')
				create_grid(i, j);
			else if (g_m.map[h][w] == '2')
				create_2d_sprite(i, j);
			j = j + g_tile;
			h++;
		}
		i = i + g_tile;
		w++;
	}
}
