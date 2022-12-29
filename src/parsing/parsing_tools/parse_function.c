/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:44:46 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/29 18:52:37 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_elements(t_cubscene *cubscene, char element, int x, int y)
{
	char	*elements;
	int		j;

	j = -1;
	elements = "01 NSWE";
	while (elements[++j])
	{
		if (element == elements[j])
		{
			if (j > 2)
			{
				printf("%d %d\n", x, y);
				cubscene->player = new_player(x, y, element);
				cubscene->counter++;
			}
			return (0);
		}
	}
	return (1);
}

void	undefined_elem(t_cubscene *cubscene, char *str, int y, int x)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (check_elements(cubscene, str[i], x, y))
			ft_error("undefine elements");
	}
}

int	corners_check(char c)
{
	if (c == '\0' || c == '\n' || c == 32)
		return (1);
	return (0);
}

void	hard_code_time(t_cubscene *cubscene)
{
	size_t	i;
	size_t	j;
	size_t	len;

	j = -1;
	while (cubscene->map[++j])
	{
		i = -1;
		len = ft_strlen(cubscene->map[j]);
		while (cubscene->map[j][++i])
		{
			if (cubscene->map[j][i] == 'N')
				player_corners(cubscene, i, j, len);
			if (cubscene->map[j][i] == '0')
				corners(cubscene, i, j, len);
		}
	}
}

void	horizontal_walls(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '1')
			ft_error("unclosed horizontal walls");
	}
}
