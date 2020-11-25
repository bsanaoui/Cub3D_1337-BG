/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:54:30 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/24 18:01:46 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	is_valid_in_map(char c)
{
	if (c != '2' && c != '1' && c != '0' && c != '\t' &&
			c != ' ' && !is_player(c))
		return (ft_perror("Invalid Map , You add non valid element in map\n"));
	return (1);
}

void		import_map(char *line)
{
	char *tmp;
	tmp = g_m.ptr;
	g_m.ptr = ft_strjoin(g_m.ptr, line);
	free(tmp);
	tmp = g_m.ptr;
	g_m.ptr = ft_strjoin(g_m.ptr, "\n");
	free(tmp);
}

static void	get_tile()
{
	if (ft_strlen(g_m.ptr) < 4)
		ft_perror("No Map!!|n");
	g_tile = ((g_cub.h / g_m.h) < (g_cub.w / g_m.w)) ?
			(g_cub.h / g_m.h) : (g_cub.w / g_m.w);
	if (g_tile == 0)
		g_tile = 1;
	g_tile_p = g_cub.w / g_m.w / 2;
}

static void fill_column(int i, char *line)
{
	int j;
	int len;

	len = (int)ft_strlen(line);
	j = -1;
	while (++j < g_m.w)
	{
		if (j >= len)
			g_m.map[i][j] = ' ';
		else if (is_valid_in_map(line[j]))
			g_m.map[i][j] = line[j];
		if (g_m.map[i][j] == '2')
			g_n_sp++;
		else if (is_player(g_m.map[i][j]))
			get_position_player(g_m.map[i][j], i, j);
	}
	g_m.map[i][j] = '\0';
}

void 		fill_map(void)
{
	char **line;
	int i;

	get_tile();
	line = ft_split(g_m.ptr, '\n');
	g_m.map = malloc(sizeof(char *) * g_m.h);
	i = -1;
	while (++i < g_m.h)
	{
		g_m.map[i] = malloc(sizeof(char) * g_m.w + 1);
		fill_column(i, line[i]);
	}
	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
	check_map();
}
