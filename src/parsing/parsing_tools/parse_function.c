/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:44:46 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/23 17:20:00 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_undefined_elements(t_cubscene *cubscene, char *str, int *counter, int y, int x)
{
	char *elements;
	int i;
	int j;
	int flag;

	i = -1;
	elements = "01 NSWE";
	while (str[++i])
	{
		j = -1;
		flag = 0;
		while (elements[++j])
		{
			if (str[i] == elements[j])
			{
				flag = 1;
				if (j > 2)
				{
					cubscene->player = new_player(x, y, str[i]);
					(*counter)++;
				}
			}
		}
		if (!flag)
			ft_error("undefine elements");
	}
}

int		corners_check(char c)
{
	if (c == '\0' || c == '\n' || c == 32)
		return 1;
	return 0;
}

void		hard_code_time(t_cubscene *cubscene)
{
	int i;
	int j;
	int len;

	j = -1;
	while(cubscene->map[++j])
	{
		i = -1;
		len = ft_strlen(cubscene->map[j]);
		while (cubscene->map[j][++i])
		{
			if (cubscene->map[j][i] == '0')
			{
				if ((i - 1 >= 0 && corners_check(cubscene->map[j][i - 1]))
				|| (i + 1 < len && corners_check(cubscene->map[j][i + 1]))
				|| (j - 1 >= 0 && corners_check(cubscene->map[j - 1][i]))
				|| (j + 1 < cubscene->map_height && corners_check(cubscene->map[j + 1][i])))
					ft_error("unclosed map");
			}
		}
	}
}

void		horizontal_walls(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] != '1')
			ft_error("unclosed horizontal walls");	
}
