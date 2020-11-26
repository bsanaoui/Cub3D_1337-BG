/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:54:30 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/25 18:11:10 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int		is_empty_line(char *line)
{
	if (*line == '\0' && (g_m.h == 0 || g_newline))
	{
		free(line);
		return (1);
	}
	else if (*line == '\0' && g_m.h > 0 && g_newline == 0)
	{
		g_newline++;
		free(line);
		return (1);
	}
	else if (g_newline)
		ft_perror("Map Invalid; Empty Line !!\n");
	return (0);
}

static	void	fill_data(char *line)
{
	char	**ptr;
	int		i;

	ptr = ft_split(line, ' ');
	if (!(*ptr))
		ft_perror("Non Valid cub.config !!\n");
	if (**ptr == 'R')
		resolution(ptr);
	else if (is_path_texture(*ptr))
		get_path_texture(line);
	else if (ptr[0][0] == 'F' || ptr[0][0] == 'C')
		color_flo_cei(line);
	else if (is_all_elem())
	{
		g_m.w = (int)ft_strlen(line) > g_m.w ? (int)
			ft_strlen(line) : g_m.w;
		import_map(line);
		g_m.h++;
	}
	else
		ft_perror("Non Valid cub.config !!\n");
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

static	void	init_var(int *return_val, int *fd)
{
	*return_val = 1;
	*fd = open("conf.cub", O_RDONLY);
	g_m.w = 0;
	g_m.h = 0;
	g_m.ptr = ft_strdup("");
}

void			import_data(void)
{
	int		fd;
	char	*line;
	int		return_val;

	init_var(&return_val, &fd);
	while (return_val)
	{
		return_val = get_next_line(fd, &line);
		if (is_empty_line(line))
			continue ;
		fill_data(line);
		if (line)
			free(line);
	}
	if (!is_all_elem())
		ft_perror("Missing Element(s) in Config File !!\n");
	fill_map();
	get_texture();
	fclose(fopen("conf.cub", "r"));
}
