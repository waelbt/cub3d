/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:43:24 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/20 20:25:23 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/cub3D.h"

void render(t_cubscene *cubscene)
{
	int i;
	int j;

	j = -1;
	cubscene->canvas = new_canvas(cubscene->mlx, cubscene->_width, cubscene->_height);
	while (++j < cubscene->map_height)
	{
		i = -1;
		while(cubscene->map[j][++i])
		{
			if (cubscene->map[j][i] == '0' || cubscene->map[j][i] == cubscene->player->character)
				rec(cubscene->canvas, i, j, cubscene->floor);
			else if (cubscene->map[j][i] == '1')
				rec(cubscene->canvas, i, j, cubscene->ceilling);
		}
	}
	circle(cubscene->canvas, cubscene->player->x, cubscene->player->y, 7, get_color(init_lexer("255, 0, 0\n")));
	mlx_put_image_to_window(cubscene->mlx, cubscene->win, cubscene->canvas->img, 0, 0);
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
	render(cubscene);
	mlx_loop(cubscene->mlx);
	return (EXIT_SUCCESS);
}
