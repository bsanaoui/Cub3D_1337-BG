/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:07:26 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/11/27 14:07:27 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char g_header[54] = { 0 };

static	void	bitmap_create(unsigned char *buf, uint32_t imagesize)
{
	int				fd;

	fd = open("screenshot.bmp", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	if (fd == -1)
		return ;
	write(fd, g_header, 54);
	write(fd, buf, imagesize);
	close(fd);
	free(buf);
}

static	void	bitmap_calc(uint32_t imagesize, int32_t width, int32_t height,
int width_in_bytes)
{
	int				col;
	int				row;
	unsigned char	*buf;
	t_img_bmp		img;

	img.data = mlx_get_data_addr(g_img_3d.img, &img.bits_per_pixel,
		&img.size_line, &img.endian);
	row = height - 1;
	buf = malloc(imagesize);
	while (row >= 0)
	{
		col = 0;
		while (col < width)
		{
			img.endian = col * 4 + img.size_line * (height - 1 - row);
			buf[row * width_in_bytes + col * 3 + 0] = img.data[img.endian];
			buf[row * width_in_bytes + col * 3 + 1] = img.data[img.endian + 1];
			buf[row * width_in_bytes + col * 3 + 2] = img.data[img.endian + 2];
			col++;
		}
		row--;
	}
	bitmap_create(buf, imagesize);
}

void			ft_screenshot(void)
{
	t_bitmap bmp;

	bmp.bisize = 40;
	bmp.bfoffbits = 54;
	bmp.biplanes = 1;
	bmp.width = g_cub.w;
	bmp.height = g_cub.h;
	bmp.bitcount = 24;
	bmp.width_in_bytes = ((bmp.width * bmp.bitcount + 31) / 32) * 4;
	bmp.imagesize = bmp.width_in_bytes * bmp.height;
	bmp.filesize = 54 + bmp.imagesize;
	ft_memcpy(g_header, "BM", 2);
	ft_memcpy(g_header + 2, &bmp.filesize, 4);
	ft_memcpy(g_header + 10, &bmp.bfoffbits, 4);
	ft_memcpy(g_header + 14, &bmp.bisize, 4);
	ft_memcpy(g_header + 18, &bmp.width, 4);
	ft_memcpy(g_header + 22, &bmp.height, 4);
	ft_memcpy(g_header + 26, &bmp.biplanes, 2);
	ft_memcpy(g_header + 28, &bmp.bitcount, 2);
	ft_memcpy(g_header + 34, &bmp.imagesize, 4);
	bitmap_calc(bmp.imagesize, bmp.width, bmp.height, bmp.width_in_bytes);
	exit(EXIT_SUCCESS);
}
