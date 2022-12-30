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
		return (WE);
	else if (cubscene->rays[x]->ver_hit
		&& cubscene->rays[x]->is_ray_facing_right)
		return (EA);
	else if (!cubscene->rays[x]->ver_hit && cubscene->rays[x]->is_ray_facing_up)
		return (NO);
	return (SO);
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
	if (cubscene->rays[x]->ver_hit)
		x2 = (((int)cubscene->rays[x]->_y
					% cubscene->tx_canvas[w]->width) * k[1]);
	else
		x2 = (((int)cubscene->rays[x]->_x
					% cubscene->tx_canvas[w]->width) * k[1]);
	while (y2 < h)
	{
		y1 = floor(y2 * k[0]);
		write_pixel(cubscene->canvas, x, (y + y2),
			cubscene->tx_canvas[w]->color[y1][x2]);
		y2++;
	}
}
//if (x2 > cubscene->tx_canvas[w]->width)
	//printf(" x2= %d		y1 = %d color= %u\n", x2, y1, cubscene->tx_canvas[w]->color[y1][x2]);

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

	cubscene->player->rotation_angle
		+= cubscene->player->turn_direction * cubscene->player->rotationspeed;
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
