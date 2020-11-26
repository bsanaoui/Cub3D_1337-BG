/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mini_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:08:42 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/15 15:08:44 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_rays(void)
{
	int i;

	i = 0;
	while (i < g_nb_ray)
	{
		line(g_player.x * MAP_SC, g_player.y * MAP_SC,
			g_rays[i].wall_hit.x * MAP_SC, g_rays[i].wall_hit.y * MAP_SC);
		i++;
	}
}

void	render_mini_map(void)
{
	g_map_img.img = mlx_new_image(g_cub.ptr, g_cub.w * MAP_SC,
			g_cub.h * MAP_SC);
	create_2d_map();
	create_rays();
	mlx_put_image_to_window(g_cub.ptr, g_cub.win, g_map_img.img, 0, 0);
	display_player();
	mlx_destroy_image(g_cub.ptr, g_map_img.img);
}
