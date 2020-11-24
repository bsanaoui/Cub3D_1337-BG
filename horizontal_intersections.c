/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:55:18 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/09 17:55:20 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static T_CAST	calculate_steps(T_CAST cast, T_RAY ray)
{
	/* **************** Find y closet horizontal grid intersection *************** */
	cast.yinterept = floor(player.y / g_tile) * g_tile;
	cast.yinterept += (ray.isRayFacingDown ? g_tile : 0);
	/* **************** Find x closet horizontal grid intersection *************** */
	cast.xinterept = player.x + (((-cast.yinterept + player.y) / tan(-ray.rayAngle)));
	/* **************** calculate the increment xstep and ystep ****************** */
	cast.ystep = g_tile;
	cast.ystep *= ray.isRayFacingUp ? -1 : 1;
	cast.xstep = cast.ystep / tan(-ray.rayAngle);

	cast.nextTouchX = cast.xinterept;
	cast.nextTouchY = cast.yinterept;
	if (ray.isRayFacingUp)
		cast.minusY = 1;
	else
		cast.minusY = 0;
	return (cast);
}

static T_CAST	increment_steps(T_CAST cast)
{
	while (cast.nextTouchX >= 0 && cast.nextTouchX <= mlx.WIN_W
		&& cast.nextTouchY >= 0 && cast.nextTouchY <= mlx.WIN_H)
	{
		//sprite
		if (hasWallAt(cast.nextTouchX, cast.nextTouchY - cast.minusY) == 1)
		{
			cast.foundHorzWallHit = 1;
			cast.wallHitX = cast.nextTouchX;
			cast.wallHitY = cast.nextTouchY;
			break ;
		}
		if (hasWallAt(cast.nextTouchX, cast.nextTouchY - cast.minusY) == 2)
		{
			cast.i_sp++;
			cast.sprite[cast.i_sp].hit_horz = 1;
			cast.sprite[cast.i_sp].index_x = cast.nextTouchX / g_tile;
			cast.sprite[cast.i_sp].index_y = (cast.nextTouchY - cast.minusY) / g_tile;
			cast.sprite[cast.i_sp].hit_x = (cast.sprite[cast.i_sp].index_x * g_tile) + (g_tile / 2);
			cast.sprite[cast.i_sp].hit_y = (cast.sprite[cast.i_sp].index_y * g_tile) + (g_tile / 2);
			//distance to center
		}
		cast.nextTouchX -= cast.xstep;
		cast.nextTouchY += cast.ystep;
	}
	if (!cast.foundHorzWallHit)
	{
		cast.wallHitX = player.x;
		cast.wallHitY = player.y;
	}
	return (cast);
}

T_CAST	horizontal_intersections(T_RAY ray)
{
	/* ************************************************************************** */
	/*                         HORIZONTAL INTERSECTION                            */
	/* ************************************************************************** */
	T_CAST 	cast;
	int		i;

	//sprite
	cast.sprite = (T_SPRITE_CAST *)(malloc(g_n_sp * 2 * sizeof(T_SPRITE_CAST *)));
	cast.i_sp = -1;
	cast.foundHorzWallHit = 0;
	i = 0;
	// /* **************** calculate the increment xstep and ystep ****************** */
	cast = calculate_steps(cast, ray);
	//Increment by xstep and ystep until we find a wall;
	cast = increment_steps(cast);
	/* ******************   Calculate distance **************************** */
	cast.distance = (cast.foundHorzWallHit) 
	? distance(player.x, player.y, cast.wallHitX, cast.wallHitY)
	: WINT_MAX;

	// sprite
	while (i < cast.i_sp + 1)
	{
		cast.sprite[i].distance = (cast.sprite[i].hit_horz)
		? distance(player.x, player.y, cast.sprite[i].hit_x, cast.sprite[i].hit_y)
		: WINT_MAX;
		i++;
	}
	return(cast);
}