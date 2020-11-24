/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:54:30 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/17 19:54:31 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	import_map(char *line)
{
	char *tmp;

	tmp = g_m.ptr;
	g_m.ptr = ft_strjoin(g_m.ptr, line);
	free(tmp);
	tmp = g_m.ptr;
	g_m.ptr = ft_strjoin(g_m.ptr, "\n");
	free(tmp);
}

int     check_arr_space(int i, int j)
{
    if(i > 0 && g_m.map[i-1][j] != ' ' && g_m.map[i-1][j] != '1')
        return(0);
    if(i < g_m.h - 1 && g_m.map[i+1][j] != ' ' && g_m.map[i+1][j] != '1')
        return(0);
    if(j > 0 && g_m.map[i][j-1] != ' ' && g_m.map[i][j-1] != '1')
        return(0);
    if(j < g_m.w - 1 && g_m.map[i][j+1] != ' ' && g_m.map[i][j+1] != '1')
        return(0);
    return (1);
}

void    check_map()
{
    int i;
	int j;
	
	i = 0;
    while (i++ < g_m.h)
    {
        j = 0;
        while (j++ < g_m.w)
        {
            if (i - 1 == 0 || j - 1 == 0 || i - 1 == g_m.h - 1 || j - 1 == g_m.w - 1)
                if(g_m.map[i - 1][j - 1] == '0')
					ft_perror("Invalid Map ; Brorders are Open  (Zero) !!");
                if(g_m.map[i - 1][j -1] == ' ')
                    if(!check_arr_space(i - 1, j - 1))
                        ft_perror("Invalid Map ; Brorders are Open (Space) !!");
        }
    }
}

int     is_valid_in_map(char c)
{
    if (c != '2' && c != '1' && c != '0' && c != '\t' && c != ' ' && !is_player(c))
        return(ft_perror("Invalid Map , You add non valid element in map\n"));
    return (1);
}

void    fill_map()
{
    char **line;
    int i;
    int j;
    int len;

    if (ft_strlen(g_m.ptr) < 4)
        ft_perror("No Map!!|n");
    g_tile = ((g_cub.h / g_m.h) < (g_cub.w / g_m.w)) ? (g_cub.h / g_m.h) : (g_cub.w / g_m.w) ;
    if (g_tile == 0)
        g_tile = 1;
	g_tile_p = g_cub.w / g_m.w / 2;
	line = ft_split(g_m.ptr, '\n');
    g_m.map = malloc(sizeof(char *) * g_m.h);
	i = 0;
    while(i < g_m.h)
    {
		g_m.map[i] = malloc(sizeof(char) * g_m.w + 1);
        len = (int)ft_strlen(line[i]);
		j = 0;
        while (j < g_m.w)
        {
            if(j >= len)
                g_m.map[i][j] = ' ';
            else if (is_valid_in_map(line[i][j]))
             	g_m.map[i][j] = line[i][j];
            if (g_m.map[i][j] == '2')
                g_n_sp++;
            else if (is_player(g_m.map[i][j]))
			    get_position_player(g_m.map[i][j], i, j);
			j++;
        }
        g_m.map[i][j] = '\0';
	i++;
    }
    i = 0;
	while (line [i])
		free(line[i++]);
	free(line);
    if (!g_is_set.player)
        ft_perror("There is no player in Map !!\n");
  	check_map();
}