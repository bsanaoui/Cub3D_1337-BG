/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:43:39 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/26 17:19:09 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void		check_error(char *str)
{
	if ((*str < '0' || *str > '9') && *str != '\0' && *str != ' ')
		ft_perror("Invalid character ; !!\n");
	while (*str)
	{
		if (*str != '\0' && *str != ' ')
			ft_perror("Invalid character ; !!\n");
		str++;
	}
}

long	double		ft_atoi_parse(char *str, int *len)
{
	long	double	ch;
	int				sign;
	int				space;

	ch = 0;
	sign = 1;
	space = 0;
	*len = 0;
	while (*str == ' ' || *str == '\n' || *str == '\v' ||
			*str == '\r' || *str == '\t' || *str == '\f')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		space = 1;
		ch = (ch * 10) + *str - '0';
		if (ch > 20000)
			(*len) = 1;
		str++;
	}
	if (!space)
		ft_perror("Invalid character ; !!\n");
	check_error(str);
	if (*len)
		return (30000);
	return (sign * ch);
}
