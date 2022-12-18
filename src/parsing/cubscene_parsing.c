/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubscene_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 20:12:03 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	cubscene->ceilling = NULL;
	while (++i < 4)
		cubscene->texture->path[i] = NULL;
	return (cubscene);
}

void	add_lines(t_cubscene *cubscene, char *str)
{
	char	**new_map;
	int		index;

	index = -1;
	new_map = malloc(sizeof(char *) * (++cubscene->map_height + 1));
	while (cubscene->map[++index])
		new_map[index] = cubscene->map[index];
	new_map[index++] = str;
	new_map[index] = NULL;
	free(cubscene->map);
	cubscene->map = new_map;
}

void	check_map(t_cubscene *cubscene)
{
	char		**chunks;
	static int	position_element;
	int			i[2];

	i[0] = -1;
	if (!cubscene->map_height)
		ft_error("missing map -_-");
	hard_code_time(cubscene);
	while (++i[0] < cubscene->map_height)
	{
		chunks = ft_split(cubscene->map[i[0]], 32);
		i[1] = -1;
		while (chunks[++i[1]])
		{
			check_undefined_elements(chunks[i[1]], &position_element);
			if (i[0] == 0 || i[0] == cubscene->map_height - 1)
				horizontal_walls(chunks[i[1]]);
			else if (chunks[i[1]][0] != '1'
				|| chunks[i[1]][ft_strlen(chunks[i[1]]) - 1] != '1')
				ft_error("unclosed vertical walls");
		}
		ft_free(chunks);
	}
	if (position_element != 1)
		ft_error("invalid staring position !");
}

void	except_for_the_map(t_cubscene *cubscene, t_lexer *lexer, int *counter)
{
	char	*key;

	key = filter(lexer, identifier);
	if (!ft_strcmp(key, "F"))
	{
		if (cubscene->floor)
			ft_error("repeated identifier");
		cubscene->floor = get_color(lexer);
	}
	else if (!ft_strcmp(key, "C"))
	{
		if (cubscene->ceilling)
			ft_error("repeated identifier");
		cubscene->ceilling = get_color(lexer);
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

void	parsing(int fd, t_cubscene *cubscene)
{
	t_lexer		*lexer;
	static int	counter;

	while (1)
	{
		lexer = init_lexer(get_next_line(fd));
		if (!lexer)
			break ;
		lexer_skip_whitespace(lexer);
		if (lexer->c == '\n')
		{
			if (!cubscene->map_height)
				continue ;
			ft_error("can't have empty lines inside a map -_-");
		}
		if (counter < 6)
			except_for_the_map(cubscene, lexer, &counter);
		else
			add_lines(cubscene, ft_strtrim(lexer->contents, "\n"));
		free(lexer->contents);
		free(lexer);
	}
	check_map(cubscene);
	if (counter != 6)
		ft_error("missing identifier");
}