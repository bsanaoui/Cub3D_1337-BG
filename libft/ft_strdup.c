/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 23:26:34 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/10/12 23:26:38 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)malloc((ft_strlen((char *)s1) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (*s1 != '\0')
	{
		p[i] = *((char *)s1);
		i++;
		s1++;
	}
	p[i] = '\0';
	return (p);
}
