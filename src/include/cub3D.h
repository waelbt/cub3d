/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 01:45:06 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/09 19:02:18 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# define TYPES ((char const*[]){ "NO", "SO", "WE", "EA"})
# define TYPES_SIZE 4
# include   <unistd.h>
# include   <stdlib.h>
# include   <stdarg.h>
# include   <string.h>
# include   <sys/errno.h>
# include   <stdio.h>
# include   <mlx.h>
# include   <fcntl.h>
# include   <math.h>
# include   "libft.h"
# include   "get_next_line.h"
# include   "lexer.h"

#define STDERR 2

typedef struct color
{
    int red;
    int green;
    int blue;
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
} t_texture;

typedef struct cubscene
{
    int counter;
    t_texture *texture;
    t_color *Ceilling;
    t_color *floor;
    char    **map;
    int     map_height;
} t_cubscene;

t_cubscene  *new_cubscene(void);
void        ft_error(char *Raison);

#endif