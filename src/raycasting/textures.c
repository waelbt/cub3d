/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:20:04 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/29 17:22:41 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_colors(t_canvas *canvas)
{
	int	x;
	int	y;

	x = -1;
	y = 0;
	canvas->color = (unsigned int **)malloc(sizeof(unsigned int *)
			* canvas->height);
	while (y < canvas->height)
	{
		canvas->color[y] = (unsigned int *)malloc(sizeof(unsigned int)
				* canvas->width);
		x = -1;
		while (++x < canvas->width)
		{
			canvas->color[y][x] = get_color_from_img(canvas, x, y);
		}
		y++;
	}
}

void	texture_canvas_init(t_cubscene *cubscene, int *w, int *h)
{
	int	i;
	t_texture	*tmp;

	i = -1;
	tmp = cubscene->texture;
	cubscene->tx_canvas[NO] = new_canvas(tmp->north, w[NO], h[NO]);
	cubscene->tx_canvas[SO] = new_canvas(tmp->south, w[SO], h[SO]);
	cubscene->tx_canvas[EA] = new_canvas(tmp->east, w[EA], h[EA]);
	cubscene->tx_canvas[WE] = new_canvas(tmp->west, w[WE], h[WE]);
	while (++i < 4)
		init_colors(cubscene->tx_canvas[i]);
}

void	texture_init(t_cubscene *cubscene)
{
	int			w[4];
	int			h[4];
	int			i;
	t_texture	*tmp;

	i = -1;
	tmp = cubscene->texture;
	cubscene->tx_canvas = (t_canvas **)malloc(4 * sizeof(t_canvas *));
	tmp->north = mlx_xpm_file_to_image(cubscene->mlx,
			tmp->path[NO], &w[NO], &h[NO]);
	tmp->south = mlx_xpm_file_to_image(cubscene->mlx,
			tmp->path[SO], &w[SO], &h[SO]);
	tmp->east = mlx_xpm_file_to_image(cubscene->mlx,
			tmp->path[EA], &w[EA], &h[EA]);
	tmp->west = mlx_xpm_file_to_image(cubscene->mlx,
			tmp->path[WE], &w[WE], &h[WE]);
	if (!tmp->north || !tmp->east || !tmp->west || !tmp->south)
		ft_error("invalid file or wrong path!");
	while (++i <= EA)
	{
		if (w[i] != REC_SIZE || h[i] != REC_SIZE)
			ft_error("bad texture dimentions!");
	}
	texture_canvas_init(cubscene, w, h);
}

unsigned int	get_color_from_img(t_canvas *canvas, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x > canvas->width || y > canvas->height)
		ft_error("problem occured in get_color function.");
	dst = canvas->addr + (y * canvas->line_length + x
			* (canvas->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
