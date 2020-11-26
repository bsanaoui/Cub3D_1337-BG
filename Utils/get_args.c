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

static	void	ft_screenshoot(void)
{
	int fd;

	fd = open("screen.bmp", O_CREAT | O_RDWR);
	fclose(fopen("screen.bmp", "w"));
}

// static	void	check_args(int argc, char *argv[])
// {
// 	if (argc == 2)
// 	{
// 		if (ft_strncmp(argv[1], "conf.cub", ft_strlen(argv[1])) != 0)
// 			ft_perror("wrong config file\n");
// 	}
// 	else if (argc == 1)
// 		ft_perror("No Config Cub are included\n");
// 	else
// 		ft_perror("To much arguments\n");
// }

void			get_args(int argc, char *argv[])
{
	if (argc >= 2)
	{
		if (ft_strncmp(argv[1], "conf.cub", ft_strlen(argv[1])) != 0)
			ft_perror("wrong config file\n");
	}
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
			ft_screenshoot();
		else 
			ft_perror("second arg must be \"--save\"!!\n");
	}
	if (argc == 1 || argc > 3)
		ft_perror("Wrong arguments!!\n");
}
