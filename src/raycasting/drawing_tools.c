/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:51:31 by lchokri           #+#    #+#             */
/*   Updated: 2022/12/30 15:51:36 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	mini_rec(t_canvas *canvas, int x, int y, int color)
{
	int	i;
	int	j;

	j = -1;
	while (++j < REC_SIZE)
	{
		i = -1;
		while (++i < REC_SIZE)
			write_pixel(canvas, (i + (x * REC_SIZE)) * SCALE,
				(j + (y * REC_SIZE)) * SCALE, color);
	}
}

void	line(t_cubscene *cubscene, int x, int y, double scale)
{
	int		dx;
	int		dy;
	int		steps;
	float	tmpx;
	float	tmpy;

	dx = x * scale - cubscene->player->x * scale;
	dy = y * scale - cubscene->player->y * scale;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	dx = dx / (float) steps;
	dy = dy / (float) steps;
	tmpx = cubscene->player->x * scale;
	tmpy = cubscene->player->y * scale;
	while (steps)
	{
		write_pixel(cubscene->canvas, tmpx, tmpy, RED);
		tmpx += dx;
		tmpy += dy;
		steps--;
	}
}

void	render_player(t_cubscene *cubscene, int color)
{
	int		i;
	int		j;
	int		point_x;
	int		point_y;
	int		radius;

	j = -1;
	radius = cubscene->player->radius;
	while (radius > 0)
	{
		i = -1;
		while (++i < 360)
		{
			point_x = radius * cos(i) * SCALE;
			point_y = radius * sin(i) * SCALE;
			write_pixel(cubscene->canvas, point_x
				+ (cubscene->player->x * SCALE),
				point_y + (cubscene->player->y * SCALE), color);
		}
		radius--;
	}
}

void	rec(t_cubscene *cubscene, int x, int y, int h)
{
	int		x2;
	int		y1;
	int		y2;
	int		w;
	double	k[2];

	y2 = 0;
	w = get_dir(cubscene, x);
	k[0] = ((float)cubscene->tx_canvas[w]->height / h);
	k[1] = ((float)cubscene->tx_canvas[w]->width / REC_SIZE);
	x2 = (int)(cubscene->rays[x]->_x * k[1]) % cubscene->tx_canvas[w]->width;
	if (cubscene->rays[x]->ver_hit)
		x2 = (int)(cubscene->rays[x]->_y * k[1])
			% cubscene->tx_canvas[w]->width;
	while (y2 < h)
	{
		y1 = floor(y2 * k[0]);
		write_pixel(cubscene->canvas, x, (y + y2),
			cubscene->tx_canvas[w]->color[y1][x2]);
		y2++;
	}
}
