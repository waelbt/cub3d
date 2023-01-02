/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:32:15 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/31 14:15:06 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_map(t_cubscene *cubscene)
{
	char		**c;
	int			i[2];

	i[0] = -1;
	if (!cubscene->map_height)
		ft_error("missing map -_-");
	hard_code_time(cubscene);
	while (++i[0] < cubscene->map_height)
	{
		c = ft_split(cubscene->map[i[0]], 32);
		if (!c[0])
			ft_error("undefine elements");
		i[1] = -1;
		while (c[++i[1]])
		{
			undefined_elem(cubscene, c[i[1]], i[0], posi(cubscene->map[i[0]]));
			if (i[0] == 0 || i[0] == cubscene->map_height - 1)
				horizontal_walls(c[i[1]]);
			if (c[i[1]][0] != '1' || c[i[1]][ft_strlen(c[i[1]]) - 1] != '1')
				ft_error("unclosed vertical walls");
		}
		ft_free(c);
	}
	if (cubscene->counter != 1)
		ft_error("zero or more then one staring position !");
}

void	except_for_the_map(t_cubscene *cubscene, t_lexer *lexer, int *counter)
{
	char	*key;

	key = filter(lexer, identifier);
	if (!ft_strcmp(key, "F"))
	{
		if (cubscene->floor)
			ft_error("repeated identifier");
		cubscene->floor = convert_color(get_color(lexer));
	}
	else if (!ft_strcmp(key, "C"))
	{
		if (cubscene->ceilling)
			ft_error("repeated identifier");
		cubscene->ceilling = convert_color(get_color(lexer));
	}
	else
		fill_textures(cubscene, lexer, key);
	free(key);
	key = filter(lexer, identifier_value);
	if (ft_strcmp(key, ""))
		ft_error("to many value for an identifier");
	free(key);
	(*counter)++;
}

void	playercnr(t_cubscene *cubscene, size_t i, size_t j, size_t len)
{
	if ((i - 1 >= 0 && cubscene->map[j][i - 1] == 32)
		|| (i + 1 < len && cubscene->map[j][i + 1] == 32)
		|| (j - 1 >= 0 && i < ft_strlen(cubscene->map[j - 1])
			&& cubscene->map[j - 1][i] == 32)
		|| (j + 1 < (size_t) cubscene->map_height
			&& i < ft_strlen(cubscene->map[j - 1])
			&& cubscene->map[j + 1][i] == 32))
		ft_error(ft_strjoin(ft_strjoin("unclosed map at i: ", ft_itoa(i)),
				ft_strjoin(" & j: ", ft_itoa(j))));
}

void	corners(t_cubscene *cubscene, size_t i, size_t j, size_t len)
{
	if ((i - 1 >= 0 && corners_check(cubscene->map[j][i - 1]))
		|| (i + 1 < len && corners_check(cubscene->map[j][i + 1]))
		|| (j - 1 >= 0 && i < ft_strlen(cubscene->map[j - 1])
			&& corners_check(cubscene->map[j - 1][i]))
		|| (j + 1 < (size_t) cubscene->map_height
			&& i < ft_strlen(cubscene->map[j - 1])
			&& corners_check(cubscene->map[j + 1][i])))
		ft_error(ft_strjoin(ft_strjoin("unclosed map at i: ", ft_itoa(i)),
				ft_strjoin(" & j: ", ft_itoa(j))));
}
