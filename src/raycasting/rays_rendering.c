/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 04:00:18 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/26 19:27:30 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_rays	*new_ray(double angle, t_cubscene *cubscene)
{
	t_rays	*ray;

	ray = (t_rays *)malloc(sizeof(t_rays));
	ray->angle = fmod(angle, (2 * M_PI));
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	ray->_x = cubscene->player->x;
	ray->_y = cubscene->player->y;
	ray->distance = 0;
	ray->is_ray_facing_down = ((ray->angle >= 0) && (ray->angle <= M_PI));
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ((ray->angle <= 0.5 * M_PI)
			|| (ray->angle >= 1.5 * M_PI));
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
	return (ray);
}

double	distance(t_cubscene *cubscene, int index, double x2, double y2)
{
	return ((x2 - cubscene->player->x)
		* cos(cubscene->rays[index]->angle) + (y2 - cubscene->player->y)
		* sin(cubscene->rays[index]->angle));
}

void	intersection(t_cubscene *cubscene, int index)
{
	double	*horz_hit;
	double	*ver_hit;
	double	horzditance;
	double	verditance;

	horzditance = INT_MAX;
	verditance = INT_MAX;
	horz_hit = hor_intersection(cubscene, index);
	ver_hit = ver_intersection(cubscene, index);
	if (horz_hit[HIT_STAT])
		horzditance = distance(cubscene, index, horz_hit[X], horz_hit[Y]);
	if (ver_hit[HIT_STAT])
		verditance = distance(cubscene, index, ver_hit[X], ver_hit[Y]);
	if (verditance < horzditance)
	{
		cubscene->rays[index]->distance = verditance;
		cubscene->rays[index]->_x = ver_hit[X];
		cubscene->rays[index]->_y = ver_hit[Y];
		cubscene->rays[index]->ver_hit = true;
	}
	else
	{
		cubscene->rays[index]->distance = horzditance;
		cubscene->rays[index]->_x = horz_hit[X];
		cubscene->rays[index]->_y = horz_hit[Y];
		cubscene->rays[index]->ver_hit = false;
	}
}

void	cast_all_rays(t_cubscene *cubscene)
{
	int		column_id;
	double	ray_angle;

	column_id = 0;
	cubscene->rays = (t_rays **) malloc(sizeof(t_rays) * cubscene->_width);
	ray_angle = cubscene->player->rotation_angle - FIELD_OF_ANGLE_2;
	while (column_id < cubscene->_width)
	{
		cubscene->rays[column_id] = new_ray(ray_angle, cubscene);
		intersection(cubscene, column_id);
		ray_angle += ((double) FIELD_OF_ANGLE) / cubscene->_width;
		column_id++;
	}
}

void	ft_free_rays(t_cubscene *cubscene)
{
	int	i;

	i = -1;
	while (++i < cubscene->_width)
		free(cubscene->rays[i]);
	free (cubscene->rays);
}
