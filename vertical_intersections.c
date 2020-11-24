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

static t_cast	calculate_steps(t_cast cast, t_ray ray)
{
	/* **************** Find x closet vertical grid intersection *************** */
	cast.xinterept = floor(g_player.x / g_tile) * g_tile;
	cast.xinterept += (ray.is_right ? g_tile : 0);
	/* **************** Find x closet vertical grid intersection *************** */
	cast.yinterept = g_player.y + (((-cast.xinterept + g_player.x) * tan(-ray.angle)));
	/* **************** calculate the increment xstep and ystep ****************** */
	cast.xstep = g_tile;
	cast.xstep *= ray.is_left ? -1 : 1;
	cast.ystep = cast.xstep * tan(-ray.angle);

	cast.next_touch_x = cast.xinterept;
	cast.next_touch_y = cast.yinterept;
	if (ray.is_left)
		cast.minus_x = 1;
	else
		cast.minus_x = 0;

	return (cast);
}

static t_cast	increment_steps(t_cast cast)
{
	while (cast.next_touch_x >= 0 && cast.next_touch_x <= g_cub.w
		&& cast.next_touch_y >= 0 && cast.next_touch_y <= g_cub.h)
	{
		//g_sprites
		if (has_wall(cast.next_touch_x - cast.minus_x, cast.next_touch_y) == 1)
		{
			cast.found_vert_wall = 1;
			cast.wall_hit_x = cast.next_touch_x;
			cast.wall_hit_y = cast.next_touch_y;
			break ;
		}
		if (has_wall(cast.next_touch_x - cast.minus_x, cast.next_touch_y) == 2)
		{
			cast.i_sp++;
			cast.sprite[cast.i_sp].hit_vert = 1;
			cast.sprite[cast.i_sp].index_x = (cast.next_touch_x - cast.minus_x)  / g_tile ; 
			cast.sprite[cast.i_sp].index_y = cast.next_touch_y / g_tile;
			cast.sprite[cast.i_sp].hit_x = (cast.sprite[cast.i_sp].index_x * g_tile) + (g_tile / 2);
			cast.sprite[cast.i_sp].hit_y = (cast.sprite[cast.i_sp].index_y * g_tile) + (g_tile / 2);
			//dist to center
		}
		cast.next_touch_x += cast.xstep;
		cast.next_touch_y -= cast.ystep;
	}
	if (!cast.found_vert_wall)
	{
		cast.wall_hit_x = g_player.x;
		cast.wall_hit_y = g_player.y;
	}
	return (cast);
}

t_cast	vertical_intersections(t_ray ray)
{
	/* ************************************************************************** */
	/*                         VERTICAL INTERSECTION                              */
	/* ************************************************************************** */
	t_cast 	cast;
	int		i;

	//sprite
	cast.sprite = (t_sp_cast *)(malloc(g_n_sp * 2 * sizeof(t_sp_cast *)));
	cast.i_sp = -1;

	cast.found_vert_wall = 0;
	i = 0;
	// /* **************** Find x closet vertical grid intersection *************** */
	// /* **************** calculate the increment xstep and ystep ****************** */
	cast = calculate_steps(cast, ray);
	// Increment by xstep and ystep until we find a wall;
	cast = increment_steps(cast);
	/* ******************   Calculate dist **************************** */
	cast.dist = (cast.found_vert_wall) 
	? dist(g_player.x, g_player.y, cast.wall_hit_x, cast.wall_hit_y)
	: WINT_MAX;
	// sprite
	while (i < cast.i_sp + 1)
	{
		cast.sprite[i].dist = (cast.sprite[i].hit_vert)
		? dist(g_player.x, g_player.y, cast.sprite[i].hit_x, cast.sprite[i].hit_y)
		: WINT_MAX;
		i++;
	}
	return(cast);
}