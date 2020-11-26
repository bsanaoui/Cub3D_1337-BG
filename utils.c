/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:27:08 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/07 15:27:09 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		finalize(void *s)
{
	s = NULL;
	mlx_destroy_image(g_cub.ptr, g_pl_img.img);
	mlx_destroy_window(g_cub.ptr, g_cub.win);
	free(g_rays);
	free(g_sprites);
	free(g_m.map);
	exit(EXIT_SUCCESS);
	return (0);
}

int		ft_perror(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
	return (0);
}

float	normalize_angle(float angle)
{
	float new_angle;

	new_angle = fmod(angle, (2 * M_PI));
	if (new_angle < 0)
		new_angle += (2 * M_PI);
	return (new_angle);
}

int		has_wall(int x, int y)
{
	int	index_x;
	int	index_y;

	index_x = x / g_tile;
	index_y = y / g_tile;
	if (index_y < g_m.h && index_x < g_m.w)
	{
		if (g_m.map[index_y][index_x] == '1')
			return (1);
		else if (g_m.map[index_y][index_x] == '2')
			return (2);
	}
	return (0);
}

float	dist(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
