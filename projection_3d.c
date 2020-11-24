/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projected_wall_3d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 22:18:22 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/09 22:18:24 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float		get_offset_x(int ray_n)
{
	if (g_rays[ray_n].was_hit_vertical)
		return ((int)g_rays[ray_n].wall_hit.y % (int)g_tile);
	return ((int)g_rays[ray_n].wall_hit.x % (int)g_tile);
}

void			render3d()
{
	int		i;
	float	wallStripHeight;
	float	correctWallDistance;
	float	distanceProjectionPlane;

	g_img_3d.img = mlx_new_image(g_cub.ptr, g_cub.w , g_cub.h); 
	distanceProjectionPlane = (g_cub.w / 2) / tan(g_player.fov / 2); 
	i = 0;
	while(i < g_nb_ray)
	{
		correctWallDistance = g_rays[i].dist * cos(g_rays[i].angle - g_player.angle);
		wallStripHeight = (g_tile / correctWallDistance) * distanceProjectionPlane;
		create_strip_wall((float[]){i * g_wall_strip_w, (g_cub.h / 2) - (wallStripHeight / 2), g_wall_strip_w, wallStripHeight}, get_offset_x(i), i);
		create_strip_height((float[]){i * g_wall_strip_w, 0, g_wall_strip_w, (g_cub.h - wallStripHeight) / 2 }, g_ceil_color);
		create_strip_height((float[]){i * g_wall_strip_w, wallStripHeight  + ((g_cub.h - wallStripHeight) / 2), g_wall_strip_w, (g_cub.h - wallStripHeight) / 2}, g_floor_color);
		i++;
	}
	render_sprites(); /////////// SPRITE RENDRINNG
	mlx_put_image_to_window(g_cub.ptr, g_cub.win, g_img_3d.img, 0, 0);
	mlx_destroy_image(g_cub.ptr, g_img_3d.img);
}