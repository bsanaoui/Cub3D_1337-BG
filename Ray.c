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

static T_RAY 		direction_ray(float rayAngle, int n_ray)
{
	T_RAY		ray;

	ray.rayAngle = rayAngle;
	ray.isRayFacingDown = ray.rayAngle > 0 && ray.rayAngle < M_PI;
	ray.isRayFacingUp = !ray.isRayFacingDown;
	ray.isRayFacingRight = ray.rayAngle >= (M_PI * 3 / 2) || ray.rayAngle <= (M_PI / 2);
	ray.isRayFacingLeft = !ray.isRayFacingRight;

	rays[n_ray].rayAngle = rayAngle;
	rays[n_ray].isRayFacingDown = ray.rayAngle > 0 && ray.rayAngle < M_PI;
	rays[n_ray].isRayFacingUp = !ray.isRayFacingDown;
	rays[n_ray].isRayFacingRight = ray.rayAngle >= (M_PI * 3 / 2) || ray.rayAngle <= (M_PI / 2);
	rays[n_ray].isRayFacingLeft = !ray.isRayFacingRight;
	return(ray);
}

void		ray()
{
	int			i;

	rays[0].rayAngle = normalizeAngle(player.Angle - (player.fov / 2));
	cast_ray(direction_ray(rays[0].rayAngle, 0), 0);
	i = 1;
	while (i < n_rays)
	{
		rays[i].rayAngle = normalizeAngle(rays[i - 1].rayAngle + (player.fov / n_rays));
		cast_ray(direction_ray(rays[i].rayAngle, i), i);
		i++;
	}

	// **** Affichage sprites **** //
	// int  k = 0;
	// if (count_sprite == 0)
	// 	printf("No Sprites\n");
	// printf("******** Number of sprtites : << %d >>********\n",count_sprite);
	// while (k < count_sprite)
    // {
    //     printf("sprtie << %d >>  {%d, %d} || Num Array = %d || angle_sp = %f\n",k + 1, sprites[k].index_x,sprites[k].index_y, sprites[k].num_ray, sprites[k].angle * 180 / M_PI);
	// 	k++;
    // }
	// printf("*******************************\n");
	//	*************************** //
}

void	get_sprites(T_CAST vert, T_CAST horz, float dist_wall)
{
	int			i;
	// check sprites in one ray
	i = 0;
	while (i < (vert.i_sp + 1))
	{
		if (vert.sprite[i].distance < dist_wall)
			get_sprite_data(vert.sprite[i]);
		i++;
	}
	i = 0;
	while (i < (horz.i_sp + 1))
	{
		if (horz.sprite[i].distance < dist_wall)
			get_sprite_data(horz.sprite[i]);
		i++;
	}
}

void	cast_ray(T_RAY ray, int ray_count)
{
	T_CAST		vertInter;
	T_CAST		horzInter;

	vertInter = vertical_intersections(ray);
	horzInter = horizontal_intersections(ray);
	/* *************  smallest distance between the player and hitWall ********** */
	rays[ray_count].wallHit.X = ((horzInter.foundHorzWallHit && (horzInter.distance < vertInter.distance))) ? horzInter.wallHitX : vertInter.wallHitX;
	rays[ray_count].wallHit.Y = ((horzInter.foundHorzWallHit && (horzInter.distance < vertInter.distance))) ? horzInter.wallHitY : vertInter.wallHitY;
	rays[ray_count].distance = (horzInter.distance < vertInter.distance) ? horzInter.distance : vertInter.distance;

	// get sprites from one ray
	if ((vertInter.i_sp  >= 0) || (horzInter.i_sp  >= 0))
		get_sprites(vertInter, horzInter, rays[ray_count].distance);
	/////// check  hor or vert
	if (vertInter.distance < horzInter.distance)
		rays[ray_count].was_hit_vertical = 1;
	else
		rays[ray_count].was_hit_vertical = 0;

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
	while (i < n_rays)
	{
		line(player.x * MAP_SC, player.y * MAP_SC, rays[i].wallHit.X * MAP_SC, rays[i].wallHit.Y * MAP_SC);
		i++;
	}
}

void    clear_rays()
{
    if (rays)
    {
         free(rays);
         rays = NULL;
    }
}