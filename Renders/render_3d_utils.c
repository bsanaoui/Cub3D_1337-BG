/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:46:27 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/12/04 20:59:40 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			create_strip_height(float tab[], int color)
{
	int j;

	j = -1;
	while (++j < tab[2])
		put_pixel_in_img(g_img_3d, tab[0], tab[1] + j, color);
}

static	double	get_color_text(int k, int j, float h, int offset_x)
{
	if (k == 0 && (offset_x * g_text_we.w / g_tile) + (g_text_we.w * j *
		g_text_we.h / h) < (g_text_we.h * g_text_we.w))
		return (g_text_we.data[(offset_x * (g_text_we.w / g_tile) +
					(g_text_we.w * (int)(j * g_text_we.h / h)))]);
	else if (k == 1 && (offset_x * g_text_ea.w / g_tile) + (g_text_ea.w * j *
				g_text_ea.h / h) < (g_text_ea.h * g_text_ea.w))
		return (g_text_ea.data[(offset_x * (g_text_ea.w / g_tile) +
					(g_text_ea.w * (int)(j * g_text_ea.h / h)))]);
	else if (k == 2 && (offset_x * g_text_so.w / g_tile) + (g_text_so.w * j *
				g_text_ea.h / h) < (g_text_so.h * g_text_so.w))
		return (g_text_so.data[(offset_x * (g_text_so.w / g_tile) +
					(g_text_so.w * (int)(j * g_text_so.h / h)))]);
	else if (k == 3 && (offset_x * g_text_no.w / g_tile) + (g_text_no.w * j *
				g_text_no.h / h) < (g_text_no.h * g_text_no.w))
		return (g_text_no.data[(offset_x * (g_text_no.w / g_tile) +
					(g_text_no.w * (int)(j / h * g_text_no.h)))]);
	else
		return (0);
}

void			create_strip_wall(float tab[], int offset_x, int n_ray)
{
	int		j;
	int		k;
	float	h;

	h = tab[2];
	tab[1] = tab[1] < 0 ? 0 : tab[1];
	tab[2] = tab[2] + tab[1] > g_cub.h ? g_cub.h - tab[1] : tab[2];
	j = -1;
	while (++j < tab[2])
	{
		if (g_rays[n_ray].was_hit_vertical && g_rays[n_ray].is_left)
			k = 1;
		else if (g_rays[n_ray].was_hit_vertical && g_rays[n_ray].is_right)
			k = 0;
		else if (!g_rays[n_ray].was_hit_vertical && g_rays[n_ray].is_down)
			k = 3;
		else if (!g_rays[n_ray].was_hit_vertical && g_rays[n_ray].is_up)
			k = 2;
		put_pixel_in_img(g_img_3d, tab[0], tab[1] + j,
			get_color_text(k, tab[1] + j + h / 2 - g_cub.h / 2, h, offset_x));
	}
}

void			create_strip_sprite(float tab[], int num_sp)
{
	int		j;
	int		i;
	float	scale_x;
	float	scale_y;
	double	text_color;

	i = -1;
	scale_x = g_text_sp.w / tab[2];
	scale_y = g_text_sp.h / tab[3];
	text_color = 0;
	while (++i < tab[2])
	{
		if ((tab[0] + i) < g_nb_ray - 1 && (tab[0] + i) >= 0)
			if (g_rays[(int)tab[0] + i].dist < g_sprites[num_sp].dist)
				continue ;
		j = -1;
		while (++j < tab[3])
		{
			text_color = g_text_sp.data[(int)(scale_x * i) +
				(((int)((float)(scale_y * j)) * g_text_sp.size_line / 4))];
			if (text_color != 0x980088)
				put_pixel_in_img(g_img_3d, tab[0] + i, tab[1] + j, text_color);
		}
	}
}
