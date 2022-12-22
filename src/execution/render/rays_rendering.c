/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 04:00:18 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/22 04:32:48 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_rays *new_ray(double angle)
{
	t_rays *ray;

	ray = (t_rays *) malloc(sizeof(t_rays));
	ray->angle = angle;
	return ray;
}

void ray_render(t_cubscene *cubscene, int index)
{
	int x;
	int y;
	
	x = cubscene->player->x - cos(cubscene->rays[index]->angle) * 30;
	y = cubscene->player->y - sin(cubscene->rays[index]->angle) * 30;
	 if (x < 0 || y < 0 || x >= cubscene->_width
        || y >= cubscene->_height)
		return ;
	line(cubscene, x, y, YELLOW);
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
		cubscene->rays[column_id] = new_ray(rayAngle);
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