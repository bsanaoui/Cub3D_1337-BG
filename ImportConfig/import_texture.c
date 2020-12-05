/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:29:27 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/25 14:52:44 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_bpp;
int		g_endian;

static	int	is_val_ext(char *file)
{
	if (is_valid_ext(file, ".xpm") ||
		is_valid_ext(file, ".XPM"))
		return (1);
	return (0);
}

void		get_path_texture(char *line)
{
	char *ptr;

	while (*line != 'S' && *line != 'N' &&
			*line != 'E' && *line != 'W' && *line)
		line++;
	ptr = ft_strtrim(line + 2, " ");
	if (*(line + 2) == ' ')
	{
		if ((*line == 'N' && *(line + 1) == 'O'))
			g_text_no.path = ft_strdup(ptr);
		else if ((*line == 'S' && *(line + 1) == 'O'))
			g_text_so.path = ft_strdup(ptr);
		else if ((*line == 'W' && *(line + 1) == 'E'))
			g_text_we.path = ft_strdup(ptr);
		else if ((*line == 'E' && *(line + 1) == 'A'))
			g_text_ea.path = ft_strdup(ptr);
	}
	if (*line == 'S' && *(line + 1) == ' ')
		g_text_sp.path = ft_strdup(ptr);
	if (ptr)
		free(ptr);
}

int			is_path_texture(char *line)
{
	if (*line == 'N' && *(line + 1) == 'O')
		return ((g_is_set.text_no = (g_is_set.text_no == 0) ?
					1 : ft_perror("Duplicate NO Texture\n")));
	else if (*line == 'S' && *(line + 1) == 'O')
		return ((g_is_set.text_so = (g_is_set.text_so == 0) ?
					1 : ft_perror("Duplicate SO Texture !")));
	else if (*line == 'W' && *(line + 1) == 'E')
		return ((g_is_set.text_we = (g_is_set.text_we == 0) ?
					1 : ft_perror("Duplicate WE Texture\n")));
	else if (*line == 'E' && *(line + 1) == 'A')
		return ((g_is_set.text_ea = (g_is_set.text_ea == 0) ?
					1 : ft_perror("Duplicate EA Texture\n")));
	else if (*line == 'S')
		return ((g_is_set.sprite = (g_is_set.sprite == 0) ?
					1 : ft_perror("Duplicate Sprite\n")));
		return (0);
}

void		get_texture_sprite(void)
{
	g_bpp = 0;
	g_endian = 0;
	if (!(g_text_sp.img = mlx_xpm_file_to_image(g_cub.ptr, g_text_sp.path,
		&g_text_sp.w, &g_text_sp.h)) || !is_val_ext(g_text_sp.path))
		ft_perror("Sprite Not valid !\n");
	g_text_sp.data = (int *)mlx_get_data_addr(g_text_sp.img, &g_bpp,
			&g_text_sp.size_line, &g_endian);
}

void		get_texture(void)
{
	g_bpp = 0;
	g_endian = 0;
	if (!(g_text_no.img = mlx_xpm_file_to_image(g_cub.ptr, g_text_no.path,
		&g_text_no.w, &g_text_no.h)) || !is_val_ext(g_text_no.path))
		ft_perror("NO Texture Not valid !\n");
	g_text_no.data = (int *)mlx_get_data_addr(g_text_no.img, &g_bpp,
			&g_text_no.size_line, &g_endian);
	if (!(g_text_so.img = mlx_xpm_file_to_image(g_cub.ptr, g_text_so.path,
		&g_text_so.w, &g_text_so.h)) || !is_val_ext(g_text_so.path))
		ft_perror("SO Texture Not valid !\n");
	g_text_so.data = (int *)mlx_get_data_addr(g_text_so.img, &g_bpp,
			&g_text_so.size_line, &g_endian);
	if (!(g_text_ea.img = mlx_xpm_file_to_image(g_cub.ptr, g_text_ea.path,
		&g_text_ea.w, &g_text_ea.h)) || !is_val_ext(g_text_ea.path))
		ft_perror("EA Texture Not valid !\n");
	g_text_ea.data = (int *)mlx_get_data_addr(g_text_ea.img, &g_bpp,
			&g_text_ea.size_line, &g_endian);
	if (!(g_text_we.img = mlx_xpm_file_to_image(g_cub.ptr, g_text_we.path,
		&g_text_we.w, &g_text_we.h)) || !is_val_ext(g_text_we.path))
		ft_perror("WE Texture Not valid !\n");
	g_text_we.data = (int *)mlx_get_data_addr(g_text_we.img, &g_bpp,
			&g_text_we.size_line, &g_endian);
	get_texture_sprite();
}
