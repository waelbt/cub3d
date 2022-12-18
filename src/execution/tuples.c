/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:34:55 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 20:31:47 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool equal(double a, double b)
{
    if(fabs(a - b) < FLT_EPSILON)
        return true;
    return false;
}

t_tuple *New_tuples(double x, double y, double z, int type)
{
    t_tuple *new;

    new = (t_tuple *) malloc(sizeof(t_tuple));
    if(!new)
        return (NULL);
    new->e_type = type;
    new->x = x;
    new->y = y;
    new->z = z;
    return new;
}
t_tuple *Adding(t_tuple *a, t_tuple  *b)
{
    return (New_tuples(a->x + b->x, a->y + b->y, a->z + b->z, a->e_type + b->e_type));
}

t_tuple *subtracting(t_tuple *a, t_tuple  *b)
{
    return (New_tuples(a->x - b->x, a->y - b->y, a->z - b->z, a->e_type - b->e_type));
}

t_tuple *negating(t_tuple *a)
{
    return (New_tuples(-(a->x), -(a->y), -(a->z),a->e_type));
}

t_tuple *Multiplying(t_tuple *a, double t)
{
    return (New_tuples(a->x * t, a->y * t, a->z * t, a->e_type));
}

t_tuple *devide(t_tuple *a, double t)
{
    if(!equal(t, 0))
        return (New_tuples(a->x / t, a->y / t, a->z / t, a->e_type / t));
    ft_putstr_fd("impossible to devide with zero\n", 2);
    return NULL;
}

double	magnitude(t_tuple *a)
{
    return (sqrtf(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2)));
}

t_tuple *normalization(t_tuple *a)
{
    return devide(a, magnitude(a));
}

double dot(t_tuple *a, t_tuple *b)
{
    return (a->e_type * b->e_type + a->x * b->x + a->y * b->y + a->z * b->z);
}

t_tuple *cross(t_tuple *a, t_tuple *b)
{
    return (New_tuples(a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z, a->x * b->y - a->y * b->x, Vector));
}

t_tuple *hadamard(t_tuple *a, t_tuple *b)
{
    return New_tuples(a->x * b->x, a->y * b->y, a->z * b->z, Color);
}

void	printf_tuple(t_tuple *a)
{
    printf("(%d, %d, %d, %d)\n\n", (int)a->x,(int) a->y, (int)a->z, a->e_type);
}
