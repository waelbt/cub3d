/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubscene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/10 12:46:47 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_cubscene	*new_cubscene(void)
{
	t_cubscene	*cubscene;
	int			i;

	i = -1;
	cubscene = (t_cubscene *) malloc(sizeof(t_cubscene));
	cubscene->counter = 0;
	cubscene->texture = (t_texture *) malloc(sizeof(t_texture));
	cubscene->texture->path = (char **) malloc(sizeof(char *) * 5);
	cubscene->floor = NULL;
	cubscene->map = malloc(sizeof(char *));
	cubscene->map[0] = NULL;
	cubscene->map_height = 0;
	cubscene->Ceilling = NULL;
	while (++i < 4)
		cubscene->texture->path[i] = NULL;
	return (cubscene);
}
