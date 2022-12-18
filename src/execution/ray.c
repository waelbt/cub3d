/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:46:30 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/18 20:52:53 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_ray *new_ray(t_tuple *point, t_tuple *vector)
{
    t_ray *ray;

    if (point->e_type == Vector || vector->e_type == Point)
        printf("warning : your are trying to set a vector instead of point");
    ray = (t_ray *)malloc(sizeof(t_ray));
    if(!ray)
        return NULL;
    ray->origin = point;
    ray->direction = vector;
    return (ray);
}

t_tuple *position(t_ray *ray, double t)
{
    return (Adding(ray->origin, Multiplying(ray->direction, t)));
}