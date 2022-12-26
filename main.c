/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:43:24 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/26 20:07:18 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/cub3D.h"

void render_border(t_cubscene *cubscene)
{
	int i;
	int j;

	j = -1;
	while (++j < cubscene->_height)
	{
		i = -1;
		while(++i < cubscene->_width)
		{
			if (!fmod(i, REC_SIZE) || !fmod(j, REC_SIZE))
				write_pixel(cubscene->canvas, i * SCALE, j * SCALE, 0);
			if (j == cubscene->_height - 1 || i == cubscene->_width - 1)
				write_pixel(cubscene->canvas, i * SCALE, j * SCALE, 0xFFFFFF);
		}
	}
}

void render_env(t_cubscene *cubscene)
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
				mini_rec(cubscene->canvas, i, j, cubscene->floor);
			else if (cubscene->map[j][i] == '1')
				mini_rec(cubscene->canvas, i, j, 0x2D3047);
		}
	}
}

void render_minimap(t_cubscene *cubscene)
{
	int i;

	i  = -1;
	render_env(cubscene);
	while (++i < cubscene->_width)
		line(cubscene, cubscene->rays[i]->_x, cubscene->rays[i]->_y, YELLOW, SCALE);
	render_border(cubscene);
	render_player(cubscene, RED);
}

void ft_clear(t_cubscene *cubscene)
{
	int i;
	int j;

	j = -1;
	while(++j < cubscene->_height / 2)
	{
		i = -1;
		while(++i < cubscene->_width)
			write_pixel(cubscene->canvas, i, j , cubscene->ceilling);
	}
	while(j < cubscene->_height)	
	{
		i = -1;
		while(++i < cubscene->_width)
			write_pixel(cubscene->canvas, i, j , cubscene->floor);
		j++; 
	}
}

int render(t_cubscene *cubscene)
{
	if(cubscene->frame_rate > 0)
	{
		update_player(cubscene);
		cast_all_rays(cubscene);
		ft_clear(cubscene);
		projectewalls(cubscene);
		render_minimap(cubscene);
		ft_free_rays(cubscene);
		mlx_put_image_to_window(cubscene->mlx, cubscene->win, cubscene->canvas->img, 0, 0);
	}
	cubscene->frame_rate--;
	return 0;
}

int key_handler(int keycode, t_cubscene * cubscene)
{
	if (keycode == 53 || keycode < 0)
		exit(0);
	else if (keycode == DOWN || keycode == DOWN_ARROW)
	{
		cubscene->frame_rate = 30;
		cubscene->player->walkDirection = -1;
	}
	else if (keycode == UP || keycode == UP_ARROW)
	{
		cubscene->frame_rate = 30;
		cubscene->player->walkDirection = 1;
	}
	else if (keycode == RIGHT || keycode == RIGHT_ARROW)
	{
		cubscene->frame_rate = 30;
		cubscene->player->turnDirection = 1;
	}
	else if (keycode == LEFT || keycode == LEFT_ARROW)
	{
		cubscene->frame_rate = 30;
		cubscene->player->turnDirection = -1;
	}
	return (0);
}

int key_release(int keycode, t_cubscene * cubscene)
{
	if (keycode == DOWN || keycode == DOWN_ARROW ||
		keycode == UP || keycode == UP_ARROW)
		cubscene->player->walkDirection = 0;
	if (keycode == RIGHT || keycode == RIGHT_ARROW
		|| keycode == LEFT || keycode == LEFT_ARROW)
		cubscene->player->turnDirection = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_cubscene	*cubscene;
	void		*canvas;
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
	cubscene->half_height = cubscene->_height / 2;
	cubscene->half_width = cubscene->_width / 2;
	cubscene->win = mlx_new_window(cubscene->mlx, cubscene->_width, cubscene->_height, "cub3d");
	canvas = mlx_new_image(cubscene->mlx, cubscene->_width, cubscene->_height);
	cubscene->canvas = new_canvas(canvas,cubscene->_width, cubscene->_height);
	texture_init(cubscene);
	mlx_hook(cubscene->win, 2, 0, key_handler, cubscene);
	mlx_hook(cubscene->win, 3, 0, key_release, cubscene);
	mlx_hook(cubscene->win, 17, 0, key_handler, cubscene);
	mlx_loop_hook(cubscene->mlx, render, cubscene);
	mlx_loop(cubscene->mlx);
	return (EXIT_SUCCESS);
}
