/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:17:26 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/10/16 19:44:50 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int			i;
	char		*ds;
	const char	*sr;

	if (!dst && !src)
		return (NULL);
	i = 0;
	ds = dst;
	sr = src;
	while (i < (int)n)
	{
		ds[i] = sr[i];
		i++;
	}
	return (dst);
}
