/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:56:14 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/20 19:43:17 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void rec(t_canvas *canvas, int x, int y, t_color *color)
{
	int i;
	int j;

	j = -1;
	while(++j < REC_SIZE)
	{
		i = -1;
		while(++i < REC_SIZE)
		{
			if (i == 0 || i == REC_SIZE - 1 || j == REC_SIZE -1 || j == 0)
				write_pixel(canvas, i + (x * REC_SIZE), j + (y * REC_SIZE), 0);
			else
				write_pixel(canvas, i + (x * REC_SIZE), j + (y * REC_SIZE), convert_color(color));
		}
	}
}