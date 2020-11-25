/* *****w********************************************************************* */
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

int	update()
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
	render_mini_map();
	return (0);
}

int			is_wall(int walk_dir, int kind_move)
{
	float moveStep;
	int x_index;
	int y_index;

	moveStep = walk_dir * g_player.move_speed;
	x_index = (g_player.x + (cos(kind_move ? g_player.angle : g_player.angle - M_PI / 2) * moveStep)) / g_tile;
	y_index = (g_player.y + (sin(kind_move ? g_player.angle : g_player.angle - M_PI / 2) * moveStep)) / g_tile;
	if ((y_index < g_m.h && x_index < g_m.w) && (g_m.map[y_index][x_index] == '1'))
		return (1);
	return (0);
}

void		move_walkDirection_direct(int sign_walkDirection)
{
	float moveStep;

	g_player.walk_dir = sign_walkDirection;
	moveStep =  g_player.walk_dir * g_player.move_speed;
	g_player.x -= cos(g_player.angle) * moveStep;
	g_player.y -= sin(g_player.angle) * moveStep;
}

void		move_walkDirection_side(int sign_walkDirection)
{
	float moveStep;

	g_player.walk_dir = sign_walkDirection;
	moveStep =  g_player.walk_dir * g_player.move_speed;
	g_player.x -= cos(g_player.angle - M_PI / 2) * moveStep;
	g_player.y -= sin(g_player.angle - M_PI / 2) * moveStep;
}

void		move_turnDirection(int sign_turnDirection)
{
	g_player.turn_dir = sign_turnDirection;
	g_player.angle = normalize_angle(g_player.angle + (g_player.turn_dir * g_player.rot_speed));
}

int			key_release(int key)
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

int			key_press(int key)
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
	return (key);
}

void		move_player(int key)
{
	if (key == 2 && !is_wall(-1, 0) && g_rays[g_nb_ray - 1].dist > 17) // D
			move_walkDirection_side(1);
	if (key == 1 && !is_wall(-1, 1)) // S 
			move_walkDirection_direct(1);
	if (key == -5 && !is_wall(1, 0) && g_rays[0].dist > 17) // A 
			move_walkDirection_side(-1);
	if (key == 13 && !is_wall(1, 1) && g_rays[g_nb_ray / 2].dist > 17) // W
			move_walkDirection_direct(-1);
	if (key == 123 && g_rays[0].dist > 17) // <-- 
			move_turnDirection(-1);
	if (key == 124 && g_rays[g_nb_ray - 1].dist > 17) // -->
			move_turnDirection(1);
	if (key == 53)
		finalize(NULL);
}