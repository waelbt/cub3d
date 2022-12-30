/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:26:24 by lchokri           #+#    #+#             */
/*   Updated: 2022/12/30 13:26:28 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	*hor_intersection(t_cubscene *cubscene, int index)
{
	double	intercept[2];
	double	step[2];
	double	next_horz_touch[2];
	double	*hit;
	double	x;
	double	tan_ray_angle;

	hit = malloc(sizeof(double) * 3);
	tan_ray_angle = 1 / tan(cubscene->rays[index]->angle);
	hit[HIT_STAT] = 0;
	intercept[Y] = ((int)(cubscene->player->y / REC_SIZE)) * REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_down)
		intercept[Y] += REC_SIZE;
	intercept[X] = cubscene->player->x + (intercept[Y]
			- cubscene->player->y) * tan_ray_angle;
	step[Y] = REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_up)
		step[Y] *= -1;
	step[X] = REC_SIZE * tan_ray_angle;
	if (cubscene->rays[index]->is_ray_facing_left && step[X] > 0)
		step[X] *= -1;
	if (cubscene->rays[index]->is_ray_facing_right && step[X] < 0)
		step[X] *= -1;
	next_horz_touch[X] = intercept[X];
	next_horz_touch[Y] = intercept[Y];
	while (next_horz_touch[X] >= 0 && next_horz_touch[X] <= cubscene->_width
		&& next_horz_touch[Y] >= 0 && next_horz_touch[Y] <= cubscene->_height)
	{
		x = 0;
		if (cubscene->rays[index]->is_ray_facing_up)
			x = 1;
		if (has_wall_at(cubscene, next_horz_touch[X], next_horz_touch[Y] - x))
		{
			hit[HIT_STAT] = 1;
			hit[X] = next_horz_touch[X];
			hit[Y] = next_horz_touch[Y];
			break ;
		}
		next_horz_touch[X] += step[X];
		next_horz_touch[Y] += step[Y];
	}
	return (hit);
}

double	*ver_intersection(t_cubscene *cubscene, int index)
{
	double	intercept[2];
	double	step[2];
	double	nextvertouch[2];
	double	*hit;
	double	x;
	double	tan_ray_angle;

	hit = malloc(sizeof(double) * 3);
	tan_ray_angle = tan(cubscene->rays[index]->angle);
	hit[HIT_STAT] = 0;
	intercept[X] = ((int)(cubscene->player->x / REC_SIZE)) * REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_right)
		intercept[X] += REC_SIZE;
	intercept[Y] = cubscene->player->y + (intercept[X]
			- cubscene->player->x) * tan_ray_angle;
	step[X] = REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_left)
		step[X] *= -1;
	step[Y] = REC_SIZE * tan_ray_angle;
	if (cubscene->rays[index]->is_ray_facing_up && step[Y] > 0)
		step[Y] *= -1;
	if (cubscene->rays[index]->is_ray_facing_down && step[Y] < 0)
		step[Y] *= -1;
	nextvertouch[X] = intercept[X];
	nextvertouch[Y] = intercept[Y];
	while (nextvertouch[X] >= 0 && nextvertouch[X] <= cubscene->_width
		&& nextvertouch[Y] >= 0 && nextvertouch[Y] <= cubscene->_height)
	{
		x = 0;
		if (cubscene->rays[index]->is_ray_facing_left)
			x = 1;
		if (has_wall_at(cubscene, nextvertouch[X] - x, nextvertouch[Y]))
		{
			hit[HIT_STAT] = 1;
			hit[X] = nextvertouch[X];
			hit[Y] = nextvertouch[Y];
			break ;
		}
		else
		{
			nextvertouch[X] += step[X];
			nextvertouch[Y] += step[Y];
		}
	}
	return (hit);
}