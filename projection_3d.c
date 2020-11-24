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
	if (rays[ray_n].was_hit_vertical)
		return ((int)rays[ray_n].wallHit.Y % (int)g_tile);
	return ((int)rays[ray_n].wallHit.X % (int)g_tile);
}

void			render3DProjectedWalls()
{
	int		i;
	float	wallStripHeight;
	float	correctWallDistance;
	float	distanceProjectionPlane;

	project_3d.img = mlx_new_image(mlx.ptr, mlx.WIN_W , mlx.WIN_H); 
	distanceProjectionPlane = (mlx.WIN_W / 2) / tan(player.fov / 2); 
	i = 0;
	while(i < g_nb_ray)
	{
		correctWallDistance = rays[i].distance * cos(rays[i].rayAngle - player.Angle);
		wallStripHeight = (g_tile / correctWallDistance) * distanceProjectionPlane;
		create_strip_wall((float[]){i * g_wall_strip_w, (mlx.WIN_H / 2) - (wallStripHeight / 2), g_wall_strip_w, wallStripHeight}, get_offset_x(i), i);
		create_strip_height((float[]){i * g_wall_strip_w, 0, g_wall_strip_w, (mlx.WIN_H - wallStripHeight) / 2 }, g_ceil_color);
		create_strip_height((float[]){i * g_wall_strip_w, wallStripHeight  + ((mlx.WIN_H - wallStripHeight) / 2), g_wall_strip_w, (mlx.WIN_H - wallStripHeight) / 2}, g_floor_color);
		i++;
	}
	render_sprites(); /////////// SPRITE RENDRINNG
	mlx_put_image_to_window(mlx.ptr, mlx.win, project_3d.img, 0, 0);
	mlx_destroy_image(mlx.ptr, project_3d.img);
}