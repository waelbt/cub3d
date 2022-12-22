/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:43:24 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/22 04:29:34 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/cub3D.h"

void render_map(t_cubscene *cubscene)
{
	int i;
	int j;

	j = -1;
	while (++j < cubscene->map_height)
	{
		i = -1;
		while(cubscene->map[j][++i])
		{
			if (cubscene->map[j][i] == '0'
				|| cubscene->map[j][i] == cubscene->player->character)
				rec(cubscene->canvas, i, j, cubscene->floor);
			else if (cubscene->map[j][i] == '1')
				rec(cubscene->canvas, i, j, cubscene->ceilling);
		}
	}
}

int render(t_cubscene *cubscene)
{
	// int x;
	// int y;
	int i;

	i  = -1;
	render_map(cubscene);
	update_player(cubscene);
	cast_all_rays(cubscene);
	while (++i < cubscene->_width)
		ray_render(cubscene, i);
	render_player(cubscene, RED);
	// x = cubscene->player->x - cos(cubscene->player->rotationAngle) * 30;
	// y = cubscene->player->y - sin(cubscene->player->rotationAngle) * 30;
	// line(cubscene,  x, y,  RED);
	mlx_put_image_to_window(cubscene->mlx, cubscene->win, cubscene->canvas->img, 0, 0);
	ft_free_rays(cubscene);
	return 0;
}

int key_handler(int keycode, t_cubscene * cubscene)
{
	if (keycode == 53 || keycode < 0)
		exit(0);
	if (keycode == RIGHT || keycode == RIGHT_ARROW)
		cubscene->player->turnDirection = 1;
	else if (keycode == LEFT || keycode == LEFT_ARROW)
		cubscene->player->turnDirection = -1;
	else if (keycode == DOWN || keycode == DOWN_ARROW)
		cubscene->player->walkDirection = 1;
	else if (keycode == UP || keycode == UP_ARROW)
		cubscene->player->walkDirection = -1;
	return (0);
}

int key_release(int keycode, t_cubscene * cubscene)
{
	if (keycode == RIGHT || keycode == RIGHT_ARROW
		|| keycode == LEFT || keycode == LEFT_ARROW)
		cubscene->player->turnDirection = 0;
	if (keycode == DOWN || keycode == DOWN_ARROW ||
	keycode == UP || keycode == UP_ARROW)
		cubscene->player->walkDirection = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_cubscene	*cubscene;
	(void) argv;

	if (argc != 2)
		ft_error(strerror(EINVAL));
	cubscene = new_cubscene();
	parsing(extension_check(argv[1]), cubscene);
	cubscene->mlx = mlx_init();
	if (!cubscene->mlx)
		ft_error("mlx_init() fails to set up the connection to the  graphical  system");
	cubscene->_height = cubscene->map_height * REC_SIZE;
	cubscene->_width = cubscene->map_width * REC_SIZE;
	cubscene->win = mlx_new_window(cubscene->mlx, cubscene->_width, cubscene->_height, "cub3d");
	cubscene->canvas = new_canvas(cubscene->mlx, cubscene->_width, cubscene->_height);
	mlx_hook(cubscene->win, 2, 0, key_handler, cubscene);
	mlx_hook(cubscene->win, 3, 0, key_release, cubscene);
	mlx_hook(cubscene->win, 17, 0, key_handler, cubscene);
	mlx_loop_hook(cubscene->mlx, render, cubscene);
	mlx_loop(cubscene->mlx);
	return (EXIT_SUCCESS);
}
