/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:26:01 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/26 13:26:03 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int		in_array_sprites(int p_x, int p_y)
{
	int i;

	i = 0;
	while (i < g_index_sp)
	{
		if (g_sprites[i].index_x == p_x && g_sprites[i].index_y == p_y)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static	void	get_ray_hit_sp(float s_x, float s_y, int i_sp)
{
	double		alpha;
	t_vector	v_ray1;
	t_vector	v_sp;

	v_ray1.x = g_rays[0].wall_hit.x - g_player.x;
	v_ray1.y = g_rays[0].wall_hit.y - g_player.y;
	v_sp.x = s_x - g_player.x;
	v_sp.y = s_y - g_player.y;
	alpha = -atan2(v_ray1.y, v_ray1.x) + atan2(v_sp.y, v_sp.x);
	if (alpha > M_PI)
		alpha -= M_PI * 2;
	else if (alpha < -M_PI)
		alpha += M_PI * 2;
	g_sprites[i_sp].num_ray = (g_nb_ray / g_player.fov) * alpha;
}

void			get_sprite_data(t_sp_cast tmp_sp)
{
	if (!in_array_sprites(tmp_sp.index_x, tmp_sp.index_y))
	{
		g_sprites[g_index_sp].x = tmp_sp.hit_x;
		g_sprites[g_index_sp].y = tmp_sp.hit_y;
		g_sprites[g_index_sp].index_x = tmp_sp.index_x;
		g_sprites[g_index_sp].index_y = tmp_sp.index_y;
		g_sprites[g_index_sp].dist = tmp_sp.dist;
		get_ray_hit_sp(g_sprites[g_index_sp].x, g_sprites[g_index_sp].y,
			g_index_sp);
		g_sprites[g_index_sp].angle = normalize_angle(g_player.angle -
				g_player.fov / 2) + (g_sprites[g_index_sp].num_ray *
				(g_player.fov / g_nb_ray));
		g_index_sp++;
	}
}

void			sort_sprites(void)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < (g_index_sp - 1))
	{
		j = 0;
		while (j < (g_index_sp - i - 1))
		{
			if (g_sprites[j].dist < g_sprites[j + 1].dist)
			{
				tmp = g_sprites[j];
				g_sprites[j] = g_sprites[j + 1];
				g_sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void			clear_sprites(void)
{
	int n_sp;

	n_sp = g_n_sp;
	if (g_sprites)
	{
		free(g_sprites);
		g_sprites = NULL;
	}
	g_index_sp = 0;
	g_sprites = (t_sprite *)(malloc(n_sp * sizeof(t_sprite)));
}
