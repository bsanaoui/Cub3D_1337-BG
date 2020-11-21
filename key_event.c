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

#include "Cub3D.h"

int	update()
{
	if(!key_released)
	{
		move_player();
		clear_sprites();
		ray();
		render3DProjectedWalls();
		render_mini_map();
	}
	return (0);
}

int			is_wall(int walkDirection, int kindMove) // kind_move 1 if move up_down and 0 if right_left
{
	float moveStep;
	int x_index;
	int y_index;

	moveStep = walkDirection * MOVE_SPEED;
	x_index = (player.x + (cos(kindMove ? player.Angle : player.Angle - M_PI / 2) * moveStep)) / TILE_SIZE;
	y_index = (player.y + (sin(kindMove ? player.Angle : player.Angle - M_PI / 2) * moveStep)) / TILE_SIZE;
	if ((y_index < m.h && x_index < m.w) && (m.map[y_index][x_index] == '1' || m.map[y_index][x_index] == '2'))
		return (0);  //error
	return (0);
}

int		is_sprite(int dist)
{
	int	i;

	i = 0;
	while (i < count_sprite)
	{
		if (sprites[i++].distance < dist)
			return (0);
	}
	return(0);
}

void		move_walkDirection_direct(int sign_walkDirection)
{
	float moveStep;

	player.walkDirection = sign_walkDirection;
	moveStep =  player.walkDirection * MOVE_SPEED;
	player.x -= cos(player.Angle) * moveStep;
	player.y -= sin(player.Angle) * moveStep;
}

void		move_walkDirection_side(int sign_walkDirection)
{
	float moveStep;

	player.walkDirection = sign_walkDirection;
	moveStep =  player.walkDirection * MOVE_SPEED;
	player.x -= cos(player.Angle - M_PI / 2) * moveStep;
	player.y -= sin(player.Angle - M_PI / 2) * moveStep;
}

void		move_turnDirection(int sign_turnDirection)
{
	player.turnDirection = sign_turnDirection;
	player.Angle = normalizeAngle(player.Angle + (player.turnDirection * ROTATION_SPEED));
}

int			key_release(int key)
{
	key_released = 1;
	return (key);
}

int			key_press(int key)
{
	key_pressed = key;
	key_released = 0;
	return (key);
}

void		speedcontrol(int key_pressed)
{
	if (key_pressed == 115)
	{
		MOVE_SPEED += 0.5;
		ROTATION_SPEED += (0.3 * (M_PI / 180));
	}
	if (key_pressed == 119)
	{
		MOVE_SPEED -= 0.5;
		ROTATION_SPEED -= (0.3 * (M_PI / 180));
	}	
	if (MOVE_SPEED < 0.5)
		MOVE_SPEED = 0.5;
	if (MOVE_SPEED > 8.5)
		MOVE_SPEED = 8.5;
	if (ROTATION_SPEED < (0.6 * (M_PI / 180)))
		ROTATION_SPEED = (0.6 * (M_PI / 180));
	if (ROTATION_SPEED > (5.0 * (M_PI / 180)))
		ROTATION_SPEED = (5.0 * (M_PI / 180));
}

// void		move_player()
// {
// 	if (key_pressed == 2 && !is_wall(-1, 0)) // D
// 			move_walkDirection_side(1);
// 	if (key_pressed == 1 && !is_wall(-1, 1)) // S 
// 			move_walkDirection_direct(1);
// 	if (key_pressed == 0 && !is_wall(1, 0)) // A 
// 			move_walkDirection_side(-1);
// 	if (key_pressed == 13 && !is_wall(1, 1)) // W
// 			move_walkDirection_direct(-1);
// 	if (key_pressed == 123) // <-- 
// 			move_turnDirection(-1);
// 	if (key_pressed == 124) // --> 
// 			move_turnDirection(1);
// 	speedcontrol(key_pressed);
// 	if (key_pressed == 53)
// 		finalize(NULL);
// }

void		move_player()
{
	if (key_pressed == 2) // D
			move_walkDirection_side(1);
	if (key_pressed == 1) // S 
			move_walkDirection_direct(1);
	if (key_pressed == 0) // A 
			move_walkDirection_side(-1);
	if (key_pressed == 13) // W
			move_walkDirection_direct(-1);
	if (key_pressed == 123) // <-- 
			move_turnDirection(-1);
	if (key_pressed == 124) // --> 
			move_turnDirection(1);
	speedcontrol(key_pressed);
	if (key_pressed == 53)
		finalize(NULL);
}