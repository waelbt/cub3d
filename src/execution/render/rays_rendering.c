/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 04:00:18 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/22 07:29:06 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

double normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return angle;	
}

t_rays *new_ray(double angle)
{
	t_rays *ray;

	ray = (t_rays *) malloc(sizeof(t_rays));
	ray->angle = normalize_angle(angle);
	ray->wallhitx = 0;
	ray->wallhity = 0;
	ray->distance = 0;
	ray->israyfacingup = (angle > 0) && (angle < M_PI);
	ray->israyfacingdown = !ray->israyfacingup ;
	ray->israyfacingright = (angle < (0.5 * M_PI)) || (angle > (1.5 * M_PI));
	ray->israyfacingleft = !ray->israyfacingright;
	return ray;
}

double distance_between_points(int x1, int y1, int x2, int y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void cast(t_cubscene *cubscene, t_rays *ray)
{
	int xintercept;
	int yintercept;
	int xstep;
	int ystep;
	bool foundhorzwallhit;
	int horzwallhitx = 0;
	int horzwallhity = 0;

	ystep = REC_SIZE;
	foundhorzwallhit = false;
	yintercept = floor(cubscene->player->y / REC_SIZE) * REC_SIZE;
	if (!ray->israyfacingup)
	{
		ystep *= -1;
		yintercept += REC_SIZE;
	}
	xintercept = cubscene->player->x
		+ (yintercept - cubscene->player->x)
		/ tan(ray->angle);
	xstep = REC_SIZE / tan(ray->angle);
	if (ray->israyfacingleft && xstep > 0)
		xstep *= -1;
	if (ray->israyfacingright && xstep < 0)
		xstep *= -1;

	int nexthorzwallhittx = xintercept;
	int nexthorzwallhitty = yintercept;

	if (ray->israyfacingup)
		nexthorzwallhitty--;
	while (nexthorzwallhittx >= 0 && nexthorzwallhittx <= cubscene->_width
		&& nexthorzwallhitty >= 0 && nexthorzwallhitty <= cubscene->_height)
	{
		if (hasWallAt(cubscene, nexthorzwallhittx, nexthorzwallhitty))
		{
			foundhorzwallhit = true;
			horzwallhitx = nexthorzwallhittx;
			horzwallhity = nexthorzwallhitty;
			//line(cubscene, ray->wallhitx, ray->wallhity, YELLOW);
			break;
		}
		nexthorzwallhittx +=xstep;
		nexthorzwallhitty +=ystep;
	}
	/*********************************/
	bool foundVertWallHit = false;
    int vertWallHitX = 0;
    int vertWallHitY = 0;

	xstep = REC_SIZE;
	xintercept = floor(cubscene->player->x / REC_SIZE) * REC_SIZE;
	if (!ray->israyfacingright)
	{
		ystep *= -1;
		yintercept += REC_SIZE;
	}
	yintercept = cubscene->player->y
		+ (xintercept - cubscene->player->x)
		/ tan(ray->angle);
	xstep = REC_SIZE / tan(ray->angle);
	if (ray->israyfacingup && xstep > 0)
		xstep *= -1;
	if (ray->israyfacingdown && xstep < 0)
		xstep *= -1;
	int nextverttouchx = xintercept;
	int nextverttouchy = yintercept;
	if (ray->israyfacingleft)
		nextverttouchx--;
	
	while (nextverttouchx >= 0 && nextverttouchx <= cubscene->_width
		&& nextverttouchy >= 0 && nextverttouchy <= cubscene->_height)
	{
		if (hasWallAt(cubscene, nextverttouchx, nextverttouchy))
		{
			foundVertWallHit = true;
			vertWallHitX = nextverttouchx;
			vertWallHitY = nextverttouchy;
			//line(cubscene, ray->wallhitx, ray->wallhity, YELLOW);
			break;
		}
		nextverttouchx +=xstep;
		nextverttouchy +=ystep;
	}
	int horzhitdistance = (foundhorzwallhit) ? distance_between_points(cubscene->player->x, cubscene->player->y, horzwallhitx, horzwallhity) :
	INT_MAX;
	int verhitdistance = (foundVertWallHit) ? distance_between_points(cubscene->player->x, cubscene->player->y, vertWallHitX, vertWallHitY) :
	INT_MAX;
	if (horzhitdistance < verhitdistance)
	{
		ray->wallhitx = horzwallhitx;
		ray->wallhity = horzwallhity;
	}
	else
	{
		ray->wallhitx = vertWallHitX;
		ray->wallhity = horzwallhity;
	}
}

void ray_render(t_cubscene *cubscene, int index)
{
	line(cubscene, cubscene->rays[index]->wallhitx, cubscene->rays[index]->wallhity, YELLOW);
}

void cast_all_rays(t_cubscene *cubscene)
{
	int column_id;
	t_rays *ray;
	double rayAngle;

	column_id = 0;
	cubscene->rays = (t_rays **) malloc(sizeof(t_rays) * cubscene->_width);
	rayAngle = cubscene->player->rotationAngle - (FIELD_OF_ANGLE / 2);
	
	while (column_id < cubscene->_width)
	{
		ray = new_ray(rayAngle);
		cast(cubscene, ray);
		cubscene->rays[column_id] = ray;
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