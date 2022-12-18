/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:24:45 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 20:21:00 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_HPP
#define TUPLES_HPP

typedef struct s_tuple
{
    /*in cas of colors */
    double  x; /*red*/
    double  y; /*green*/
    double  z; /*blue*/
    enum
    {
        Vector,
        Point,
        Color,
        undefine,
    }	e_type;
}t_tuple;

t_tuple *New_tuples(double x, double y, double z, int type);
t_tuple *Adding(t_tuple *a, t_tuple  *b);
t_tuple *subtracting(t_tuple *a, t_tuple  *b);
t_tuple *negating(t_tuple *a);
t_tuple *Multiplying(t_tuple *a, double t);
t_tuple *devide_tuple(t_tuple *a, double t);
double	magnitude(t_tuple *a);
t_tuple *normalization(t_tuple *a);
double	dot(t_tuple *a, t_tuple *b);
t_tuple	*cross(t_tuple *a, t_tuple *b);
t_tuple *hadamard(t_tuple *a, t_tuple *b);
void	printf_tuple(t_tuple *a);
#endif