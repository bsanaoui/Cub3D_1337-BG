/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:59:14 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/26 16:45:22 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_dx;
int		g_dy;
int		g_x;
int		g_y;
int		g_yi;
int		g_xi;
int		g_delta;

static	void		reset_var(void)
{
	g_dx = 0;
	g_dy = 0;
	g_x = 0;
	g_y = 0;
	g_yi = 0;
	g_xi = 0;
	g_delta = 0;
}

static	void		linelow(int x0, int y0, int x1, int y1)
{
	reset_var();
	g_dx = x1 - x0;
	g_dy = y1 - y0;
	g_yi = 1;
	if (g_dy < 0)
	{
		g_yi = -1;
		g_dy = -g_dy;
	}
	g_delta = 2 * g_dy - g_dx;
	g_y = y0;
	g_x = x0;
	while (g_x <= x1)
	{
		put_pixel_in_img(g_map_img, g_x, g_y, RAY_COLOR);
		if (g_delta > 0)
		{
			g_y = g_y + g_yi;
			g_delta = g_delta - 2 * g_dx;
		}
		g_delta = g_delta + 2 * g_dy;
		g_x++;
	}
}

static void			linehigh(int x0, int y0, int x1, int y1)
{
	reset_var();
	g_dx = x1 - x0;
	g_dy = y1 - y0;
	g_xi = 1;
	if (g_dx < 0)
	{
		g_xi = -1;
		g_dx = -g_dx;
	}
	g_delta = 2 * g_dx - g_dy;
	g_x = x0;
	g_y = y0;
	while (g_y <= y1)
	{
		put_pixel_in_img(g_map_img, g_x, g_y, RAY_COLOR);
		if (g_delta > 0)
		{
			g_x = g_x + g_xi;
			g_delta = g_delta - 2 * g_dy;
		}
		g_delta = g_delta + 2 * g_dx;
		g_y++;
	}
}

void				line(int x0, int y0, int x1, int y1)
{
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			linelow(x1, y1, x0, y0);
		else
			linelow(x0, y0, x1, y1);
	}
	else
	{
		if (y0 > y1)
			linehigh(x1, y1, x0, y0);
		else
			linehigh(x0, y0, x1, y1);
	}
}
