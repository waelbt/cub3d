/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 04:00:18 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/31 12:16:16 by waboutzo         ###   ########.fr       */
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

void	cast_all_rays(t_cubscene *cubscene)
{
	int		column_id;
	double	ray_angle;
	double	tan_angle;

	column_id = 0;
	cubscene->rays = (t_rays **) malloc(sizeof(t_rays) * WIDTH);
	ray_angle = cubscene->player->rotation_angle - FIELD_OF_ANGLE_2;
	while (column_id < WIDTH)
	{
		cubscene->rays[column_id] = new_ray(ray_angle, cubscene);
		tan_angle = tan(cubscene->rays[column_id]->angle);
		intersection(cubscene, column_id, tan_angle);
		ray_angle += ((double) FIELD_OF_ANGLE) / WIDTH;
		column_id++;
	}
}

void	ft_free_rays(t_cubscene *cubscene)
{
	int	i;

	i = -1;
	while (++i < WIDTH)
		free(cubscene->rays[i]);
	free (cubscene->rays);
}
