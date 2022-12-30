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
	canvas->color = (unsigned int **)malloc(sizeof(unsigned int*) * canvas->height);
	while (y < canvas->height)
	{
		canvas->color[y] = (unsigned int *)malloc(sizeof(unsigned int) * canvas->width);
		x = -1;
		while (++x < canvas->width)
		{
			canvas->color[y][x] = get_color_from_img(canvas, x, y);
		}
		y++;
	}
}

void texture_init(t_cubscene *cubscene)
{
	int		width[4];
	int		height[4];
	int		i;

	i = -1;
	cubscene->tx_canvas = (t_canvas **)malloc(4 * sizeof(t_canvas *));
	cubscene->texture->north_image = mlx_xpm_file_to_image(cubscene->mlx, cubscene->texture->path[NO], &width[NO], &height[NO]);
	cubscene->texture->south_image = mlx_xpm_file_to_image(cubscene->mlx, cubscene->texture->path[SO], &width[SO], &height[SO]);
	cubscene->texture->east_image = mlx_xpm_file_to_image(cubscene->mlx, cubscene->texture->path[EA], &width[EA], &height[EA]);
	cubscene->texture->west_image = mlx_xpm_file_to_image(cubscene->mlx, cubscene->texture->path[WE], &width[WE], &height[WE]);
 	if(!cubscene->texture->north_image ||!cubscene->texture->east_image || !cubscene->texture->west_image || !cubscene->texture->south_image)
 		ft_error("invalid file or wrong path!");
	cubscene->tx_canvas[NO] = new_canvas(cubscene->texture->north_image, width[NO], height[NO]);
	cubscene->tx_canvas[SO] = new_canvas(cubscene->texture->south_image, width[SO], height[SO]);
	cubscene->tx_canvas[EA] = new_canvas(cubscene->texture->east_image, width[EA], height[EA]);
	cubscene->tx_canvas[WE] = new_canvas(cubscene->texture->west_image, width[WE], height[WE]);
	i = -1;
	while (++i < 4)
		init_colors(cubscene->tx_canvas[i]);
}
unsigned int get_color_from_img(t_canvas *canvas, int x, int y)
{
	char	*dst;

    if (x < 0 || y < 0 || x > canvas->width
        || y > canvas->height)
			ft_error("get color overflowed, check your boucle codition idiot -_-");
	dst = canvas->addr + (y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}