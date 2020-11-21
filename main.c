/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:29:18 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/12/18 15:49:52 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	InitGame()
{
	mlx.ptr = mlx_init();
	ROTATION_SPEED = (2.0 * (M_PI / 180));
	MOVE_SPEED = 4.2;
	newline = 0;
	reset_elem_conf();
	import_data();
	WALL_COLOR = 0xffffff;
	key_released = 1;
	player.turnDirection = 0;
	player.walkDirection = 0;
	player.fov = 60 * M_PI / 180;
	wall_strip_width = 1;
	count_sprite = 0;
	n_rays = mlx.WIN_W / wall_strip_width;
	rays = (T_RAYS *)(malloc(n_rays * sizeof(T_RAYS)));
	sprites = (T_SPRITE *)(malloc(n_sp * sizeof(T_SPRITE)));
	mlx.win = mlx_new_window(mlx.ptr, mlx.WIN_W , mlx.WIN_H, "CMOS WIN");
}

void	render()
{
	map_img.img = mlx_new_image(mlx.ptr, map_img.w = mlx.WIN_W * MINIMAP_SCALE_FACTOR, map_img.h = mlx.WIN_H * MINIMAP_SCALE_FACTOR); //image of maps
	player_img.img = mlx_new_image(mlx.ptr, player_img.w = TILE_SIZE_P * MINIMAP_SCALE_FACTOR, player_img.h = TILE_SIZE_P * MINIMAP_SCALE_FACTOR); // image of player
	project_3d.img = mlx_new_image(mlx.ptr, project_3d.w = mlx.WIN_W , project_3d.h = mlx.WIN_H);
	create_player2d();//character
	ray();
	render3DProjectedWalls();
	render_mini_map();
	mlx_hook(mlx.win,2,1L<<0, key_press, NULL);
	mlx_hook(mlx.win,3,1L<<1, key_release, NULL);
	mlx_hook(mlx.win,17, 0L, finalize, NULL);
	mlx_loop_hook(mlx.ptr, update, NULL);
	mlx_loop(mlx.ptr);
}

int main ()
{
	InitGame();
	render();
	return (0);
}
