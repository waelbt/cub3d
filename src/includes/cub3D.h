/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 01:45:06 by waboutzo          #+#    #+#             */
/*   Updated: 2023/01/01 15:22:57 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdarg.h>
# include	<stdbool.h>
# include	<string.h>
# include	<sys/errno.h>
# include	<stdio.h>
# include	<mlx.h>
# include	<fcntl.h>
# include	<math.h>
# include	<limits.h>
# include	<float.h>
# include	"libft.h"
# include	"get_next_line.h"
# include	"lexer.h"

# define STDERR  			2
# define REC_SIZE 			32
# define RED 				16711680
# define UP					13
# define DOWN				1
# define LEFT				0
# define RIGHT				2
# define UP_ARROW			126
# define DOWN_ARROW			125
# define LEFT_ARROW			123
# define RIGHT_ARROW		124
# define FIELD_OF_ANGLE		1.047197551196598
# define FIELD_OF_ANGLE_2	0.523598775598299
# define CENTER				16
# define X					0
# define Y					1
# define HIT_STAT			2
# define SCALE				0.2
# define HEIGHT				720
# define WIDTH				1080
# define HEIGHT_2			360.0
# define WIDTH_2			540.0

typedef struct color
{
	int	red;
	int	green;
	int	blue;
}t_color;

typedef struct player
{
	int		x;
	int		y;
	int		radius;
	int		character;
	int		flag;
	int		turn_direction;
	int		walk_direction;
	double	rotation_angle;
	double	movespeed;
	double	rotationspeed;
}t_player;

typedef struct ray
{
	double	angle;
	double	_x;
	double	_y;
	double	distance;
	bool	is_ray_facing_down;
	bool	is_ray_facing_up;
	bool	is_ray_facing_right;
	bool	is_ray_facing_left;
	bool	ver_hit;
}t_rays;

typedef struct texture
{
	enum
	{
		NO,
		SO,
		WE,
		EA
	} e_type;
	char		**path;
	void		*north;
	void		*west;
	void		*east;
	void		*south;
	int			tx_width;
	int			tx_height;
}	t_texture;

typedef struct s_canvas
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	unsigned int	**color;
	double			scale;
}	t_canvas;

typedef struct cubscene
{
	void		*mlx;
	void		*win;
	t_canvas	*canvas;
	t_rays		**rays;
	t_player	*player;
	t_texture	*texture;
	int			ceilling;
	int			floor;
	int			counter;
	char		**map;
	t_canvas	**tx_canvas;
	int			map_height;
	int			frame_rate;
	int			map_width;
}	t_cubscene;

t_canvas		*new_canvas(void *img, int width, int height);
int				convert_color(t_color *color);
void			write_pixel(t_canvas *canvas, int x, int y, unsigned int color);
t_cubscene		*new_cubscene(void);
void			ft_error(char *Raison);
void			ft_free(char **str);
void			undefined_elem(t_cubscene *cubscene, char *str, int y, int x);
void			horizontal_walls(char *str);
void			hard_code_time(t_cubscene *cubscene);
int				extension_check(char *file);
int				color_check(char *str);
void			add_lines(t_cubscene *cubscene, char *str);
void			check_map(t_cubscene *cubscene);
void			parsing(int fd, t_cubscene *cubscene);
void			mini_rec(t_canvas *canvas, int x, int y, int color);
t_player		*new_player(int x, int y, char character);
void			render_player(t_cubscene *cubscene, int color);
void			update_player(t_cubscene *cubscene);
void			line(t_cubscene *cubscene, int x, int y, double scale);
void			ray_render(t_cubscene *cubscene, int index);
void			new_ray(double angle, t_cubscene *cubscene, int index);
void			cast_all_rays(t_cubscene *cubscene);
void			ft_free_rays(t_cubscene *cubscene);
int				has_wall_at(t_cubscene *cubscene, double x, double y);
void			projectewall(t_cubscene *cubscene, int i);
void			rec(t_cubscene *cubscene, int x, int y, int h);
void			texture_init(t_cubscene *cubscene);
unsigned int	get_color_from_img(t_canvas *canvas, int x, int y);
int				key_release(int keycode, t_cubscene *cubscene);
int				key_handler(int keycode, t_cubscene *cubscene);
int				close_x(void);
int				posi(char *str);
void			playercnr(t_cubscene *cubscene, size_t i, size_t j, size_t len);
void			corners(t_cubscene *cubscene, size_t i, size_t j, size_t len);
int				corners_check(char c);
void			hor(t_cubscene *cubscene, int index, double *hit, double tan);
void			ver(t_cubscene *cubscene, int index, double *hit, double tan);
void			intersection(t_cubscene *cubscene, int index, double tan_angle);
double			distance(t_cubscene *cubscene, int index, double x2, double y2);
int				get_dir(t_cubscene *cubscene, int x);
#endif