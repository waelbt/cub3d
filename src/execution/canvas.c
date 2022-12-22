/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:26:19 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/22 03:00:27 by waboutzo         ###   ########.fr       */
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

int convert_color(t_color *color)
{
	return ( color->blue << 0 ) + ( color->green << 8 ) + ( color->red << 16 );
}

void write_pixel(t_canvas *canvas, int x, int y, int color)
{
	char	*dst;

    if (x < 0 || y < 0 || x >= canvas->width
        || y >= canvas->height)
		return ;
	dst = canvas->addr + (y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_player *new_player(int x, int y, char character)
{
    t_player *player;

    player = (t_player *)malloc(sizeof(t_player));
    player->x = x * REC_SIZE;
    player->y = y * REC_SIZE;
    player->radius = 4;
    player->character = character;
    player->turnDirection = 0;
    player->walkDirection = 0;
    if (character == 'N')
        player->rotationAngle = M_PI / 2;
    else if (character == 'S')
        player->rotationAngle = (3 * M_PI )/ 2;
    else if (character == 'E')
        player->rotationAngle = 0;
    else if (character == 'W')
        player->rotationAngle = M_PI;
    player->movespeed = 4.0;
    player->rotationspeed = 2 * (M_PI / 180);
    return player;
}