/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_resol_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:19:38 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/25 17:22:58 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			resolution(char **ptr)
{
	int len_width;
	int	i;

	len_width = 0;
	g_is_set.resolu = (g_is_set.resolu == 0) ?
		1 : ft_perror("Duplicate Resolution; Set One Resolution !\n");
	i = 0;
	while (ptr[i])
		i++;
	if (i != 3)
		ft_perror("Invalid Resolution ; Other Param\n");
	g_cub.w = ft_atoi_parse(ptr[1], &len_width);
	g_cub.h = ft_atoi_parse(ptr[2], &len_width);
	if (g_cub.w <= 0 || g_cub.h <= 0)
		ft_perror("Invalid Resolution !!\n");
	g_cub.w = (g_cub.w > 2880) ? 2880 : g_cub.w;
	g_cub.h = (g_cub.h > 1620) ? 1620 : g_cub.h;
}

static	void	check_error_color(char *line, char **ptr)
{
	int i;
	int k;

	k = 0;
	i = 0;
	while (line[i] != '\0')
		if (line[i++] == ',')
			k++;
	i = 0;
	while (ptr[i])
		i++;
	if (i != 3 || k != 2)
		ft_perror("Invalid Color ; Other Param\n");
}

static	void	set_color(char c, int r, int g, int b)
{
	if (c == 'F')
	{
		g_is_set.color_f = (g_is_set.color_f == 0) ?
				1 : ft_perror("Duplicate Floor Color; Set One Color !\n");
		g_floor_color = (r * 256 * 256) + (g * 256) + b;
	}
	else
	{
		g_is_set.color_c = (g_is_set.color_c == 0) ?
				1 : ft_perror("Duplicate Ceil Color; Set One Color !\n");
		g_ceil_color = (r * 256 * 256) + (g * 256) + b;
	}
}

void			color_flo_cei(char *line)
{
	int		r;
	int		g;
	int		b;
	char	**ptr;
	int		i;

	while (*line != 'C' && *line != 'F' && *line)
		line++;
	ptr = ft_split(line + 1, ',');
	check_error_color(line, ptr);
	r = ft_atoi_parse(ptr[0], &r);
	g = ft_atoi_parse(ptr[1], &g);
	b = ft_atoi_parse(ptr[2], &b);
	if (r < 0 || r > 256 || g < 0 || g > 256 || b < 0 || b > 256)
		ft_perror("Invalid Color");
	set_color(*line, r, g, b);
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}
