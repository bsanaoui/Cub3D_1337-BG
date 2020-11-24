/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:43:39 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/09/10 19:43:48 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi(char *str, int *len)
{
	int ch;
	int sign;

	ch = 0;
	sign = 1;
	while (*str == ' ' || *str == '\n' || *str == '\v' ||
	*str == '\r' || *str == '\t' || *str == '\f' || *str == '-')
	{
		str++;
		(*len) += 1;
	}
	if (*str == '-')
	{
		sign = -1;
		str++;
		(*len) += 1;
	}
	while (*str >= '0' && *str <= '9')
	{
		ch = (ch * 10) + *str - '0';
		str++;
		(*len) += 1;
	}
	if ((*str < '0' || *str > '9') && *str != '\0' && *str != ' ')
			ft_perror("Invalid character ; !!");
	//str++;
	while (*str)
	{
		if (*str != '\0' && *str != ' ')
			ft_perror("Invalid character ; !!");
		str++;
	}
	
	return (sign * ch);
}
