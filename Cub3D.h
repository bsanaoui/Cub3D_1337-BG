/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:38:31 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/12/18 17:40:24 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <stdio.h>

# define MAP_SC 0.3
# define PLAYER_COLOR 16711680
# define RAY_COLOR 16776960
# define MAP_COLOR 3093151
# define SPRITE_COLOR 14557865

float			g_tile;
float			g_tile_p;
int				g_floor_color;
int				g_ceil_color;
int				g_nb_ray;
int				g_wall_strip_w;
int				g_index_sp;
int				g_n_sp;
int				g_newline;
int				g_screenshot;
char			*g_config;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_map
{
	char		*ptr;
	char		**map;
	int			w;
	int			h;
}				t_map;

typedef struct	s_img
{
	void		*img;
	int			h;
	int			w;
	int			*data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_cub
{
	void		*ptr;
	void		*win;
	int			h;
	int			w;
}				t_cub;

typedef struct	s_player
{
	double		x;
	double		y;
	int			turn_dir;
	int			walk_dir;
	double		angle;
	float		rot_speed;
	float		move_speed;
	double		fov;
}				t_player;

typedef struct	s_wall_hit
{
	double		x;
	double		y;
}				t_wall_hit;

typedef struct	s_rays
{
	double		angle;
	double		dist;
	int			was_hit_vertical;
	t_wall_hit	wall_hit;
	int			is_down;
	int			is_up;
	int			is_right;
	int			is_left;
}				t_rays;

typedef	struct	s_sp_cast
{
	int			hit_horz;
	int			hit_vert;
	double		hit_x;
	double		hit_y;
	double		dist;
	int			index_x;
	int			index_y;
}				t_sp_cast;

typedef struct	s_cast
{
	double		xinterept;
	double		yinterept;
	double		xstep;
	double		ystep;
	double		next_touch_x;
	double		next_touch_y;
	double		wall_hit_x;
	double		wall_hit_y;
	double		dist;
	int			found_horz_wall;
	int			found_vert_wall;
	int			minus_y;
	int			minus_x;
	t_sp_cast	*sprite;
	int			i_sp;
}				t_cast;

typedef struct	s_ray
{
	double		angle;
	int			is_down;
	int			is_up;
	int			is_right;
	int			is_left;
}				t_ray;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			index_x;
	int			index_y;
	double		dist;
	int			num_ray;
	double		angle;
}				t_sprite;

typedef struct	s_texture
{
	char		*path;
	int			*data;
	void		*img;
	int			w;
	int			h;
	int			size_line;
}				t_texture;

typedef struct	s_is_set_el
{
	int			resolu;
	int			text_no;
	int			text_so;
	int			text_we;
	int			text_ea;
	int			sprite;
	int			color_f;
	int			color_c;
	int			player;
}				t_is_set_el;

typedef struct	s_bitmap
{
	int32_t		width;
	int32_t		height;
	uint16_t	bitcount;
	int			width_in_bytes;
	uint32_t	imagesize;
	uint32_t	bisize;
	uint32_t	bfoffbits;
	uint32_t	filesize;
	uint16_t	biplanes;
}				t_bitmap;

typedef	struct	s_img_bmp
{
	char		*data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_img_bmp;

t_map			g_m;
t_cub			g_cub;
t_img			g_map_img;
t_img			g_pl_img;
t_img			g_img_3d;
t_player		g_player;
t_rays			*g_rays;
t_sprite		*g_sprites;
t_is_set_el		g_is_set;
t_texture		g_text_sp;
t_texture		g_text_no;
t_texture		g_text_so;
t_texture		g_text_we;
t_texture		g_text_ea;
int				g_keys[7];

int				ft_atoi_parse(char *str, int *len);
int				update();
int				key_press(int key);
int				key_release(int key);
void			move_player(int key);
void			create_2d_map(void);
void			create_grid(int i, int j);
void			create_player2d();
void			display_player();
void			line(int x0, int y0, int x1, int y1);
void			put_pixel_in_img(t_img s_img, int x, int y, int color);
void			ray();
int				is_wall(int walk_dir, int kind_move);
float			normalize_angle(float angle);
int				has_wall(int x, int y);
t_cast			horizontal_intersections(t_ray ray);
t_cast			vertical_intersections(t_ray ray);
float			dist(float x1, float x2, float y1, float y2);
void			render3d();
void			sort_sprites();
void			create_strip_height(float tab[], int color);
void			create_strip_wall(float tab[], int offset_x, int n_ray);
void			create_rays();
void			render_mini_map();
void			import_data();
int				finalize(void *s);
int				is_player(char c);
void			get_position_player(char c, int pos_x, int pos_y);
void			get_texture();
void			get_sprite_data(t_sp_cast tmp_sp);
void			create_strip_sprite(float tab[], int num_sp);
void			clear_sprites();
void			clear_rays();
int				ft_perror(const char *s);
int				is_all_elem();
void			reset_elem_conf();
void			import_map();
int				check_arr_space(int i, int j);
void			check_map();
void			fill_map();
void			get_path_texture(char *line);
int				is_path_texture(char *line);
void			resolution(char **ptr);
void			color_flo_cei(char *line);
void			get_args(int argc, char *argv[]);
void			ft_screenshot();
float			colli(float dst);

#endif
