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

void	create_grid(int i, int j)
{
	int x;
	int y;

	x = i;
	while (x < TILE_SIZE + i)
	{
		y = j;
		while (y < TILE_SIZE + j)
			put_pixel_in_img(map_img, MAP_SC * x,MAP_SC * y++, FLOOR_COLOR);
		x++;
	}
}

static	void	create_2d_sprite(int i, int j)
{
	int x;
	int y;

	x = i;
	while (x < (TILE_SIZE - 2 + i))
	{
		y = j;
		while (y < (TILE_SIZE - 2 + j))
			put_pixel_in_img(map_img, MAP_SC * x,MAP_SC * y++, SPRITE_COLOR);
		x++;
	}
}

void	create_2d_map(void)
{
	int	i = 0;
	int	j = 0;
	int MAP_WD = 0;
	int MAP_HT;

	while (MAP_WD < m.w)
	{
		MAP_HT = 0;
		j = 0;
		while (MAP_HT < m.h)
		{
			if (m.map[MAP_HT][MAP_WD] == '1')
				create_grid(i, j);
			else if (m.map[MAP_HT][MAP_WD] == '2')
				create_2d_sprite(i, j);
			j = j + TILE_SIZE;
			MAP_HT++;
		}
		i = i + TILE_SIZE;
		MAP_WD++;
	}
}