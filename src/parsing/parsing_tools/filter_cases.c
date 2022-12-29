/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:38:15 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/29 18:44:56 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	identifier(t_lexer *lexer)
{
	if (lexer->c == '\n' || lexer->c == '\0')
		ft_error("identifier without value");
	if (lexer->c == 32)
		return (0);
	return (1);
}

int	identifier_value(t_lexer *lexer)
{
	if (lexer->c == '\0')
		ft_error("invalid identifier");
	if (lexer->c == '\n')
		return (0);
	return (1);
}

int	identifier_color(t_lexer *lexer)
{
	if (lexer->c == '\0')
		ft_error("invalid identifier");
	if (lexer->c == ',' || lexer->c == '\n' || lexer->c == 32)
		return (0);
	return (1);
}

void	add_lines(t_cubscene *cubscene, char *str)
{
	char	**new_map;
	int		index;
	int		len;

	index = -1;
	new_map = malloc(sizeof(char *) * (++cubscene->map_height + 1));
	while (cubscene->map[++index])
	{
		len = ft_strlen(cubscene->map[index]);
		if (cubscene->map_width < len)
			cubscene->map_width = len;
		new_map[index] = cubscene->map[index];
	}
	new_map[index++] = str;
	len = ft_strlen(str);
	if (cubscene->map_width < len)
		cubscene->map_width = len;
	new_map[index] = NULL;
	free(cubscene->map);
	cubscene->map = new_map;
}

void	free_lexer(t_lexer *lexer)
{
	free(lexer->contents);
	free(lexer);
}
