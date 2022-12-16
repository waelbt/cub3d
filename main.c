/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:43:24 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 20:16:31 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_cubscene	*cubscene;
	int			i;

	if (argc != 2)
		ft_error(strerror(EINVAL));
	cubscene = new_cubscene();
	parsing(extension_check(argv[1]), cubscene);
	printf("NO %s\n", cubscene->texture->path[NO]);
	printf("SO %s\n", cubscene->texture->path[SO]);
	printf("WE %s\n", cubscene->texture->path[WE]);
	printf("EA %s\n", cubscene->texture->path[EA]);
	printf("Ceilling %d %d %d\n", cubscene->ceilling->red,
		cubscene->ceilling->green, cubscene->ceilling->blue);
	printf("floor %d %d %d\n", cubscene->floor->red,
		cubscene->floor->green, cubscene->floor->blue);
	i = -1;
	while (cubscene->map[++i])
		printf("%s\n", cubscene->map[i]);
	return (EXIT_SUCCESS);
}
