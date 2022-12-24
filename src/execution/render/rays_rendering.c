/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 04:00:18 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/23 21:49:25 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_rays *new_ray(double angle, t_cubscene *cubscene)
{
	t_rays *ray;

	ray = (t_rays *) malloc(sizeof(t_rays));
	ray->angle = fmod(angle, (2 * M_PI));
	if(ray->angle < 0){
		ray->angle += 2 * M_PI;
	}
	ray->_x = cubscene->player->x;
	ray->_y = cubscene->player->y;
	/*laila kalt khassna ndiro lpostion deyal player fe blasst 0 0 */
	ray->distance = 0;
	ray->is_ray_facing_down = ((ray->angle >= 0) && (ray->angle <= M_PI));
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ((ray->angle <= 0.5 * M_PI) || (ray->angle >= 1.5 * M_PI));
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
	return ray;
}

void ray_render(t_cubscene *cubscene, int index)
{
	line(cubscene, cubscene->rays[index]->_x, cubscene->rays[index]->_y, YELLOW);
}

double *hor_intersection(t_cubscene *cubscene, int index)
{
	double intercept[2];
	double step[2];
	double nextHorzTouch[2];
	double *hit;
	int		a;

	a = 0;
	hit = malloc(sizeof(double) * 3);
	hit[HIT_STAT] = 0;
	intercept[Y] = floor(cubscene->player->y / REC_SIZE) * REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_down)
		intercept[Y] += REC_SIZE;
	intercept[X] = cubscene->player->x + (intercept[Y] - cubscene->player->y) / tan(cubscene->rays[index]->angle);
	step[Y] = REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_up)
		step[Y] *= -1;
	step[X] = REC_SIZE / tan(cubscene->rays[index]->angle);
	if (cubscene->rays[index]->is_ray_facing_left && step[X] > 0)
		step[X] *= -1;
	if (cubscene->rays[index]->is_ray_facing_right && step[X] < 0)
		step[X] *= -1;
	nextHorzTouch[X] = intercept[X];
	nextHorzTouch[Y] = intercept[Y];
	while (nextHorzTouch[X] >= 0 && nextHorzTouch[X] <= cubscene->_width
		&& nextHorzTouch[Y] >= 0 && nextHorzTouch[Y] <= cubscene->_height)
	{
		a = 0;
		if (cubscene->rays[index]->is_ray_facing_up)
			a = 1;
		if (hasWallAt(cubscene, nextHorzTouch[X], nextHorzTouch[Y] - a))
		{
			hit[HIT_STAT] = 1;
			hit[X] =  nextHorzTouch[X];
			hit[Y] =  nextHorzTouch[Y];
			break;
		}
		nextHorzTouch[X] += step[X];
		nextHorzTouch[Y] += step[Y];
	}
	return hit;
}



double *ver_intersection(t_cubscene *cubscene, int index)
{
	double intercept[2];
	double step[2];
	double nextverTouch[2];
	double *hit;
	int		a;

	a = 0;
	hit = malloc(sizeof(double) * 3);
	hit[HIT_STAT] = 0;
	intercept[X] = floor(cubscene->player->x / REC_SIZE) * REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_right)
		intercept[X] += REC_SIZE;
	intercept[Y] = cubscene->player->y + (intercept[X] - cubscene->player->x) * tan(cubscene->rays[index]->angle);
	step[X] = REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_left)
		step[X] *= -1;
	step[Y] = REC_SIZE * tan(cubscene->rays[index]->angle);
	if (cubscene->rays[index]->is_ray_facing_up && step[Y] > 0)
		step[Y] *= -1;
	if (cubscene->rays[index]->is_ray_facing_down && step[Y] < 0)
		step[Y] *= -1;
	nextverTouch[X] = intercept[X];
	nextverTouch[Y] = intercept[Y];
	while (nextverTouch[X] >= 0 && nextverTouch[X] <= cubscene->_width
		&& nextverTouch[Y] >= 0 && nextverTouch[Y] <= cubscene->_height)
	{
		a = 0;
		if (cubscene->rays[index]->is_ray_facing_left)
			a = 1;
		if (hasWallAt(cubscene, nextverTouch[X] - a, nextverTouch[Y]))
		{
			hit[HIT_STAT] = 1;
			hit[X] =  nextverTouch[X];
			hit[Y] =  nextverTouch[Y];
			break;
		}
		else
		{
			nextverTouch[X] += step[X];
			nextverTouch[Y] += step[Y];
		}
	}
	return hit;
}

#include <limits.h>

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
void intersection(t_cubscene *cubscene, int index)
{
	double *horz_hit;
	double *ver_hit;
	double horzditance = INT_MAX;
	double verditance = INT_MAX;

	horz_hit = hor_intersection(cubscene, index);
	ver_hit = ver_intersection(cubscene, index);
	if (horz_hit[HIT_STAT])
		horzditance = distance(cubscene->player->x, cubscene->player->y
		, horz_hit[X], horz_hit[Y]);
	if (ver_hit[HIT_STAT])
		verditance = distance(cubscene->player->x, cubscene->player->y
		, ver_hit[X], ver_hit[Y]);
	if (verditance < horzditance)
	{
		cubscene->rays[index]->_x = ver_hit[X];
		cubscene->rays[index]->_y = ver_hit[Y];
	}
	else
	{
		cubscene->rays[index]->_x = horz_hit[X];
		cubscene->rays[index]->_y = horz_hit[Y];
	}
}

void cast_all_rays(t_cubscene *cubscene)
{
	int column_id;
	double rayAngle;

	column_id = 0;
	cubscene->rays = (t_rays **) malloc(sizeof(t_rays) * cubscene->_width);
	rayAngle = cubscene->player->rotationAngle - (FIELD_OF_ANGLE / 2);
	
	while (column_id < cubscene->_width)
	{
		cubscene->rays[column_id] = new_ray(rayAngle, cubscene);
		intersection(cubscene, column_id);
		rayAngle += FIELD_OF_ANGLE / cubscene->_width;
		column_id++;
	}
}

void ft_free_rays(t_cubscene *cubscene)
{
	int i;

	i = -1;
	while(++i < cubscene->_width)
		free(cubscene->rays[i]);
	free(cubscene->rays);
}