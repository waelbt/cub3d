/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:19:44 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/26 15:38:03 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "cub3D.h"

typedef struct color	t_color;

typedef struct s_canvas
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_canvas;

t_canvas	*new_canvas(void *img, int width, int height);
int			convert_color(t_color *color);
void		write_pixel(t_canvas *canvas, int x, int y, unsigned int color);
#endif