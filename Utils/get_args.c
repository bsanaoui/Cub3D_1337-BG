/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:03:38 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/26 20:22:15 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	is_valid_extension(char *file, char *ext)
{
	int i;
	int	len;

	len = ft_strlen(file);
	i = len - 4;
	while (i < len && *ext)
		if (file[i++] != *(ext++))
			return (0);
	return (1);
}

void		get_args(int argc, char *argv[])
{
	screenshot = 0;
	config = NULL;
	if (argc >= 2)
	{
		if (is_valid_extension(argv[1], ".cub"))
			config = ft_strdup(argv[1]);
		else
			ft_perror("You must include a \".cub\" File Extension !!\n");
	}
	if (argc == 3)
	{
		if (ft_strlen(argv[2]) == ft_strlen("--save") &&
			ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
			screenshot = 1;
		else
			ft_perror("second arg must be \"--save\"!!\n");
	}
	if (argc == 1 || argc > 3)
		ft_perror("Wrong arguments!!\n");
}
