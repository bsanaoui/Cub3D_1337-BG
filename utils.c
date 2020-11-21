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

#include "Cub3D.h"

int 	finalize(void *s)
{
	s = NULL;
	mlx_destroy_image(mlx.ptr, player_img.img);
	mlx_destroy_window(mlx.ptr, mlx.win);
	free(rays);
	free(sprites);
	free(m.map);
	exit(EXIT_SUCCESS);
	return (0);
}

int		ft_perror(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
	return (0);
}

float	normalizeAngle(float angle)
{
	float new_angle;

	new_angle = fmod(angle,(2 * M_PI));
	if(new_angle < 0)
		new_angle += (2 * M_PI);
	return (new_angle);
}

int		hasWallAt(int x, int y)
{
	int	index_x;
	int	index_y;

	index_x = x / TILE_SIZE;
	index_y = y / TILE_SIZE;

	if (index_y < m.h && index_x < m.w)
	{
		if (m.map[index_y][index_x] == '1')
			return (1);
		else if (m.map[index_y][index_x] == '2')
			return (2);
	}	
	return (0);
}

float	distance(float x1, float y1, float x2, float y2)
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
			put_pixel_in_img(project_3d, tab[0] + j, tab[1] + i, color);
			j++;
		}
		i++;
	}
}

static 	int 	get_color_text(int k, int j, float h, int offset_x)
{
	if (k == 0)
		if(((offset_x * text_we.w / TILE_SIZE) + (text_we.w * j * text_we.h / h)) < (text_we.h * text_we.w))
					return(text_we.data[(offset_x * (text_we.w/ TILE_SIZE) + (text_we.w * (int)(j * text_we.h / h)))]);
	if (k == 1)
		if((offset_x * text_ea.w / TILE_SIZE) + (text_ea.w * j * text_ea.h / h) < (text_ea.h * text_ea.w))
					return(text_ea.data[(offset_x * (text_ea.w/ TILE_SIZE) + (text_ea.w * (int)(j * text_ea.h / h)))]);
	if (k == 2)
		if((offset_x * text_so.w / TILE_SIZE) + (text_so.w * j * text_ea.h / h) < (text_so.h * text_so.w))
					return(text_so.data[(offset_x * (text_so.w/ TILE_SIZE) + (text_so.w * (int)(j * text_so.h / h)))]);
	if (k == 3)
		if((offset_x * text_no.w / TILE_SIZE) + (text_no.w * j * text_no.h / h) < (text_no.h * text_no.w))
					return(text_no.data[(offset_x * (text_no.w/ TILE_SIZE) + (text_no.w * (int)(j * text_no.h / h)))]);
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
				if (rays[n_ray].was_hit_vertical && rays[n_ray].isRayFacingLeft)
					k = 0;
				else if (rays[n_ray].was_hit_vertical && rays[n_ray].isRayFacingRight)
					k = 1;
				else if (!rays[n_ray].was_hit_vertical && rays[n_ray].isRayFacingDown)
					k = 2;
				else if (!rays[n_ray].was_hit_vertical && rays[n_ray].isRayFacingUp)
					k = 3;
				put_pixel_in_img(project_3d, tab[0] + i, tab[1] + j, get_color_text(k, j, tab[3], offset_x));
			j++;
		}
		i++;
	}
}