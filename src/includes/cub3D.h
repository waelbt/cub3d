/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 01:45:06 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/17 09:11:33 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define    TYPES_SIZE  4
# define    STDERR  2
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
# include	"ray.h"
# include 	"tuples.h"



typedef struct color
{
	int	red;
	int	green;
	int	blue;
}t_color;

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
}	t_texture;

typedef struct cubscene
{
	int			counter;
	t_texture	*texture;
	t_color		*ceilling;
	t_color		*floor; 
	char		**map;
	int			map_height;
}	t_cubscene;

t_cubscene	*new_cubscene(void);
void		ft_error(char *Raison);
void		ft_free(char **str);
void		check_undefined_elements(char *str, int *counter);
void		horizontal_walls(char *str);
void		hard_code_time(t_cubscene *cubscene);
int			extension_check(char *file);
int			color_check(char *str);
void		add_lines(t_cubscene *cubscene, char *str);
void		check_map(t_cubscene *cubscene);
void		parsing(int fd, t_cubscene *cubscene);

#endif