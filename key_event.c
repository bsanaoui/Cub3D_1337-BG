/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:25:26 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/12/20 15:25:27 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				update(void)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (g_keys[i])
			move_player(g_keys[i]);
		i++;
	}
	clear_sprites();
	ray();
	render3d();
	return (0);
}

int				key_release(int key)
{
	if (key == 13)
		g_keys[0] = 0;
	if (key == 1)
		g_keys[1] = 0;
	if (key == 0)
		g_keys[2] = 0;
	if (key == 2)
		g_keys[3] = 0;
	if (key == 123)
		g_keys[4] = 0;
	if (key == 124)
		g_keys[5] = 0;
	return (key);
}

static	void	reset_key(void)
{
	int i;

	i = 0;
	while (i < 7)
		g_keys[i++] = 0;
}

int				key_press(int key)
{
	if (key == 13)
		g_keys[0] = key;
	if (key == 1)
		g_keys[1] = key;
	if (key == 0)
		g_keys[2] = -5;
	if (key == 2)
		g_keys[3] = key;
	if (key == 123)
		g_keys[4] = key;
	if (key == 124)
		g_keys[5] = key;
	if (key == 53)
		g_keys[6] = key;
	if (key == 260)
		reset_key();
	return (key);
}
