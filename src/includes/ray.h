/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:44:05 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 20:31:08 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
#define RAY_H

#include "cub3D.h"


typedef struct s_ray
{
	t_tuple *origin;
	t_tuple *direction;
} t_ray;

t_ray		*new_ray(t_tuple *point, t_tuple *vector);
t_tuple		*position(t_ray *ray, double t);

#endif