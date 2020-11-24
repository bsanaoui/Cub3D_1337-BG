/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:54:30 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/15 19:54:31 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	resolution(char **ptr)
{
	int len_width;
	int	i;

	len_width = 0;
	g_is_set.resolu = (g_is_set.resolu == 0) ? 1 : ft_perror("Duplicate Resolution; Set One Resolution !");
	i = 0;
	while (ptr[i])
		i++;
	if (i != 3)
		ft_perror("Invalid Resolution ; Other Param");
	g_cub.w = ft_atoi(ptr[1], &len_width);
	g_cub.h = ft_atoi(ptr[2], &len_width);

	if (g_cub.w <= 0 || g_cub.h <= 0)
		ft_perror("Invalid Resolution !!\n");
	g_cub.w= (g_cub.w > 2880) ? 2880: g_cub.w;
	g_cub.h = (g_cub.h > 1620) ? 1620: g_cub.h;
}

void	color_flo_cei(char *line)
{
	int	r;
	int	g;
	int	b;
	char **ptr;
	int i;

	while (*line != 'C' && *line != 'F' && *line)
		line++;
	ptr = ft_split(line + 1, ',');
	i = 0;
	while (ptr[i])
		i++;
	if (i != 3)
			ft_perror("Invalid Color ; Other Param");
	r = ft_atoi(ptr[0], &r);
	g = ft_atoi(ptr[1], &g);
	b = ft_atoi(ptr[2], &b);
	if (r < 0 || r > 256 || g < 0 || g > 256 || b < 0 || b > 256)
		ft_perror("Invalid Color");
	if (*line == 'F')
	{
		g_is_set.color_f = (g_is_set.color_f == 0) ? 1 : ft_perror("Duplicate Floor Color; Set One Color !\n");
		g_floor_color = (r * 256 * 256) + (g * 256) + b;
	}
	else
	{
		g_is_set.color_c = (g_is_set.color_c == 0) ? 1 : ft_perror("Duplicate Ceil Color; Set One Color !\n");
		g_ceil_color = (r * 256 * 256) + (g * 256) + b;
	}
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

static	void	get_path_texture(char *line)
{
	char *ptr;

	while (*line != 'S' && *line != 'N' && *line != 'E' && *line != 'W' && *line)
		line++;
	ptr = ft_strtrim(line + 2, " ");
	if (*(line + 2) == ' ')
	{
		if ((*line == 'N' && *(line + 1) == 'O'))
			g_text_no.path = ft_strdup(ptr);
		else if ((*line== 'S' && *(line + 1) == 'O'))
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

static	int		is_path_texture(char *line)
{
	if (*line == 'N' && *(line + 1) == 'O')
		return((g_is_set.text_no = (g_is_set.text_no == 0) ? 1 : ft_perror("Duplicate NO Texture\n")));
	else if (*line == 'S' && *(line + 1) == 'O')
		return((g_is_set.text_so = (g_is_set.text_so == 0) ? 1 : ft_perror("Duplicate SO Texture !")));
	else if (*line == 'W' && *(line + 1) == 'E')
		return((g_is_set.text_we = (g_is_set.text_we == 0) ? 1 : ft_perror("Duplicate WE Texture\n")));
	else if (*line == 'E' && *(line + 1) == 'A')
		return((g_is_set.text_ea = (g_is_set.text_ea == 0) ? 1 : ft_perror("Duplicate EA Texture\n")));
	else if (*line == 'S')
		return((g_is_set.sprite = (g_is_set.sprite == 0) ? 1 : ft_perror("Duplicate Sprite\n")));
	return (0);
}

int				is_line_empty(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\0')
			return(0);
		i++;
	}
	return (1);
}

void			import_data()
{
	int		fd;
	char	*line;
	int 	return_val;
	int		i;
	char 	**ptr;

	return_val = 1;
	fd = open("conf.cub", O_RDONLY);
	g_m.w = 0;
	g_m.h = 0;
	g_m.ptr = ft_strdup("");
	while (return_val)
	{
		i = 0;
		return_val = get_next_line(fd, &line);
		if (is_line_empty(line) && (g_m.h == 0 || g_newline))
			continue ;
		else if (is_line_empty(line) && g_m.h > 0 && g_newline == 0)
		{
			g_newline++;
			continue ;
		}
		else if (g_newline)
			ft_perror("Map Invalid; Empty Line !!\n");
		ptr = ft_split(line, ' ');
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
		if (line)
			free(line);
	}
	if (!is_all_elem())
		ft_perror("Missing Element(s) in Config File !!\n");
	fill_map();
	get_texture();
	fclose(fopen("conf.cub" , "r"));
}