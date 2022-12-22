/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:56:14 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/22 04:25:06 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void rec(t_canvas *canvas, int x, int y, t_color *color)
{
	int i;
	int j;

	j = -1;
	while(++j < REC_SIZE)
	{
		i = -1;
		while(++i < REC_SIZE)
		{
			if (i == 0 || i == REC_SIZE - 1 || j == REC_SIZE -1 || j == 0)
				write_pixel(canvas, i + (x * REC_SIZE), j + (y * REC_SIZE), 0);
			else
				write_pixel(canvas, i + (x * REC_SIZE), j + (y * REC_SIZE), convert_color(color));
		}
	}
}

void line(t_cubscene *cubscene, int x, int y, int color)
{
	int dx;
	int dy;
	int i;
	int steps;
	float xinc;
	float yinc;
	float tmpx;
	float tmpy;
	int center;

	i = -1;
	center = REC_SIZE / 2;
	dx = x - cubscene->player->x;
	dy = y - cubscene->player->y;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	xinc = dx / (float) steps;
	yinc = dy / (float) steps;
	tmpx = cubscene->player->x + center;
	tmpy = cubscene->player->y + center;
	while (++i <= steps)
	{
		write_pixel(cubscene->canvas, tmpx, tmpy, color);
		tmpx += xinc;
		tmpy += yinc;
	}
}

void render_player(t_cubscene *cubscene,int color)
{
	int i;
	int j;
	int point_x;
	int point_y;
	int center;
	int radius;
	
	j = -1;
	center = REC_SIZE / 2;
	radius = cubscene->player->radius;
	while(radius > 0)
	{
		i = -1;
		while(++i < 360)
		{
			point_x = center + radius * cos(i);
			point_y = center + radius * sin(i);
			write_pixel(cubscene->canvas, point_x + (cubscene->player->x),
			point_y + (cubscene->player->y), color);
		}
		radius--;
	}
}

int hasWallAt(t_cubscene *cubscene, int x, int y)
{
	int i;
	int j;

	i = roundf((double)x / REC_SIZE);
	j = roundf((double)y / REC_SIZE);
	if (x < 0 || y < 0 || y >= cubscene->_height
		|| x >= cubscene->_width || i >= (int) ft_strlen(cubscene->map[j]))
		return (1);
	if (cubscene->map[j][i] == '1')
		return (1);
	return (0);
}

void update_player(t_cubscene *cubscene)
{
	int movesptep;
    int newplayerx[3];
    int newplayery[3];

	cubscene->player->rotationAngle += cubscene->player->turnDirection * cubscene->player->rotationspeed;
	movesptep = cubscene->player->walkDirection * cubscene->player->movespeed;
	newplayerx[0] = movesptep;
	newplayery[0] = movesptep;
	if (cubscene->player->walkDirection != 0)
	{
		newplayerx[0] *= cos(cubscene->player->rotationAngle);
		newplayery[0] *= sin(cubscene->player->rotationAngle);
	}
	newplayerx[0] += cubscene->player->x;
	newplayery[0] += cubscene->player->y;
	newplayerx[1] = newplayerx[0] + cubscene->player->radius;
	newplayerx[2] =  newplayerx[0] - cubscene->player->radius;
	newplayery[1] = newplayery[0] + cubscene->player->radius;
	newplayery[2] =  newplayery[0] - cubscene->player->radius;
    if (!hasWallAt(cubscene, newplayerx[1], newplayery[1])
		&& !hasWallAt(cubscene, newplayerx[2], newplayery[2])
		&& !hasWallAt(cubscene, newplayerx[1], newplayery[2])
		&& !hasWallAt(cubscene, newplayerx[2],newplayery[1]))
	{
    	cubscene->player->x = newplayerx[0];
		cubscene->player->y = newplayery[0];
    }
}
