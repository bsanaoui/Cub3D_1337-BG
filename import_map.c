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

	tmp = m.ptr;
	m.ptr = ft_strjoin(m.ptr, line);
	free(tmp);
	tmp = m.ptr;
	m.ptr = ft_strjoin(m.ptr, "\n");
	free(tmp);
}

int     check_arr_space(int i, int j)
{
    if(i > 0 && m.map[i-1][j] != ' ' && m.map[i-1][j] != '1')
        return(0);
    if(i < m.h - 1 && m.map[i+1][j] != ' ' && m.map[i+1][j] != '1')
        return(0);
    if(j > 0 && m.map[i][j-1] != ' ' && m.map[i][j-1] != '1')
        return(0);
    if(j < m.w - 1 && m.map[i][j+1] != ' ' && m.map[i][j+1] != '1')
        return(0);
    return (1);
}

void    check_map()
{
    int i;
	int j;
	
	i = 0;
    while (i++ < m.h)
    {
        j = 0;
        while (j++ < m.w)
        {
            if (i - 1 == 0 || j - 1 == 0 || i - 1 == m.h - 1 || j - 1 == m.w - 1)
                if(m.map[i - 1][j - 1] == '0')
					ft_perror("Invalid Map ; Brorders are Open  (Zero) !!");
                if(m.map[i - 1][j -1] == ' ')
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

    if (ft_strlen(m.ptr) < 4)
        ft_perror("No Map!!|n");
    g_tile = ((mlx.WIN_H / m.h) < (mlx.WIN_W / m.w)) ? (mlx.WIN_H / m.h) : (mlx.WIN_W / m.w) ;
    if (g_tile == 0)
        g_tile = 1;
	g_tile_p = mlx.WIN_W / m.w / 2;
	line = ft_split(m.ptr, '\n');
    m.map = malloc(sizeof(char *) * m.h);
	i = 0;
    while(i < m.h)
    {
		m.map[i] = malloc(sizeof(char) * m.w + 1);
        len = (int)ft_strlen(line[i]);
		j = 0;
        while (j < m.w)
        {
            if(j >= len)
                m.map[i][j] = ' ';
            else if (is_valid_in_map(line[i][j]))
             	m.map[i][j] = line[i][j];
            if (m.map[i][j] == '2')
                g_n_sp++;
            else if (is_player(m.map[i][j]))
			    get_position_player(m.map[i][j], i, j);
			j++;
        }
        m.map[i][j] = '\0';
	i++;
    }
    i = 0;
	while (line [i])
		free(line[i++]);
	free(line);
    if (!is_set.player)
        ft_perror("There is no Player in Map !!\n");
  	check_map();
}