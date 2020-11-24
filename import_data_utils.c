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
    if (!(text_no.img = mlx_xpm_file_to_image (mlx.ptr, text_no.path, &text_no.w, &text_no.h)))
        ft_perror("NO Texture Not valid !\n");
    text_no.data = (int *)mlx_get_data_addr(text_no.img, &bits_per_pixel, &text_no.size_line, &endian);
    if (!(text_so.img = mlx_xpm_file_to_image (mlx.ptr, text_so.path, &text_so.w, &text_so.h)))
        ft_perror("SO Texture Not valid !\n");
    text_so.data = (int *)mlx_get_data_addr(text_so.img, &bits_per_pixel, &text_so.size_line, &endian);
    if (!(text_ea.img = mlx_xpm_file_to_image (mlx.ptr, text_ea.path, &text_ea.w, &text_ea.h)))
        ft_perror("EA Texture Not valid !\n");
    text_ea.data = (int *)mlx_get_data_addr(text_ea.img, &bits_per_pixel, &text_ea.size_line, &endian);
    if (!(text_we.img = mlx_xpm_file_to_image (mlx.ptr, text_we.path, &text_we.w, &text_we.h)))
        ft_perror("WE Texture Not valid !\n");
    text_we.data = (int *)mlx_get_data_addr(text_we.img, &bits_per_pixel, &text_we.size_line, &endian);
}

void        get_texture_sprite()
{
    int bits_per_pixel = 0;
	int	endian = 0;
	void *img_texture;

    if (!(img_texture = mlx_xpm_file_to_image (mlx.ptr, texture_sp.path, &texture_sp.w, &texture_sp.h)))
        ft_perror("Sprite Not valid !\n");
	texture_sp.data_tex  = (int *)mlx_get_data_addr(img_texture, &bits_per_pixel, &texture_sp.size_line_texture_sp, &endian);
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
        player.Angle = M_PI * 3 / 2;
    if (c == 'S')
        player.Angle = M_PI / 2;
    if (c == 'E')
        player.Angle = 0;
    if (c == 'W')
        player.Angle = M_PI;
}

void        get_position_player(char c, int pos_x, int pos_y)
{
    is_set.player = (is_set.player == 0) ? 1 : ft_perror("Duplicate PLayer; Set One Position !");
    oriontation_player(c);
    player.x = (pos_y * TILE_SIZE) + (TILE_SIZE / 2);
    player.y = (pos_x * TILE_SIZE) + (TILE_SIZE / 2);
}

int         is_all_elem()
{
    if (is_set.resolu && is_set.text_no && is_set.text_so && is_set.text_we && is_set.text_ea &&
     is_set.sprite && is_set.color_c && is_set.color_f )
        return (1);
    return (0);
}

void        reset_elem_conf()
{
    is_set.resolu = 0;
    is_set.text_no = 0;
    is_set.text_so = 0;
    is_set.text_we = 0;
    is_set.text_ea = 0;
    is_set.sprite = 0;
    is_set.color_c = 0;
    is_set.color_f = 0;
    is_set.player = 0;
}
