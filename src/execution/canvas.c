/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:26:19 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/18 20:53:18 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_canvas *new_canvas(void *mlx, int width, int height)
{
    t_canvas *canvas;

    canvas = (t_canvas *)malloc(sizeof(t_canvas));
    canvas->width = width;
    canvas->height = height;
    canvas->img = mlx_new_image(mlx, width, height);
    canvas->addr = mlx_get_data_addr(canvas->img, &canvas->bits_per_pixel, &canvas->line_length, &canvas->endian);
    return (canvas);
}

int convert_color(t_tuple *color)
{
    int r = round(color->x * 255);
    int g = round(color->y * 255);
    int b = round(color->z * 255);

	return ( b << 0 ) + ( g << 8 ) + ( r << 16 );
}

void write_pixel(t_canvas *canvas, int x, int y, t_tuple *color)
{
	char	*dst;

    if (x < 0 || y < 0 || x >= canvas->width
        || y >= canvas->height)
		return ;
	dst = canvas->addr + (y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
	*(unsigned int*)dst = convert_color(color);
}
