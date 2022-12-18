/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:19:44 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/18 20:53:03 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
#define CANVAS_H

# include 	"tuples.h"

typedef struct s_canvas
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int		bits_per_pixel;
	int 	line_length;
	int		endian;
} t_canvas;


t_canvas *new_canvas(void *mlx, int width, int height);
void write_pixel(t_canvas *canvas, int x, int y, t_tuple *color);

#endif