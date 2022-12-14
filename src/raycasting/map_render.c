/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:56:14 by waboutzo          #+#    #+#             */
/*   Updated: 2023/01/01 16:02:29 by waboutzo         ###   ########.fr       */
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

//distance_projection_plane = WIDTH_2 / tan(FIELD_OF_ANGLE_2);
void	projectewall(t_cubscene *cubscene, int i)
{
	double	wall_strip_height;
	double	distance;

	distance = cubscene->rays[i]->distance
		* cos(cubscene->rays[i]->angle - cubscene->player->rotation_angle);
	wall_strip_height = (REC_SIZE / distance) * 935.3074360871934;
	rec(cubscene, i, HEIGHT_2
		- (wall_strip_height / 2), wall_strip_height);
}

int	has_wall_at(t_cubscene *cubscene, double x, double y)
{
	int	i;
	int	j;

	i = x / REC_SIZE;
	j = y / REC_SIZE;
	if (x < 0 || y < 0 || y >= cubscene->map_height
		|| x >= cubscene->map_width || i >= (int) ft_strlen(cubscene->map[j]))
		return (1);
	if (cubscene->map[j][i] == '1')
		return (1);
	return (0);
}

void	update_player_pos(t_cubscene *cubscene, int *newx, int *newy)
{
	newx[0] += cubscene->player->x;
	newy[0] += cubscene->player->y;
	newx[1] = newx[0] + cubscene->player->radius;
	newx[2] = newx[0] - cubscene->player->radius;
	newy[1] = newy[0] + cubscene->player->radius;
	newy[2] = newy[0] - cubscene->player->radius;
	if (!has_wall_at(cubscene, newx[1], newy[1])
		&& !has_wall_at(cubscene, newx[2], newy[2])
		&& !has_wall_at(cubscene, newx[1], newy[2])
		&& !has_wall_at(cubscene, newx[2], newy[1]))
	{
		cubscene->player->x = newx[0];
		cubscene->player->y = newy[0];
	}
}

void	update_player(t_cubscene *cubscene)
{
	int		movesptep;
	int		newplayerx[3];
	int		newplayery[3];
	double	angle;

	cubscene->player->rotation_angle
		+= cubscene->player->turn_direction * cubscene->player->rotationspeed;
	movesptep = cubscene->player->walk_direction * cubscene->player->movespeed;
	newplayerx[0] = movesptep;
	newplayery[0] = movesptep;
	if (cubscene->player->walk_direction != 0)
	{
		if (cubscene->player->flag)
		{
			angle = cubscene->player->rotation_angle - M_PI_2;
			newplayerx[0] *= cos(angle);
			newplayery[0] *= sin(angle);
		}
		else
		{
			newplayerx[0] *= cos(cubscene->player->rotation_angle);
			newplayery[0] *= sin(cubscene->player->rotation_angle);
		}
	}
	update_player_pos(cubscene, newplayerx, newplayery);
}
