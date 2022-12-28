/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:16:27 by lchokri           #+#    #+#             */
/*   Updated: 2022/12/28 20:16:50 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


int	key_handler(int keycode, t_cubscene *cubscene)
{
	cubscene->frame_rate = 30;
	if (keycode == 53 || keycode < 0)
		exit(0);
	else if (keycode == DOWN)
		cubscene->player->walkDirection = -1;
	else if (keycode == UP)
		cubscene->player->walkDirection = 1;
	else if (keycode == RIGHT_ARROW)
		cubscene->player->turnDirection = 1;
	else if (keycode == LEFT_ARROW)
		cubscene->player->turnDirection = -1;
	else if (keycode == RIGHT)
	{
		cubscene->player->turnDirection = 1;
		cubscene->player->walkDirection = 1;
	}
	else if (keycode == LEFT)
	{
		cubscene->player->turnDirection = -1;
		cubscene->player->walkDirection = 1;
	}
	return (0);
}

int	key_release(int keycode, t_cubscene *cubscene)
{
	if (keycode == DOWN || keycode == DOWN_ARROW || keycode == UP
		|| keycode == UP_ARROW || keycode == LEFT || keycode == RIGHT)
			cubscene->player->walkDirection = 0;
	if (keycode == RIGHT || keycode == RIGHT_ARROW
		|| keycode == LEFT || keycode == LEFT_ARROW)
			cubscene->player->turnDirection = 0;
	return (0);
}

int	close_x(void)
{
	exit (0);
	return (0);
}

