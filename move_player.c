/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:07:33 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/25 20:12:08 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				is_wall(int walk_dir, int kind_move)
{
	float	move_stp;
	int		x_inde;
	int		y_inde;

	move_stp = walk_dir * g_player.move_speed;
	x_inde = (g_player.x + (cos(kind_move ? g_player.angle :
			g_player.angle - M_PI / 2) * move_stp)) / g_tile;
	y_inde = (g_player.y + (sin(kind_move ? g_player.angle :
			g_player.angle - M_PI / 2) * move_stp)) / g_tile;
	if ((y_inde < g_m.h && x_inde < g_m.w) && (g_m.map[y_inde][x_inde] == '1'))
		return (1);
	return (0);
}

static	void	move_walkdirection_direct(int sign_walk_dire)
{
	float move_stp;

	g_player.walk_dir = sign_walk_dire;
	move_stp = g_player.walk_dir * g_player.move_speed;
	g_player.x -= cos(g_player.angle) * move_stp;
	g_player.y -= sin(g_player.angle) * move_stp;
}

static	void	move_walkdirection_side(int sign_walk_dire)
{
	float move_stp;

	g_player.walk_dir = sign_walk_dire;
	move_stp = g_player.walk_dir * g_player.move_speed;
	g_player.x -= cos(g_player.angle - M_PI / 2) * move_stp;
	g_player.y -= sin(g_player.angle - M_PI / 2) * move_stp;
}

void			move_turn_dire(int sign_turn_dire)
{
	g_player.turn_dir = sign_turn_dire;
	g_player.angle = normalize_angle(g_player.angle +
			(g_player.turn_dir * g_player.rot_speed));
}

void			move_player(int key)
{
	if (key == 2 && !is_wall(-1, 0) && g_rays[g_nb_ray - 1].dist > 22)
		move_walkdirection_side(1);
	if (key == 1 && !is_wall(-1, 1))
		move_walkdirection_direct(1);
	if (key == -5 && !is_wall(1, 0) && g_rays[0].dist > 22)
		move_walkdirection_side(-1);
	if (key == 13 && !is_wall(1, 1) && g_rays[g_nb_ray / 2].dist > 18)
		move_walkdirection_direct(-1);
	if (key == 123 && g_rays[0].dist > 21)
		move_turn_dire(-1);
	if (key == 124 && g_rays[g_nb_ray - 1].dist > 21)
		move_turn_dire(1);
	if (key == 53)
		finalize(NULL);
}
