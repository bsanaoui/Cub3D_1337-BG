/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:05:26 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/04 21:05:28 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray 		direction_ray(float angle, int n_ray)
{
	t_ray		ray;

	ray.angle = angle;
	ray.is_down = ray.angle > 0 && ray.angle < M_PI;
	ray.is_up = !ray.is_down;
	ray.is_right = ray.angle >= (M_PI * 3 / 2) || ray.angle <= (M_PI / 2);
	ray.is_left = !ray.is_right;

	g_rays[n_ray].angle = angle;
	g_rays[n_ray].is_down = ray.angle > 0 && ray.angle < M_PI;
	g_rays[n_ray].is_up = !ray.is_down;
	g_rays[n_ray].is_right = ray.angle >= (M_PI * 3 / 2) || ray.angle <= (M_PI / 2);
	g_rays[n_ray].is_left = !ray.is_right;
	return(ray);
}

void		ray()
{
	int			i;

	g_rays[0].angle = normalize_angle(g_player.angle - (g_player.fov / 2));
	cast_ray(direction_ray(g_rays[0].angle, 0), 0);
	i = 1;
	while (i < g_nb_ray)
	{
		g_rays[i].angle = normalize_angle(g_rays[i - 1].angle + (g_player.fov / g_nb_ray));
		cast_ray(direction_ray(g_rays[i].angle, i), i);
		i++;
	}

	// **** Affichage g_sprites **** //
	// int  k = 0;
	// if (g_index_sp == 0)
	// 	printf("No g_sprites\n");
	// printf("******** Number of sprtites : << %d >>********\n",g_index_sp);
	// while (k < g_index_sp)
    // {
    //     printf("sprtie << %d >>  {%d, %d} || Num Array = %d || angle_sp = %f\n",k + 1, g_sprites[k].index_x,g_sprites[k].index_y, g_sprites[k].num_ray, g_sprites[k].angle * 180 / M_PI);
	// 	k++;
    // }
	// printf("*******************************\n");
	//	*************************** //
}

void	get_sprites(t_cast vert, t_cast horz, float dist_wall)
{
	int			i;
	// check g_sprites in one ray
	i = 0;
	while (i < (vert.i_sp + 1))
	{
		if (vert.sprite[i].dist < dist_wall)
			get_sprite_data(vert.sprite[i]);
		i++;
	}
	i = 0;
	while (i < (horz.i_sp + 1))
	{
		if (horz.sprite[i].dist < dist_wall)
			get_sprite_data(horz.sprite[i]);
		i++;
	}
}

void	cast_ray(t_ray ray, int ray_count)
{
	t_cast		vertInter;
	t_cast		horzInter;

	vertInter = vertical_intersections(ray);
	horzInter = horizontal_intersections(ray);
	/* *************  smallest dist between the g_player and hitWall ********** */
	g_rays[ray_count].wall_hit.x = ((horzInter.found_horz_wall && (horzInter.dist < vertInter.dist))) ? horzInter.wall_hit_x : vertInter.wall_hit_x;
	g_rays[ray_count].wall_hit.y = ((horzInter.found_horz_wall && (horzInter.dist < vertInter.dist))) ? horzInter.wall_hit_y : vertInter.wall_hit_y;
	g_rays[ray_count].dist = (horzInter.dist < vertInter.dist) ? horzInter.dist : vertInter.dist;

	// get g_sprites from one ray
	if ((vertInter.i_sp  >= 0) || (horzInter.i_sp  >= 0))
		get_sprites(vertInter, horzInter, g_rays[ray_count].dist);
	/////// check  hor or vert
	if (vertInter.dist < horzInter.dist)
		g_rays[ray_count].was_hit_vertical = 1;
	else
		g_rays[ray_count].was_hit_vertical = 0;

	if (vertInter.sprite && horzInter.sprite)
	{
		free(vertInter.sprite);
		free(horzInter.sprite);
	}
}

void	create_rays()
{
	int i;

	i = 0;
	while (i < g_nb_ray)
	{
		line(g_player.x * MAP_SC, g_player.y * MAP_SC, g_rays[i].wall_hit.x * MAP_SC, g_rays[i].wall_hit.y * MAP_SC);
		i++;
	}
}

void    clear_rays()
{
    if (g_rays)
    {
         free(g_rays);
         g_rays = NULL;
    }
}