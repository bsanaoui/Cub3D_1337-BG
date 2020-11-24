/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_in_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:06:26 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/06 14:06:27 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_in_img(t_img s_img, int x, int y, int color)
{
	int 	bits_per_pixel;
	int 	size_line;
	int 	endian;

	if (x >= 0 && x < mlx.WIN_W &&  x < s_img.w && y >= 0 && y < mlx.WIN_H && y < s_img.h)
	{
		s_img.data  = (int *)mlx_get_data_addr(s_img.img, &bits_per_pixel, &size_line, &endian);
  		s_img.data[x + y * size_line / 4] = color;
	}
}