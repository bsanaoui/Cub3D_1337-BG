/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:04:15 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/26 12:04:16 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	t_ray	direction_ray(float angle, int n_ray)
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
	g_rays[n_ray].is_right = ray.angle >= (M_PI * 3 / 2) ||
		ray.angle <= (M_PI / 2);
	g_rays[n_ray].is_left = !ray.is_right;
	return (ray);
}

static	void	get_sprites(t_cast vert, t_cast horz, float dist_wall)
{
	int			i;

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

static	void	cast_ray(t_ray ray, int ray_count)
{
	t_cast	vert;
	t_cast	horz;

	vert = vertical_intersections(ray);
	horz = horizontal_intersections(ray);
	g_rays[ray_count].wall_hit.x = ((horz.found_horz_wall &&
			(horz.dist < vert.dist))) ? horz.wall_hit_x : vert.wall_hit_x;
	g_rays[ray_count].wall_hit.y = ((horz.found_horz_wall &&
			(horz.dist < vert.dist))) ? horz.wall_hit_y : vert.wall_hit_y;
	g_rays[ray_count].dist = (horz.dist < vert.dist) ? horz.dist : vert.dist;
	if (vert.i_sp >= 0 || horz.i_sp >= 0)
		get_sprites(vert, horz, g_rays[ray_count].dist);
	if (vert.dist < horz.dist)
		g_rays[ray_count].was_hit_vertical = 1;
	else
		g_rays[ray_count].was_hit_vertical = 0;
	if (vert.sprite && horz.sprite)
	{
		free(vert.sprite);
		free(horz.sprite);
	}
}

void			ray(void)
{
	int	i;

	g_rays[0].angle = normalize_angle(g_player.angle - (g_player.fov / 2));
	cast_ray(direction_ray(g_rays[0].angle, 0), 0);
	i = 1;
	while (i < g_nb_ray)
	{
		g_rays[i].angle = normalize_angle(g_rays[i - 1].angle +
			(g_player.fov / g_nb_ray));
		cast_ray(direction_ray(g_rays[i].angle, i), i);
		i++;
	}
}

void			clear_rays(void)
{
	if (g_rays)
	{
		free(g_rays);
		g_rays = NULL;
	}
}
