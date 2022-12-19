/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:43:24 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/19 03:30:00 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_cubscene	*cubscene;
	t_canvas 	*canvas[3];
	int			window_height;
	int			window_width;
	(void) argv;

	if (argc != 2)
		ft_error(strerror(EINVAL));
	cubscene = new_cubscene();
	parsing(extension_check(argv[1]), cubscene);
	cubscene->mlx = mlx_init();
	if (!cubscene->mlx)
		ft_error("mlx_init() fails to set up the connection to the  graphical  system");
	window_height = cubscene->map_height * REC_SIZE;
	window_width = cubscene->map_width * REC_SIZE;
	cubscene->win = mlx_new_window(cubscene->mlx, window_width, window_height, "cub3d");
	canvas[0] = new_canvas(cubscene->mlx, REC_SIZE, REC_SIZE);
	canvas[1] = new_canvas(cubscene->mlx, REC_SIZE, REC_SIZE);
	canvas[2] = new_canvas(cubscene->mlx, REC_SIZE, REC_SIZE);
	rec(canvas[0], cubscene->floor);
	rec(canvas[1], cubscene->ceilling);
	rec(canvas[2], get_color(init_lexer("255, 0, 0\n")));
	for(int i = 0; i < cubscene->map_height; i++)
	{
		int len;
		len = ft_strlen(cubscene->map[i]);
		for(int j = 0; j < len; j++)
		{
			if (cubscene->map[i][j] == '0')
				mlx_put_image_to_window(cubscene->mlx, cubscene->win, canvas[0]->img, j * REC_SIZE, i * REC_SIZE);
			else if (cubscene->map[i][j] == 'N')
				mlx_put_image_to_window(cubscene->mlx, cubscene->win, canvas[2]->img, j * REC_SIZE, i * REC_SIZE);
			else if (cubscene->map[i][j] == '1')
				mlx_put_image_to_window(cubscene->mlx, cubscene->win, canvas[1]->img, j * REC_SIZE, i * REC_SIZE);
		}
	}
	printf("%d ", cubscene->player->x);
	printf("%d \n", cubscene->player->y);
	mlx_loop(cubscene->mlx);
	return (EXIT_SUCCESS);
}
