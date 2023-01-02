/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 04:00:18 by waboutzo          #+#    #+#             */
/*   Updated: 2023/01/01 15:30:07 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	new_ray(double angle, t_cubscene *cubscene, int index)
{
	t_rays	*ray;

	ray = cubscene->rays[index];
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

	column_id = 0;
	ray_angle = cubscene->player->rotation_angle - FIELD_OF_ANGLE_2;
	while (column_id < WIDTH)
	{
		new_ray(ray_angle, cubscene, column_id);
		intersection(cubscene, column_id, tan(ray_angle));
		projectewall(cubscene, column_id);
		ray_angle += ((double) FIELD_OF_ANGLE) / WIDTH;
		column_id++;
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
	k[0] = ((double)cubscene->tx_canvas[w]->height / h);
	k[1] = cubscene->tx_canvas[w]->scale;
	x2 = (int)(cubscene->rays[x]->_x * k[1]) % cubscene->tx_canvas[w]->width;
	if (cubscene->rays[x]->ver_hit)
		x2 = (int)(cubscene->rays[x]->_y * k[1])
			% cubscene->tx_canvas[w]->width;
	while (y2 < h)
	{
		y1 = y2 * k[0];
		write_pixel(cubscene->canvas, x, (y + y2),
			cubscene->tx_canvas[w]->color[y1][x2]);
		y2++;
	}
}
