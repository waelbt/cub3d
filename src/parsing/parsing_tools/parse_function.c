/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:44:46 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/29 16:18:37 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int 	check_elements(t_cubscene *cubscene,char element, int *counter, int x, int y)
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
				(*counter)++;
			}
			return 0;
		}
	}
	return 1;
}
void	check_undefined_elements(t_cubscene *cubscene, char *str, int *counter, int y, int x)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (check_elements(cubscene, str[i], counter, x, y))
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
	size_t i;
	size_t j;
	size_t len;

	j = -1;
	while(cubscene->map[++j])
	{
		i = -1;
		len = ft_strlen(cubscene->map[j]);
		while (cubscene->map[j][++i])
		{
			if(cubscene->map[j][i] == 'N')
			{
				if ((i - 1 >= 0 && cubscene->map[j][i - 1] == 32)
				|| (i + 1 < len && cubscene->map[j][i + 1] == 32)
				|| (j - 1 >= 0 && i < ft_strlen(cubscene->map[j - 1]) && cubscene->map[j - 1][i] == 32)
				|| (j + 1 < (size_t) cubscene->map_height && i < ft_strlen(cubscene->map[j - 1]) && cubscene->map[j + 1][i] == 32))
					ft_error(ft_strjoin(ft_strjoin("unclosed map at i: ", ft_itoa(i)), ft_strjoin(" & j: ", ft_itoa(j))));
			}
			if (cubscene->map[j][i] == '0')
			{
				if ((i - 1 >= 0 && corners_check(cubscene->map[j][i - 1]))
				|| (i + 1 < len && corners_check(cubscene->map[j][i + 1]))
				|| (j - 1 >= 0 && i < ft_strlen(cubscene->map[j - 1]) && corners_check(cubscene->map[j - 1][i]))
				|| (j + 1 < (size_t) cubscene->map_height && i < ft_strlen(cubscene->map[j - 1]) && corners_check(cubscene->map[j + 1][i])))
					ft_error(ft_strjoin(ft_strjoin("unclosed map at i: ", ft_itoa(i)), ft_strjoin(" & j: ", ft_itoa(j))));
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
