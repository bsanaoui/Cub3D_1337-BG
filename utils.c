/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:27:08 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/07 15:27:09 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	finalize(void *s)
{
	s = NULL;
	mlx_destroy_image(g_cub.ptr, g_pl_img.img);
	mlx_destroy_window(g_cub.ptr, g_cub.win);
	free(g_rays);
	free(g_sprites);
	free(g_m.map);
	exit(EXIT_SUCCESS);
	return (0);
}

int		ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

int		ft_perror(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
	return (0);
}

float	normalize_angle(float angle)
{
	float new_angle;

	new_angle = fmod(angle,(2 * M_PI));
	if(new_angle < 0)
		new_angle += (2 * M_PI);
	return (new_angle);
}

int		has_wall(int x, int y)
{
	int	index_x;
	int	index_y;

	index_x = x / g_tile;
	index_y = y / g_tile;

	if (index_y < g_m.h && index_x < g_m.w)
	{
		if (g_m.map[index_y][index_x] == '1')
			return (1);
		else if (g_m.map[index_y][index_x] == '2')
			return (2);
	}	
	return (0);
}

float	dist(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1 ,2) + pow(y2 - y1, 2)));
}

void	create_strip_height(float tab[], int color) // tab[] = {float x, float y, float width, float height}
{
	int j;
	int	i;

	i = 0;
	while(i < tab[3])
	{
		j = 0;
		while(j < tab[2])
		{
			put_pixel_in_img(g_img_3d, tab[0] + j, tab[1] + i, color);
			j++;
		}
		i++;
	}
}

static 	int 	get_color_text(int k, int j, float h, int offset_x)
{
	if (k == 0)
		if(((offset_x * g_text_we.w / g_tile) + (g_text_we.w * j * g_text_we.h / h)) < (g_text_we.h * g_text_we.w))
					return(g_text_we.data[(offset_x * (int)(g_text_we.w/ g_tile) + (g_text_we.w * (int)(j * g_text_we.h / h)))]);
	if (k == 1)
		if((offset_x * g_text_ea.w / g_tile) + (g_text_ea.w * j * g_text_ea.h / h) < (g_text_ea.h * g_text_ea.w))
					return(g_text_ea.data[(offset_x * (int)(g_text_ea.w/ g_tile) + (g_text_ea.w * (int)(j * g_text_ea.h / h)))]);
	if (k == 2)
		if((offset_x * g_text_so.w / g_tile) + (g_text_so.w * j * g_text_ea.h / h) < (g_text_so.h * g_text_so.w))
					return(g_text_so.data[(offset_x * (int)(g_text_so.w/ g_tile) + (g_text_so.w * (int)(j * g_text_so.h / h)))]);
	if (k == 3)
		if((offset_x * g_text_no.w / g_tile) + (g_text_no.w * j * g_text_no.h / h) < (g_text_no.h * g_text_no.w))
					return(g_text_no.data[(offset_x * (int)(g_text_no.w/ g_tile) + (g_text_no.w * (int)(j * g_text_no.h / h)))]);
	return (0);
}

void			create_strip_wall(float tab[], int offset_x, int n_ray) // tab[] = {float x, float y, float width, float height}
{
	int j;
	int	i;
	int k;

	i = 0;
	while(i < tab[2])
	{
		j = 0; 
		while(j < tab[3])
		{
				if (g_rays[n_ray].was_hit_vertical && g_rays[n_ray].is_left)
					k = 0;
				else if (g_rays[n_ray].was_hit_vertical && g_rays[n_ray].is_right)
					k = 1;
				else if (!g_rays[n_ray].was_hit_vertical && g_rays[n_ray].is_down)
					k = 2;
				else if (!g_rays[n_ray].was_hit_vertical && g_rays[n_ray].is_up)
					k = 3;
				put_pixel_in_img(g_img_3d, tab[0] + i, tab[1] + j, get_color_text(k, j, tab[3], offset_x));
			j++;
		}
		i++;
	}
}