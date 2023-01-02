/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:43:24 by waboutzo          #+#    #+#             */
/*   Updated: 2023/01/01 15:50:19 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/cub3D.h"

void	ft_clear(t_cubscene *cubscene)
{
	int		i;
	int		j;

	j = -1;
	while (++j < HEIGHT_2)
	{
		i = -1;
		while (++i < WIDTH)
			write_pixel(cubscene->canvas, i, j, cubscene->ceilling);
	}
	while (j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
			write_pixel(cubscene->canvas, i, j, cubscene->floor);
		j++;
	}
}

int	render(t_cubscene *cubscene)
{
	if (cubscene->frame_rate > 0)
	{
		ft_clear(cubscene);
		update_player(cubscene);
		cast_all_rays(cubscene);
		mlx_put_image_to_window(cubscene->mlx, cubscene->win,
			cubscene->canvas->img, 0, 0);
	}
	cubscene->frame_rate--;
	return (0);
}

int	main(int argc, char **argv)
{
	t_cubscene	*cubscene;
	void		*canvas;

	if (argc != 2)
		ft_error(strerror(EINVAL));
	cubscene = new_cubscene();
	parsing(extension_check(argv[1]), cubscene);
	cubscene->mlx = mlx_init();
	if (!cubscene->mlx)
		ft_error("mlx_init() failed to connect to graphical system!");
	cubscene->map_height *= REC_SIZE;
	cubscene->map_width *= REC_SIZE;
	cubscene->win = mlx_new_window(cubscene->mlx,
			WIDTH, HEIGHT, "cub3d");
	canvas = mlx_new_image(cubscene->mlx, WIDTH, HEIGHT);
	cubscene->canvas = new_canvas(canvas, WIDTH, HEIGHT);
	texture_init(cubscene);
	mlx_hook(cubscene->win, 2, 0, key_handler, cubscene);
	mlx_hook(cubscene->win, 3, 0, key_release, cubscene);
	mlx_hook(cubscene->win, 17, 0, close_x, cubscene);
	mlx_loop_hook(cubscene->mlx, render, cubscene);
	mlx_loop(cubscene->mlx);
	return (EXIT_SUCCESS);
}
