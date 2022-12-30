/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:56:14 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/29 17:45:58 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_dir(t_cubscene *cubscene, int x)
{
	if (cubscene->rays[x]->ver_hit && cubscene->rays[x]->is_ray_facing_left)
		return (2);
	else if (cubscene->rays[x]->ver_hit
		&& cubscene->rays[x]->is_ray_facing_right)
		return (3);
	else if (!cubscene->rays[x]->ver_hit && cubscene->rays[x]->is_ray_facing_up)
		return (0);
	return (1);
}

void	rec(t_cubscene *cubscene, int x, int y, int h)
{
	int		j[2];
	int		z = get_dir(cubscene, x);
	double	k = ((float)cubscene->tx_canvas[z]->height / h);
	double	k2 = ((float)cubscene->tx_canvas[z]->width / REC_SIZE);
	int		x2;
	
	j[0] = 0;
	if (cubscene->rays[x]->ver_hit)
		x2 = (((int)cubscene->rays[x]->_y % cubscene->tx_canvas[z]->width) * k2);
	else 
		x2 = (((int)cubscene->rays[x]->_x % cubscene->tx_canvas[z]->width) * k2);	

	while (j[0] < h)
	{
		int y1 = floor(j[0] * k);
		write_pixel(cubscene->canvas, x, (y + j[0]) , cubscene->tx_canvas[z]->color[y1][x2]);
	 // if (x2 > cubscene->tx_canvas[z]->width)
	 //			printf(" x2= %d		y1 = %d color= %u\n", x2, y1, cubscene->tx_canvas[z]->color[y1][x2]);
		j[0]++;
	}
}

//static double tan = 0.577350269189626; // tan(FIELD_OF_ANGLE_2)
void	projectewalls(t_cubscene *cubscene)
{
	double	distance_projection_plane;
	double	wall_strip_height;
	double	distance;
	int		i;

	i = -1;
	while (++i < cubscene->_width)
	{
		distance = cubscene->rays[i]->distance
			* cos(cubscene->rays[i]->angle - cubscene->player->rotation_angle);
		distance_projection_plane = cubscene->half_width / 0.577350269189626;
		wall_strip_height = (REC_SIZE / distance) * distance_projection_plane;
		rec(cubscene, i, cubscene->half_height
			- (wall_strip_height / 2), wall_strip_height);
	}
}

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
	int		i;
	int		steps;
	float	xinc;
	float	yinc;
	float	tmpx;
	float	tmpy;

	i = -1;
	dx = x * scale - cubscene->player->x * scale;
	dy = y * scale - cubscene->player->y * scale;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	xinc = dx / (float) steps;
	yinc = dy / (float) steps;
	tmpx = cubscene->player->x * scale;
	tmpy = cubscene->player->y * scale;
	while (++i <= steps)
	{
		write_pixel(cubscene->canvas, tmpx, tmpy, RED);
		tmpx += xinc;
		tmpy += yinc;
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

int	has_wall_at(t_cubscene *cubscene, double x, double y)
{
	int	i;
	int	j;

	i = x / REC_SIZE;
	j = y / REC_SIZE;
	if (x < 0 || y < 0 || y >= cubscene->_height
		|| x >= cubscene->_width || i >= (int) ft_strlen(cubscene->map[j]))
		return (1);
	if (cubscene->map[j][i] == '1')
		return (1);
	return (0);
}

void	update_player(t_cubscene *cubscene)
{
	int	movesptep;
	int	newplayerx[3];
	int	newplayery[3];

	cubscene->player->rotation_angle += cubscene->player->turn_direction * cubscene->player->rotationspeed;
	movesptep = cubscene->player->walk_direction * cubscene->player->movespeed;
	newplayerx[0] = movesptep;
	newplayery[0] = movesptep;
	 if (cubscene->player->walk_direction != 0)
	{
		if (cubscene->player->flag)
		{
		newplayerx[0] *= cos(cubscene->player->rotation_angle - M_PI / 2);
			newplayery[0] *= sin(cubscene->player->rotation_angle - M_PI / 2);
		}
		else
		{
			newplayerx[0] *= cos(cubscene->player->rotation_angle);
			newplayery[0] *= sin(cubscene->player->rotation_angle);
		}
	}
	newplayerx[0] += cubscene->player->x;
	newplayery[0] += cubscene->player->y;
	newplayerx[1] = newplayerx[0] + cubscene->player->radius;
	newplayerx[2] = newplayerx[0] - cubscene->player->radius;
	newplayery[1] = newplayery[0] + cubscene->player->radius;
	newplayery[2] = newplayery[0] - cubscene->player->radius;
	if (!has_wall_at(cubscene, newplayerx[1], newplayery[1])
		&& !has_wall_at(cubscene, newplayerx[2], newplayery[2])
		&& !has_wall_at(cubscene, newplayerx[1], newplayery[2])
		&& !has_wall_at(cubscene, newplayerx[2], newplayery[1]))
	{
		cubscene->player->x = newplayerx[0];
		cubscene->player->y = newplayery[0];
	}
}
