/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mini_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:08:42 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/15 15:08:44 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_mini_map()
{
	map_img.img = mlx_new_image(mlx.ptr, mlx.WIN_W * MAP_SC, mlx.WIN_H * MAP_SC);
	create_2d_map();//map
	create_rays(); //rays
	mlx_put_image_to_window(mlx.ptr, mlx.win, map_img.img, 0, 0); //rays and map
	display_player();
	mlx_destroy_image(mlx.ptr, map_img.img);
}