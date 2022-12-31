/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:43:24 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/31 12:18:29 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/cub3D.h"

void	render_env(t_cubscene *cubscene)
{
	int	i;
	int	j;

	j = -1;
	while (++j < cubscene->map_height)
	{
		i = -1;
		while (cubscene->map[j][++i])
		{
			if (cubscene->map[j][i] == '0'
				|| cubscene->map[j][i] == cubscene->player->character)
				mini_rec(cubscene->canvas, i, j, cubscene->floor);
			else if (cubscene->map[j][i] == '1')
				mini_rec(cubscene->canvas, i, j, 0x2D3047);
		}
	}
}

void	render_minimap(t_cubscene *cubscene)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	x = cubscene->player->x + cos(cubscene->player->rotation_angle) * 60;
	y = cubscene->player->y + sin(cubscene->player->rotation_angle) * 60;
	render_env(cubscene);
	line(cubscene, x, y, SCALE);
	render_player(cubscene, RED);
}

void	ft_clear(t_cubscene *cubscene)
{
	int		i;
	int		j;

	j = -1;
	while (++j < HEIGHT)
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
		update_player(cubscene);
		cast_all_rays(cubscene);
		ft_clear(cubscene);
		projectewalls(cubscene);
		//render_minimap(cubscene);
		ft_free_rays(cubscene);
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
