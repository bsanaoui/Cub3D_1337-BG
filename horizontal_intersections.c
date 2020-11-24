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

static t_cast	calculate_steps(t_cast cast, t_ray ray)
{
	/* **************** Find y closet horizontal grid intersection *************** */
	cast.yinterept = floor(g_player.y / g_tile) * g_tile;
	cast.yinterept += (ray.is_down ? g_tile : 0);
	/* **************** Find x closet horizontal grid intersection *************** */
	cast.xinterept = g_player.x + (((-cast.yinterept + g_player.y) / tan(-ray.angle)));
	/* **************** calculate the increment xstep and ystep ****************** */
	cast.ystep = g_tile;
	cast.ystep *= ray.is_up ? -1 : 1;
	cast.xstep = cast.ystep / tan(-ray.angle);

	cast.next_touch_x = cast.xinterept;
	cast.next_touch_y = cast.yinterept;
	if (ray.is_up)
		cast.minus_y = 1;
	else
		cast.minus_y = 0;
	return (cast);
}

static t_cast	increment_steps(t_cast cast)
{
	while (cast.next_touch_x >= 0 && cast.next_touch_x <= g_cub.w
		&& cast.next_touch_y >= 0 && cast.next_touch_y <= g_cub.h)
	{
		//sprite
		if (has_wall(cast.next_touch_x, cast.next_touch_y - cast.minus_y) == 1)
		{
			cast.found_horz_wall = 1;
			cast.wall_hit_x = cast.next_touch_x;
			cast.wall_hit_y = cast.next_touch_y;
			break ;
		}
		if (has_wall(cast.next_touch_x, cast.next_touch_y - cast.minus_y) == 2)
		{
			cast.i_sp++;
			cast.sprite[cast.i_sp].hit_horz = 1;
			cast.sprite[cast.i_sp].index_x = cast.next_touch_x / g_tile;
			cast.sprite[cast.i_sp].index_y = (cast.next_touch_y - cast.minus_y) / g_tile;
			cast.sprite[cast.i_sp].hit_x = (cast.sprite[cast.i_sp].index_x * g_tile) + (g_tile / 2);
			cast.sprite[cast.i_sp].hit_y = (cast.sprite[cast.i_sp].index_y * g_tile) + (g_tile / 2);
			//dist to center
		}
		cast.next_touch_x -= cast.xstep;
		cast.next_touch_y += cast.ystep;
	}
	if (!cast.found_horz_wall)
	{
		cast.wall_hit_x = g_player.x;
		cast.wall_hit_y = g_player.y;
	}
	return (cast);
}

t_cast	horizontal_intersections(t_ray ray)
{
	/* ************************************************************************** */
	/*                         HORIZONTAL INTERSECTION                            */
	/* ************************************************************************** */
	t_cast 	cast;
	int		i;

	//sprite
	cast.sprite = (t_sp_cast *)(malloc(g_n_sp * 2 * sizeof(t_sp_cast *)));
	cast.i_sp = -1;
	cast.found_horz_wall = 0;
	i = 0;
	// /* **************** calculate the increment xstep and ystep ****************** */
	cast = calculate_steps(cast, ray);
	//Increment by xstep and ystep until we find a wall;
	cast = increment_steps(cast);
	/* ******************   Calculate dist **************************** */
	cast.dist = (cast.found_horz_wall) 
	? dist(g_player.x, g_player.y, cast.wall_hit_x, cast.wall_hit_y)
	: WINT_MAX;

	// sprite
	while (i < cast.i_sp + 1)
	{
		cast.sprite[i].dist = (cast.sprite[i].hit_horz)
		? dist(g_player.x, g_player.y, cast.sprite[i].hit_x, cast.sprite[i].hit_y)
		: WINT_MAX;
		i++;
	}
	return(cast);
}