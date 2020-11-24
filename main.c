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

#include "cub3d.h"

// void	ft_screenshoot()
// {
// 	int fd = open("screen.bmp", O_CREAT | O_RDWR);
// }

void	InitGame()
{
	mlx.ptr = mlx_init();
	g_rot_speed = (2.0 * (M_PI / 180));
	g_move_speed = 4.0;
	g_newline = 0;
	reset_elem_conf();
	import_data();
	player.turnDirection = 0;
	player.walkDirection = 0;
	player.fov = 60 * M_PI / 180;
	g_wall_strip_w = 1;
	g_index_sp = 0;
	g_nb_ray = mlx.WIN_W / g_wall_strip_w;
	rays = (T_RAYS *)(malloc(g_nb_ray * sizeof(T_RAYS)));
	sprites = (T_SPRITE *)(malloc(g_n_sp * sizeof(T_SPRITE)));
	mlx.win = mlx_new_window(mlx.ptr, mlx.WIN_W , mlx.WIN_H, "cub3D");
}

void	render()
{
	map_img.img = mlx_new_image(mlx.ptr, map_img.w = mlx.WIN_W * MAP_SC, map_img.h = mlx.WIN_H * MAP_SC); //image of maps
	player_img.img = mlx_new_image(mlx.ptr, player_img.w = g_tile_p * MAP_SC, player_img.h = g_tile_p * MAP_SC); // image of player
	project_3d.img = mlx_new_image(mlx.ptr, project_3d.w = mlx.WIN_W , project_3d.h = mlx.WIN_H);
	create_player2d();//character
	ray();
	render3DProjectedWalls();
	//ft_screenshoot();
	//render_mini_map();
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