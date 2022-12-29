/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:18:13 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/29 18:43:50 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_color	*get_color(t_lexer *lexer)
{
	t_color	*color;

	color = (t_color *) malloc(sizeof(t_color));
	color->red = color_check(filter(lexer, identifier_color));
	lexer_skip_comma(lexer);
	color->green = color_check(filter(lexer, identifier_color));
	lexer_skip_comma(lexer);
	color->blue = color_check(filter(lexer, identifier_color));
	if (color->red < 0 || color->blue < 0
		|| color->green < 0 || color->red > 255
		|| color->blue > 255 || color->green > 255)
		ft_error("out of range");
	return (color);
}

char	**fill_types(void)
{
	char	**types;

	types = (char **) malloc(sizeof(char *) * 5);
	types[0] = "NO";
	types[1] = "SO";
	types[2] = "WE";
	types[3] = "EA";
	types[4] = NULL;
	return (types);
}

void	path_validition(char *ptr)
{
	int	fd;

	fd = open(ptr, 0);
	if (fd < 0)
		ft_error("invalid texture");
	close(fd);
}

void	fill_textures(t_cubscene *cubscene, t_lexer *lexer, char *find)
{
	int		i[2];
	char	*str[2];
	char	**types;

	i[0] = -1;
	types = fill_types();
	while (++i[0] < 4)
		if (!ft_strcmp(find, (char *) types[i[0]]))
			break ;
	if (i[0] == 4)
		ft_error("identifier invalid");
	if (cubscene->texture->path[i[0]])
		ft_error("repeated identifier");
	cubscene->texture->path[i[0]] = filter(lexer, identifier_value);
	str[1] = ft_strtrim(cubscene->texture->path[i[0]], " ");
	str[0] = ft_strrchr(str[1], '.');
	if (str[0] && ft_strcmp(str[0], ".xpm"))
		ft_error("texture should be on xpm forma");
	str[0] = ft_strchr(str[1], '/');
	if ((str[0] && !ft_strcmp(str[0], "/.xpm"))
		|| !ft_strcmp(cubscene->texture->path[i[0]], ".xpm"))
		ft_error("extension neeed a name -_-");
	path_validition(cubscene->texture->path[i[0]]);
	free(str[1]);
	free(types);
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == 32)
		lexer_advance(lexer);
}
