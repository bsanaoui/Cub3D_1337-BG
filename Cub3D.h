/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:38:31 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/12/18 17:40:24 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Cub3D_H
# define Cub3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line.h"
# include "mlx.h"
# include <stdio.h>


#define MINIMAP_SCALE_FACTOR 0.3
#define	COLOR_PLAYER 16711680
#define	RAY_COLOR 16776960
#define	MAP_COLOR 3093151
#define	SPRITE_COLOR 14557865

float	ROTATION_SPEED;
float	MOVE_SPEED;
int		TILE_SIZE;
int		TILE_SIZE_P;
int 	WALL_COLOR;
int 	FLOOR_COLOR;
int 	CEIL_COLOR;
int		size_line_texture;
int 	TEX_WIDTH;
int 	TEX_HEIGHT;
int		n_rays;
int		wall_strip_width;
int		count_sprite;
int		n_sp;
int		newline;

typedef struct vector
{
	double	x;
	double	y;
} t_vector;

typedef struct map
{
	char	*ptr;
	char	**map;
	int		w;
	int		h;
} t_map;

typedef struct img
{
	void 	*img;
	int		h;
	int		w;
	int		*data;
} t_img ;

typedef struct mlx_var
{
	void 	*ptr;
	void	*win;
	int		WIN_H;
	int		WIN_W;
} T_MLX_VAR ;

typedef struct player
{
	double 	x;
	double 	y;
	int		turnDirection; // -1 if left , +1 if right
	int		walkDirection;
	double	Angle;
	float	rotationSpeed; // how many frames/second it will rotate
	double 	fov;
} T_PLAYER ;

typedef struct wallHit
{
	double		X;
	double		Y;
} T_WALLHIT ;

typedef struct rays
{
	double 		rayAngle;
	double		distance;
	int			was_hit_vertical;
	T_WALLHIT 	wallHit;
	int			isRayFacingDown;
	int			isRayFacingUp;
	int			isRayFacingRight;
	int			isRayFacingLeft;
} T_RAYS ;

typedef	struct sprite_cast
{
	int			hit_horz;
	int			hit_vert;
	double		hit_x;
	double		hit_y;
	double		distance;
	int			index_x;
	int			index_y;

} T_SPRITE_CAST;

typedef struct cast
{
	double			xinterept;
	double			yinterept;
	double			xstep;
	double			ystep;
	double			nextTouchX;
	double			nextTouchY;
	double			wallHitX;
	double			wallHitY;
	double			distance;
	int 			foundHorzWallHit;
	int 			foundVertWallHit;
	int				minusY;
	int				minusX;
	T_SPRITE_CAST	*sprite;
	int				i_sp;

} T_CAST ;

typedef struct ray
{
	double	rayAngle;
	int		isRayFacingDown;
	int		isRayFacingUp;
	int		isRayFacingRight;
	int		isRayFacingLeft;
} T_RAY ;

typedef struct sprite
{
	double	x;
	double	y;
	int		index_x;
	int		index_y;
	double	distance;
	int		num_ray;
	double	angle;
} T_SPRITE;

typedef struct texture_sp
{
	char	*path;
	int		*data_tex;
	int		w;
	int		h;
	int		size_line_texture_sp;
} t_texture_sp;

typedef struct texture
{
	char	*path;
	void	*img;
	int		*data;
	int		w;
	int		h;
	int		size_line;
} t_texture;

typedef struct is_set_el
{
	int	resolu;
	int	text_no;
	int	text_so;
	int	text_we;
	int	text_ea;
	int	sprite;
	int	color_f;
	int	color_c;
	int	player;

} t_is_set_el;

t_map				m;
T_MLX_VAR			mlx;
t_img				map_img;
t_img				player_img;
t_img				project_3d;
T_PLAYER			player;
T_RAYS				*rays;
T_SPRITE			*sprites;
t_texture_sp		texture_sp;
t_is_set_el			is_set;
t_texture			text_no;
t_texture			text_so;
t_texture			text_we;
t_texture			text_ea;
int					keys[7];

void		ft_putchar(char c);
void		ft_putnbr(int nb);
int			ft_atoi(char *str, int *len);
int			ft_isdigit(int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
char		**ft_split(char const *s, char c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
int			update();
int			key_press(int key);
int			key_release(int key);
void		move_player(int key);
void		create_2d_map(void);
void		create_grid(int i, int j);
void		create_player2d();
void		display_player();
void		line(int x0, int y0, int x1, int y1);
void		put_pixel_in_img(t_img s_img, int x, int y, int color);
void		ray();
int			is_wall(int walkDirection, int kindMove);
float		normalizeAngle(float angle);
int			hasWallAt(int x, int y);
void		cast_ray(T_RAY ray, int ray_count);
T_CAST		horizontal_intersections(T_RAY ray);
T_CAST		vertical_intersections(T_RAY ray);
float		distance(float x1, float x2, float y1, float y2);
void		render3DProjectedWalls();
void		create_strip_height(float tab[], int color); //tab[] = {float x, float y, float width, float height}
void		create_strip_wall(float tab[], int offset_x, int n_ray);
void		create_rays();
void		render_mini_map();
void		import_data();
int			finalize(void *s);
int     	is_player(char c);
void    	get_position_player(char c, int pos_x, int pos_y);
void        get_texture();
void		render_sprites();
void    	get_sprite_data(T_SPRITE_CAST tmp_sp);
void    	clear_sprites();
void	    clear_rays();
void		import_map();
void    	fill_map();
int			ft_perror(const char *s);
int    		is_all_elem();
void		reset_elem_conf();
int			is_line_empty(char *line);

#endif