/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:26:24 by lchokri           #+#    #+#             */
/*   Updated: 2022/12/31 12:17:08 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	hor(t_cubscene *cubscene, int index, double *hit, double tan)
{
	double	step[2];

	hit[Y] = ((int)(cubscene->player->y / REC_SIZE)) * REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_down)
		hit[Y] += REC_SIZE;
	hit[X] = cubscene->player->x + (hit[Y] - cubscene->player->y) * tan;
	step[Y] = REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_up)
		step[Y] *= -1;
	step[X] = REC_SIZE * tan;
	if (cubscene->rays[index]->is_ray_facing_left && step[X] > 0)
		step[X] *= -1;
	if (cubscene->rays[index]->is_ray_facing_right && step[X] < 0)
		step[X] *= -1;
	while (hit[X] >= 0 && hit[X] <= cubscene->map_width
		&& hit[Y] >= 0 && hit[Y] <= cubscene->map_height)
	{
		hit[HIT_STAT] = has_wall_at(cubscene, hit[X],
				hit[Y] - (cubscene->rays[index]->is_ray_facing_up));
		if (hit[HIT_STAT])
			break ;
		hit[X] += step[X];
		hit[Y] += step[Y];
	}
}

void	ver(t_cubscene *cubscene, int index, double *hit, double tan)
{
	double	step[2];

	hit[X] = ((int)(cubscene->player->x / REC_SIZE)) * REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_right)
		hit[X] += REC_SIZE;
	hit[Y] = cubscene->player->y + (hit[X]
			- cubscene->player->x) * tan;
	step[X] = REC_SIZE;
	if (cubscene->rays[index]->is_ray_facing_left)
		step[X] *= -1;
	step[Y] = REC_SIZE * tan;
	if (cubscene->rays[index]->is_ray_facing_up && step[Y] > 0)
		step[Y] *= -1;
	if (cubscene->rays[index]->is_ray_facing_down && step[Y] < 0)
		step[Y] *= -1;
	while (hit[X] >= 0 && hit[X] <= cubscene->map_width
		&& hit[Y] >= 0 && hit[Y] <= cubscene->map_height)
	{
		hit[HIT_STAT] = has_wall_at(cubscene,
				hit[X] - (cubscene->rays[index]->is_ray_facing_left), hit[Y]);
		if (hit[HIT_STAT])
			break ;
		hit[X] += step[X];
		hit[Y] += step[Y];
	}
}

void	intersection(t_cubscene *cubscene, int index, double tan_angle)
{
	double	hits[6];
	double	horzditance;
	double	verditance;

	horzditance = INT_MAX;
	verditance = INT_MAX;
	hits[HIT_STAT] = false;
	(hits + 3)[HIT_STAT] = false;
	hor(cubscene, index, hits, 1 / tan_angle);
	ver(cubscene, index, (hits + 3), tan_angle);
	if (hits[HIT_STAT])
		horzditance = distance(cubscene, index, hits[X], hits[Y]);
	if ((hits + 3)[HIT_STAT])
		verditance = distance(cubscene, index, (hits + 3)[X], (hits + 3)[Y]);
	cubscene->rays[index]->distance = horzditance;
	cubscene->rays[index]->_x = hits[X];
	cubscene->rays[index]->_y = hits[Y];
	cubscene->rays[index]->ver_hit = false;
	if (verditance < horzditance)
	{
		cubscene->rays[index]->distance = verditance;
		cubscene->rays[index]->_x = (hits + 3)[X];
		cubscene->rays[index]->_y = (hits + 3)[Y];
		cubscene->rays[index]->ver_hit = true;
	}
}
