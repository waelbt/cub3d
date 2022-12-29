
//in case i ruined smth:
//
// int key_handler(int keycode, t_cubscene * cubscene)
// {
//   if (keycode == 53 || keycode < 0 )
//     exit(0);
//   else if (keycode == DOWN || keycode == DOWN_ARROW)
//   {
//     cubscene->frame_rate = 30;
//     cubscene->player->walk_direction = -1;
//   }
//   else if (keycode == UP || keycode == UP_ARROW)
//   {
//     cubscene->frame_rate = 30;
//     cubscene->player->walk_direction = 1;
//   }
//   else if (keycode == RIGHT || keycode == RIGHT_ARROW)
//   {
//     cubscene->frame_rate = 30;
//     cubscene->player->turn_direction = 1;
//   }
//   else if (keycode == LEFT || keycode == LEFT_ARROW)
//   {
//     cubscene->frame_rate = 30;
//     cubscene->player->turn_direction = -1;
//   }
//   return (0);
// }

// void	render_border(t_cubscene *cubscene)
// {
// 	int	i;
// 	int	j;

// 	j = -1;
// 	while (++j < cubscene->_height)
// 	{
// 		i = -1;
// 		while (++i < cubscene->_width)
// 		{
// 			if (!fmod(i, REC_SIZE) || !fmod(j, REC_SIZE))
// 				write_pixel(cubscene->canvas, i * SCALE, j * SCALE, 0);
// 			if (j == cubscene->_height - 1 || i == cubscene->_width - 1)
// 				write_pixel(cubscene->canvas, i * SCALE, j * SCALE, 0xFFFFFF);
// 		}
// 	}
// }
