/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:55:45 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/25 20:48:36 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_cast	calculate_steps(t_cast cast, t_ray ray)
{
	cast.xinterept = floor(g_player.x / g_tile) * g_tile;
	cast.xinterept += (ray.is_right ? g_tile : 0);
	cast.yinterept = g_player.y + ((-cast.xinterept + g_player.x)
		* tan(-ray.angle));
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

static	void	add_tmp_sprite(t_cast *cast, double hit_x, double hit_y)
{
	cast->i_sp++;
	cast->sprite[cast->i_sp].hit_vert = 1;
	cast->sprite[cast->i_sp].index_x = hit_x / g_tile;
	cast->sprite[cast->i_sp].index_y = hit_y / g_tile;
	cast->sprite[cast->i_sp].hit_x =
		(cast->sprite[cast->i_sp].index_x * g_tile) + (g_tile / 2);
	cast->sprite[cast->i_sp].hit_y =
		(cast->sprite[cast->i_sp].index_y * g_tile) + (g_tile / 2);
}

static t_cast	increment_steps(t_cast cast)
{
	while (cast.next_touch_x >= 0 && cast.next_touch_x <= g_tile * g_m.w
			&& cast.next_touch_y >= 0 && cast.next_touch_y <= g_tile * g_m.h)
	{
		if (has_wall(cast.next_touch_x - cast.minus_x, cast.next_touch_y) == 1)
		{
			cast.found_vert_wall = 1;
			cast.wall_hit_x = cast.next_touch_x;
			cast.wall_hit_y = cast.next_touch_y;
			break ;
		}
		if (has_wall(cast.next_touch_x - cast.minus_x, cast.next_touch_y) == 2)
			add_tmp_sprite(&cast, cast.next_touch_x - cast.minus_x,
				cast.next_touch_y);
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

t_cast			vertical_intersections(t_ray ray)
{
	t_cast	cast;
	int		i;

	i = g_n_sp * 2;
	cast.sprite = (t_sp_cast *)(malloc(i * sizeof(t_sp_cast *)));
	cast.i_sp = -1;
	cast.found_vert_wall = 0;
	i = 0;
	cast = calculate_steps(cast, ray);
	cast = increment_steps(cast);
	cast.dist = (cast.found_vert_wall)
		? dist(g_player.x, g_player.y, cast.wall_hit_x, cast.wall_hit_y)
		: WINT_MAX;
	while (i < cast.i_sp + 1)
	{
		cast.sprite[i].dist = (cast.sprite[i].hit_vert)
			? dist(g_player.x, g_player.y, cast.sprite[i].hit_x,
					cast.sprite[i].hit_y)
			: WINT_MAX;
		i++;
	}
	return (cast);
}
