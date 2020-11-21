/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:49:14 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/10/13 15:49:17 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	char	*tab;

	count = 0;
	tab = 0;
	if (!s)
		return (0);
	if (!(tab = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (len > 0 && s[start + count] && ft_strlen((char *)s) > start)
	{
		tab[count] = s[start + count];
		count++;
		len--;
	}
	tab[count] = '\0';
	return (tab);
}
