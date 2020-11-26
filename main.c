/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:29:18 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/26 17:15:58 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(void)
{
	g_cub.ptr = mlx_init();
	g_player.rot_speed = (1.5 * (M_PI / 180));
	g_player.move_speed = 3.2;
	g_newline = 0;
	reset_elem_conf();
	import_data();
	g_player.turn_dir = 0;
	g_player.walk_dir = 0;
	g_player.fov = 60 * M_PI / 180;
	g_wall_strip_w = 1;
	g_index_sp = 0;
	g_nb_ray = g_cub.w / g_wall_strip_w;
	g_rays = (t_rays *)(malloc((1 * g_nb_ray) * sizeof(t_rays)));
	g_sprites = (t_sprite *)(malloc((1 * g_n_sp) * sizeof(t_sprite)));
	g_cub.win = mlx_new_window(g_cub.ptr, g_cub.w, g_cub.h, "cub3D");
	g_img_3d.w = g_cub.w;
	g_img_3d.h = g_cub.h;
	g_map_img.w = g_cub.w * MAP_SC;
	g_map_img.h = g_cub.h * MAP_SC;
	g_pl_img.w = g_tile_p * MAP_SC;
	g_pl_img.h = g_tile_p * MAP_SC;
}

void	render(void)
{
	g_map_img.img = mlx_new_image(g_cub.ptr, g_map_img.w, g_map_img.h);
	g_pl_img.img = mlx_new_image(g_cub.ptr, g_pl_img.w, g_pl_img.h);
	g_img_3d.img = mlx_new_image(g_cub.ptr, g_img_3d.w, g_img_3d.h);
	create_player2d();
	ray();
	render3d();
	render_mini_map();
	mlx_hook(g_cub.win, 2, 1L << 0, key_press, NULL);
	mlx_hook(g_cub.win, 3, 1L << 1, key_release, NULL);
	mlx_hook(g_cub.win, 17, 0L, finalize, NULL);
	mlx_loop_hook(g_cub.ptr, update, NULL);
	mlx_loop(g_cub.ptr);
}

int		main(int argc, char *argv[])
{
	get_args(argc,argv);
	init_game();
	render();
	return (0);
}
