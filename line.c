/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:59:14 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/02/04 21:59:15 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void		lineLow(int x0, int y0, int x1, int y1)
{
	int dx;
	int dy;
	int x;
	int y;
	int yi;
	int D;

	dx = x1 - x0; 
	dy = y1 - y0;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	D = 2 * dy - dx;
	y = y0;
	x = x0;
	while (x <= x1)
	{
		put_pixel_in_img(map_img, x, y, RAY_COLOR);
		if (D > 0)
		{
			y = y + yi;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
		x++;
	}
}

static void		lineHigh(int x0, int y0, int x1, int y1)
{
	int dx;
	int dy;
	int x;
	int y;
	int xi;
	int D;

	dx = x1 - x0; 
	dy = y1 - y0;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = 2 * dx - dy;
	x = x0;
	y = y0;
	while (y <= y1)
	{
		put_pixel_in_img(map_img, x, y, RAY_COLOR);
		if (D > 0)
		{
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
		y++;
	}
}

void		line(int x0, int y0, int x1, int y1)
{
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
            lineLow(x1, y1, x0, y0);
        else
            lineLow(x0, y0, x1, y1);
	}
    else
    {
    	if (y0 > y1)
            lineHigh(x1, y1, x0, y0);
        else
            lineHigh(x0, y0, x1, y1);
    }
}