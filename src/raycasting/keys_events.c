/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:16:27 by lchokri           #+#    #+#             */
/*   Updated: 2022/12/29 17:51:30 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


int	key_handler(int keycode, t_cubscene *cubscene)
{
	cubscene->frame_rate = 30;
	if (keycode == 53)
		exit(0);
	else if (keycode == DOWN)
		cubscene->player->walk_direction = -1;
	else if (keycode == UP)
		cubscene->player->walk_direction = 1;
	else if (keycode == RIGHT_ARROW)
		cubscene->player->turn_direction = 1;
	else if (keycode == LEFT_ARROW)
		cubscene->player->turn_direction = -1;
	else if (keycode == RIGHT)
	{
		cubscene->player->flag = 1;
		cubscene->player->walk_direction = -1;
	}
	else if (keycode == LEFT)
	{
		cubscene->player->flag = 1;
		cubscene->player->walk_direction = 1;
	}
	return (0);
}

int	key_release(int keycode, t_cubscene *cubscene)
{
	if (keycode == DOWN)
		cubscene->player->walk_direction = 0;
	else if (keycode == UP)
		cubscene->player->walk_direction = 0;
	else if (keycode == RIGHT_ARROW)
		cubscene->player->turn_direction = 0;
	else if (keycode == LEFT_ARROW)
		cubscene->player->turn_direction = 0;
	else if (keycode == RIGHT || keycode == LEFT)
	{
		cubscene->player->walk_direction = 0;
		cubscene->player->flag = 0;
	}
	return (0);
}

int	close_x(void)
{
	exit (0);
	return (0);
}

