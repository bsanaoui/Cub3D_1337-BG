/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:11:08 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/24 17:28:49 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_arr_space(int i, int j)
{
	if (i > 0 && g_m.map[i - 1][j] != ' ' && g_m.map[i - 1][j] != '1')
		return (0);
	if (i < g_m.h - 1 && g_m.map[i + 1][j] != ' ' && g_m.map[i + 1][j] != '1')
		return (0);
	if (j > 0 && g_m.map[i][j - 1] != ' ' && g_m.map[i][j - 1] != '1')
		return (0);
	if (j < g_m.w - 1 && g_m.map[i][j + 1] != ' ' && g_m.map[i][j + 1] != '1')
		return (0);
	return (1);
}

void	check_map(void)
{
	int i;
	int j;

	i = 0;
	if (!g_is_set.player)
		ft_perror("There is no player in Map !!\n");
	while (i++ < g_m.h)
	{
		j = 0;
		while (j++ < g_m.w)
		{
			if (i - 1 == 0 || j - 1 == 0 || i - 1 == g_m.h - 1 ||
					j - 1 == g_m.w - 1)
				if (g_m.map[i - 1][j - 1] == '0')
					ft_perror("Invalid Map ; Brorders are Open  (Zero) !!");
			if (g_m.map[i - 1][j - 1] == ' ')
				if (!check_arr_space(i - 1, j - 1))
					ft_perror("Invalid Map ; Brorders are Open (Space) !!");
		}
	}
}
