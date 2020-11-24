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
		if (keys[i])
			move_player(keys[i]);

		i++;
	}
	clear_sprites();
	ray();
	render3DProjectedWalls();
	//render_mini_map();
	return (0);
}

int			is_wall(int walkDirection, int kindMove) // kind_move 1 if move up_down and 0 if right_left
{
	float moveStep;
	int x_index;
	int y_index;

	moveStep = walkDirection * g_move_speed;
	x_index = (player.x + (cos(kindMove ? player.Angle : player.Angle - M_PI / 2) * moveStep)) / g_tile;
	y_index = (player.y + (sin(kindMove ? player.Angle : player.Angle - M_PI / 2) * moveStep)) / g_tile;
	if ((y_index < m.h && x_index < m.w) && (m.map[y_index][x_index] == '1'))
		return (1);  //error
	return (0);
}

void		move_walkDirection_direct(int sign_walkDirection)
{
	float moveStep;

	player.walkDirection = sign_walkDirection;
	moveStep =  player.walkDirection * g_move_speed;
	player.x -= cos(player.Angle) * moveStep;
	player.y -= sin(player.Angle) * moveStep;
}

void		move_walkDirection_side(int sign_walkDirection)
{
	float moveStep;

	player.walkDirection = sign_walkDirection;
	moveStep =  player.walkDirection * g_move_speed;
	player.x -= cos(player.Angle - M_PI / 2) * moveStep;
	player.y -= sin(player.Angle - M_PI / 2) * moveStep;
}

void		move_turnDirection(int sign_turnDirection)
{
	player.turnDirection = sign_turnDirection;
	player.Angle = normalizeAngle(player.Angle + (player.turnDirection * g_rot_speed));
}

int			key_release(int key)
{
	if (key == 13)
		keys[0] = 0;
	if (key == 1)
		keys[1] = 0;
	if (key == 0)
		keys[2] = 0;
	if (key == 2)
		keys[3] = 0;
	if (key == 123)
		keys[4] = 0;
	if (key == 124)
		keys[5] = 0;
	return (key);
}

int			key_press(int key)
{
	if (key == 13)
		keys[0] = key;
	if (key == 1)
		keys[1] = key;
	if (key == 0)
		keys[2] = -5;
	if (key == 2)
		keys[3] = key;
	if (key == 123)
		keys[4] = key;
	if (key == 124)
		keys[5] = key;
	if (key == 53)
		keys[6] = key;
	return (key);
}

void		speedcontrol(int key_pressed)
{
	if (key_pressed == 115)
	{
		g_move_speed += 0.5;
		g_rot_speed += (0.3 * (M_PI / 180));
	}
	if (key_pressed == 119)
	{
		g_move_speed -= 0.5;
		g_rot_speed -= (0.3 * (M_PI / 180));
	}	
	if (g_move_speed < 0.5)
		g_move_speed = 0.5;
	if (g_move_speed > 8.5)
		g_move_speed = 8.5;
	if (g_rot_speed < (0.6 * (M_PI / 180)))
		g_rot_speed = (0.6 * (M_PI / 180));
	if (g_rot_speed > (5.0 * (M_PI / 180)))
		g_rot_speed = (5.0 * (M_PI / 180));
}

void		move_player(int key)
{
	if (key == 2 && !is_wall(-1, 0) && rays[g_nb_ray - 1].distance > 20) // D
			move_walkDirection_side(1);
	if (key == 1 && !is_wall(-1, 1)) // S 
			move_walkDirection_direct(1);
	if (key == -5 && !is_wall(1, 0) && rays[0].distance > 20) // A 
			move_walkDirection_side(-1);
	if (key == 13 && !is_wall(1, 1) && rays[g_nb_ray / 2].distance > 22) // W
			move_walkDirection_direct(-1);
	if (key == 123 && rays[0].distance > 20) // <-- 
			move_turnDirection(-1);
	if (key == 124 && rays[g_nb_ray - 1].distance > 20) // --> 
			move_turnDirection(1);
	speedcontrol(key);
	if (key == 53)
		finalize(NULL);
}