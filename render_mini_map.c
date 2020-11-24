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
	g_map_img.img = mlx_new_image(g_cub.ptr, g_cub.w * MAP_SC, g_cub.h * MAP_SC);
	create_2d_map();//map
	create_rays(); //g_rays
	mlx_put_image_to_window(g_cub.ptr, g_cub.win, g_map_img.img, 0, 0); //g_rays and map
	display_player();
	mlx_destroy_image(g_cub.ptr, g_map_img.img);
}