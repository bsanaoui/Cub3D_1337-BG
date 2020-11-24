/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:55:45 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/09 17:55:46 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static T_CAST	calculate_steps(T_CAST cast, T_RAY ray)
{
	/* **************** Find x closet vertical grid intersection *************** */
	cast.xinterept = floor(player.x / g_tile) * g_tile;
	cast.xinterept += (ray.isRayFacingRight ? g_tile : 0);
	/* **************** Find x closet vertical grid intersection *************** */
	cast.yinterept = player.y + (((-cast.xinterept + player.x) * tan(-ray.rayAngle)));
	/* **************** calculate the increment xstep and ystep ****************** */
	cast.xstep = g_tile;
	cast.xstep *= ray.isRayFacingLeft ? -1 : 1;
	cast.ystep = cast.xstep * tan(-ray.rayAngle);

	cast.nextTouchX = cast.xinterept;
	cast.nextTouchY = cast.yinterept;
	if (ray.isRayFacingLeft)
		cast.minusX = 1;
	else
		cast.minusX = 0;

	return (cast);
}

static T_CAST	increment_steps(T_CAST cast)
{
	while (cast.nextTouchX >= 0 && cast.nextTouchX <= mlx.WIN_W
		&& cast.nextTouchY >= 0 && cast.nextTouchY <= mlx.WIN_H)
	{
		//sprites
		if (hasWallAt(cast.nextTouchX - cast.minusX, cast.nextTouchY) == 1)
		{
			cast.foundVertWallHit = 1;
			cast.wallHitX = cast.nextTouchX;
			cast.wallHitY = cast.nextTouchY;
			break ;
		}
		if (hasWallAt(cast.nextTouchX - cast.minusX, cast.nextTouchY) == 2)
		{
			cast.i_sp++;
			cast.sprite[cast.i_sp].hit_vert = 1;
			cast.sprite[cast.i_sp].index_x = (cast.nextTouchX - cast.minusX)  / g_tile ; 
			cast.sprite[cast.i_sp].index_y = cast.nextTouchY / g_tile;
			cast.sprite[cast.i_sp].hit_x = (cast.sprite[cast.i_sp].index_x * g_tile) + (g_tile / 2);
			cast.sprite[cast.i_sp].hit_y = (cast.sprite[cast.i_sp].index_y * g_tile) + (g_tile / 2);
			//distance to center
		}
		cast.nextTouchX += cast.xstep;
		cast.nextTouchY -= cast.ystep;
	}
	if (!cast.foundVertWallHit)
	{
		cast.wallHitX = player.x;
		cast.wallHitY = player.y;
	}
	return (cast);
}

T_CAST	vertical_intersections(T_RAY ray)
{
	/* ************************************************************************** */
	/*                         VERTICAL INTERSECTION                              */
	/* ************************************************************************** */
	T_CAST 	cast;
	int		i;

	//sprite
	cast.sprite = (T_SPRITE_CAST *)(malloc(g_n_sp * 2 * sizeof(T_SPRITE_CAST *)));
	cast.i_sp = -1;

	cast.foundVertWallHit = 0;
	i = 0;
	// /* **************** Find x closet vertical grid intersection *************** */
	// /* **************** calculate the increment xstep and ystep ****************** */
	cast = calculate_steps(cast, ray);
	// Increment by xstep and ystep until we find a wall;
	cast = increment_steps(cast);
	/* ******************   Calculate distance **************************** */
	cast.distance = (cast.foundVertWallHit) 
	? distance(player.x, player.y, cast.wallHitX, cast.wallHitY)
	: WINT_MAX;
	// sprite
	while (i < cast.i_sp + 1)
	{
		cast.sprite[i].distance = (cast.sprite[i].hit_vert)
		? distance(player.x, player.y, cast.sprite[i].hit_x, cast.sprite[i].hit_y)
		: WINT_MAX;
		i++;
	}
	return(cast);
}