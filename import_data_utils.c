/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_data_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 21:42:25 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/16 21:42:27 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void        get_texture_wall()
{
    int bits_per_pixel;
	int	endian;

    bits_per_pixel = 0;
    endian = 0;
    if (!(g_text_no.img = mlx_xpm_file_to_image (g_cub.ptr, g_text_no.path, &g_text_no.w, &g_text_no.h)))
        ft_perror("NO Texture Not valid !\n");
    g_text_no.data = (int *)mlx_get_data_addr(g_text_no.img, &bits_per_pixel, &g_text_no.size_line, &endian);
    if (!(g_text_so.img = mlx_xpm_file_to_image (g_cub.ptr, g_text_so.path, &g_text_so.w, &g_text_so.h)))
        ft_perror("SO Texture Not valid !\n");
    g_text_so.data = (int *)mlx_get_data_addr(g_text_so.img, &bits_per_pixel, &g_text_so.size_line, &endian);
    if (!(g_text_ea.img = mlx_xpm_file_to_image (g_cub.ptr, g_text_ea.path, &g_text_ea.w, &g_text_ea.h)))
        ft_perror("EA Texture Not valid !\n");
    g_text_ea.data = (int *)mlx_get_data_addr(g_text_ea.img, &bits_per_pixel, &g_text_ea.size_line, &endian);
    if (!(g_text_we.img = mlx_xpm_file_to_image (g_cub.ptr, g_text_we.path, &g_text_we.w, &g_text_we.h)))
        ft_perror("WE Texture Not valid !\n");
    g_text_we.data = (int *)mlx_get_data_addr(g_text_we.img, &bits_per_pixel, &g_text_we.size_line, &endian);
}

void        get_texture_sprite()
{
    int bits_per_pixel = 0;
	int	endian = 0;
	void *img_texture;

    if (!(img_texture = mlx_xpm_file_to_image (g_cub.ptr, g_text_sp.path, &g_text_sp.w, &g_text_sp.h)))
        ft_perror("Sprite Not valid !\n");
	g_text_sp.data  = (int *)mlx_get_data_addr(img_texture, &bits_per_pixel, &g_text_sp.size_line, &endian);
}

void        get_texture()
{
    get_texture_wall();
    get_texture_sprite();
}



int         is_player(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    return (0);
}

static void oriontation_player(char c)
{
    
    if (c == 'N')
        g_player.angle = M_PI * 3 / 2;
    if (c == 'S')
        g_player.angle = M_PI / 2;
    if (c == 'E')
        g_player.angle = 0;
    if (c == 'W')
        g_player.angle = M_PI;
}

void        get_position_player(char c, int pos_x, int pos_y)
{
    g_is_set.player = (g_is_set.player == 0) ? 1 : ft_perror("Duplicate g_player; Set One Position !");
    oriontation_player(c);
    g_player.x = (pos_y * g_tile) + (g_tile / 2);
    g_player.y = (pos_x * g_tile) + (g_tile / 2);
}

int         is_all_elem()
{
    if (g_is_set.resolu && g_is_set.text_no && g_is_set.text_so && g_is_set.text_we && g_is_set.text_ea &&
     g_is_set.sprite && g_is_set.color_c && g_is_set.color_f )
        return (1);
    return (0);
}

void        reset_elem_conf()
{
    g_is_set.resolu = 0;
    g_is_set.text_no = 0;
    g_is_set.text_so = 0;
    g_is_set.text_we = 0;
    g_is_set.text_ea = 0;
    g_is_set.sprite = 0;
    g_is_set.color_c = 0;
    g_is_set.color_f = 0;
    g_is_set.player = 0;
}
