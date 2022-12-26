/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 01:45:06 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/26 15:39:54 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include   <unistd.h>
# include   <stdlib.h>
# include   <stdarg.h>
# include	<stdbool.h>
# include   <string.h>
# include   <sys/errno.h>
# include   <stdio.h>
# include   <mlx.h>
# include   <fcntl.h>
# include	<math.h>
# include	<float.h>
# include   "libft.h"
# include   "get_next_line.h"
# include   "lexer.h"
# include	"canvas.h"

# define    STDERR  			2
# define	REC_SIZE 			60
# define 	RED 				16711680
# define 	YELLOW 				50000000
# define	UP					13
# define 	DOWN				1
# define    LEFT				0
# define 	RIGHT				2
# define	UP_ARROW			126
# define 	DOWN_ARROW			125
# define    LEFT_ARROW			123
# define 	RIGHT_ARROW			124
# define	FIELD_OF_ANGLE		M_PI / 3
# define	FIELD_OF_ANGLE_2	FIELD_OF_ANGLE / 2
# define 	CENTER				REC_SIZE / 2
# define	X					0
# define 	Y					1
# define 	HIT_STAT			2
# define	SCALE				0.2

typedef struct color
{
	int	red;
	int	green;
	int	blue;
}t_color;

typedef struct player
{
	int x;
	int y;
	int radius;
	int character;
	int turnDirection;
	int walkDirection;
	double rotationAngle;
	double movespeed;
	double rotationspeed;
}t_player;

typedef struct ray
{
	double angle;
	double _x;
	double _y;
	double distance;
	bool is_ray_facing_down;
	bool is_ray_facing_up;
	bool is_ray_facing_right;
	bool is_ray_facing_left;
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
	char	**path;
	void		*north_image;
	void		*west_image;
	void		*east_image;
	void		*south_image;
}	t_texture;

typedef struct cubscene
{
	void		*mlx;
	void		*win;
	t_canvas	*canvas;
	t_rays		**rays;
	int 		counter;
	//int 		rays_number;
	t_player	*player;
	t_texture	*texture;
	int			ceilling;
	int			floor; 
	char		**map;
	t_canvas	*no_canvas;
	t_canvas	*we_canvas;
	t_canvas	*ea_canvas;
	t_canvas	*so_canvas;
	int			map_height;
	int 		frame_rate;
	int			_height;
	int			_width;
	int			half_height;
	int			half_width;
	int			map_width; //temp
}	t_cubscene;


t_cubscene	*new_cubscene(void);
void		ft_error(char *Raison);
void		ft_free(char **str);
void		check_undefined_elements(t_cubscene *cubscene, char *str, int *counter, int y, int x);
void		horizontal_walls(char *str);
void		hard_code_time(t_cubscene *cubscene);
int			extension_check(char *file);
int			color_check(char *str);
void		add_lines(t_cubscene *cubscene, char *str);
void		check_map(t_cubscene *cubscene);
void		parsing(int fd, t_cubscene *cubscene);

void 		mini_rec(t_canvas *canvas, int x, int y, int color);
t_player	*new_player(int x, int y, char character);
void		render_player(t_cubscene *cubscene, int color);
void		update_player(t_cubscene *cubscene);
void		line(t_cubscene *cubscene, int x, int y, int color, double scale);
void		ray_render(t_cubscene *cubscene, int index);
t_rays *new_ray(double angle, t_cubscene *cubscene);
void		cast_all_rays(t_cubscene *cubscene);
void		ft_free_rays(t_cubscene *cubscene);
int			hasWallAt(t_cubscene *cubscene, double x, double y);
void		projectewalls(t_cubscene* cubscene);
void		rec(t_canvas *canvas, int x, int y, int w, int h, int color);
void		texture_init(t_cubscene *cubscene);
unsigned int get_color_from_img(t_canvas *canvas, int x, int y);
#endif