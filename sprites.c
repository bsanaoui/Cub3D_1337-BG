/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:18:22 by bsanaoui          #+#    #+#             */
/*   Updated: 2020/10/09 22:18:24 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void    sort_sprites()
{
    int i;
    int j;
    T_SPRITE tmp;

    i = 0;
    while (i < (count_sprite - 1))
    {
        j = 0;
        while (j < (count_sprite - i - 1))
        {
            if (sprites[j].distance < sprites[j + 1].distance)
            {
                tmp = sprites[j];
                sprites[j] = sprites[j + 1];
                sprites[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

int             in_array_sprites(int p_x, int p_y)
{
    int i;

    i = 0;
    while (i < count_sprite)
    {
        if (sprites[i].index_x == p_x && sprites[i].index_y == p_y)
        {
            return (1);
        }
        i++;
    }
    return (0);
}

void     get_ray_hit_sp(float s_x, float s_y, int i_sp)
{
    double   alpha;
    t_vector v_ray1;
    t_vector v_sp;

    v_ray1.x = rays[0].wallHit.X - player.x;
    v_ray1.y = rays[0].wallHit.Y - player.y;
    v_sp.x = s_x - player.x;
    v_sp.y = s_y - player.y;
    alpha = -atan2(v_ray1.y, v_ray1.x) + atan2(v_sp.y, v_sp.x);
    if (alpha > M_PI)
        alpha -= M_PI * 2;
    else if (alpha < -M_PI)
        alpha += M_PI * 2;
    sprites[i_sp].num_ray = (n_rays / player.fov) * alpha;
}

void	create_strip_sprite(float tab[], int num_sp) // tab[] = {float x, float y, float width, float height}
{
	int j;
	int	i;
	float scale_x;
    float scale_y;
	double text_color;

	i = 0;
    scale_x = texture_sp.w / tab[2];
    scale_y= texture_sp.h / tab[3];
    text_color = 0;
	while(i < tab[2])
	{
        if ((tab[0] + i) < n_rays && (tab[0] + i) > 0 && rays[(int)tab[0] + i].distance < sprites[num_sp].distance)
        {
            i++;
            continue ;
        }
		j = 0;
		while(j < tab[3])
		{
			text_color = texture_sp.data_tex[(int)(scale_x * i) + (((int)((float)(scale_y * j)) * texture_sp.size_line_texture_sp / 4))];
            if (text_color != 0x980088)
				 put_pixel_in_img(project_3d, tab[0] + i, tab[1] + j, text_color);
			j++;
		}
		i++;
	}
}

void	render_sprites()
{
	//progress
    float	spriteHeight;
	float	correctspriteDistance;
	float	distanceProjectionPlane;
    int     i;

    i = 0;
    sort_sprites();
    while (i < count_sprite)
    {
        distanceProjectionPlane = (mlx.WIN_W / 2) / tan(player.fov / 2);
        correctspriteDistance = sprites[i].distance  * cos(sprites[i].angle - player.Angle);
	    spriteHeight = (TILE_SIZE / correctspriteDistance) * distanceProjectionPlane;
        if (spriteHeight <= (mlx.WIN_W * 1.5))
            create_strip_sprite((float[]){sprites[i].num_ray - (spriteHeight / 2), (mlx.WIN_H / 2) - (spriteHeight / 2), spriteHeight, spriteHeight}, i);
        i++;
    }
}

void    get_sprite_data(T_SPRITE_CAST tmp_sp)
{
   if (!in_array_sprites(tmp_sp.index_x, tmp_sp.index_y))
   {
        sprites[count_sprite].x = tmp_sp.hit_x;
        sprites[count_sprite].y = tmp_sp.hit_y;
        sprites[count_sprite].index_x = tmp_sp.index_x;
        sprites[count_sprite].index_y = tmp_sp.index_y;
        sprites[count_sprite].distance = tmp_sp.distance;
        get_ray_hit_sp(sprites[count_sprite].x, sprites[count_sprite].y, count_sprite);
        sprites[count_sprite].angle = normalizeAngle(player.Angle - player.fov / 2) + (sprites[count_sprite].num_ray * (player.fov / n_rays));
        count_sprite++;
   }
}

void    clear_sprites()
{
    if (sprites)
    {
         free(sprites);
         sprites = NULL;
    }
    count_sprite = 0;
    sprites = (T_SPRITE *)(malloc(n_sp * sizeof(T_SPRITE)));
}
