/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:43:24 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/10 17:20:03 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/include/cub3D.h"


void ft_error(char *Raison)
{
	ft_putstr_fd("Error\nRaison : ", STDERR);
	ft_putstr_fd(Raison, STDERR);
	exit(127);
}

int extension_check(char *file)
{
	char	*tmp;
	int		fd;
	
	fd = -1;
	tmp = ft_strrchr(file, '.');
	if (tmp && !ft_strcmp(tmp, ".cub")
		&& ft_strlen(tmp) != ft_strlen(file))
		fd = open(file, O_RDONLY);
	if(fd < 0)
		ft_error("invalid extension");
	return fd;
}

int identifier(t_lexer *lexer)
{
	if (lexer->c == '\n' || !lexer->c)
		ft_error("identifier without value");
	if (lexer->c == 32)
		return 0;
	return 1;
}

int identifier_value(t_lexer *lexer)
{
	if (!lexer->c)
		ft_error("identifier without value");
	if (lexer->c == 32 || lexer->c == '\n')
		return 0;
	return 1;
}

int identifier_color(t_lexer *lexer)
{
	if (!lexer->c)
		ft_error("identifier without value");
	if (lexer->c == 32 || lexer->c == ',' || lexer->c == '\n')
		return 0;
	return 1;
}

void	fill_textures(t_cubscene *cubscene, t_lexer *lexer, char *find)
{
	int i;

	i = -1;
	while(++i < TYPES_SIZE)
		if (!ft_strcmp(find, (char *) TYPES[i]))
			break;
	if (i == TYPES_SIZE)
		ft_error("identifier invalid");
	if(cubscene->texture->path[i])
		ft_error("repeated identifier");
	cubscene->texture->path[i] = filter(lexer,identifier_value);
}

int color_check(char *str)
{
	int i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
		if (!str[i])
			return (-1);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = ft_atoi(str);
	free(str);
	return (i);
}

t_color *get_color(t_lexer *lexer)
{
	t_color	*color;

	color = (t_color *) malloc(sizeof(t_color));
	color->red = color_check(filter(lexer, identifier_color));
	lexer_skip_comma(lexer);
	color->green = color_check(filter(lexer, identifier_color));
	lexer_skip_comma(lexer);
	color->blue = color_check(filter(lexer, identifier_color));
	if (color->red < 0 || color->blue < 0
		|| color->green < 0	|| color->red > 255
		|| color->blue > 255 || color->green > 255)
		ft_error("out of range");
	return color;
}

void except_for_the_map(t_cubscene *cubscene, t_lexer *lexer)
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
		if (cubscene->Ceilling)
			ft_error("repeated identifier");
		cubscene->Ceilling = get_color(lexer);
	}
	else
		fill_textures(cubscene, lexer, key);
	free(key);
	key = filter(lexer, identifier_value);
	if (ft_strcmp(key, ""))
		ft_error("to many value for an identifier");
	free(key);
}

void add_lines(t_cubscene *cubscene ,char *str)
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

void ft_free(char **str)
{
	int i;

	i = -1;
	while(str[++i])
		free(str[i]);
	free(str);
}


void horizontal_walls(char *str)
{
	int	i;
	int len;

	i = -1;
	len = ft_strlen(str);
	while (++i < len)
		if (str[i] != '1')
			ft_error("unclosed horizontal walls");
}

int check_element(char c, int *counter)
{
	char 	*element;
	int		i;
	
	i = -1;
	element = " 01NSEW";
	while (element[++i])
	{
		if (c == element[i])
		{
			if (i > 2)
				(*counter)++;
			return 1;
		}
	}
	return 0;
}

void check_strangers(char *str)
{
	char 	*element;
	static int 	position_element;
	int		i;
	int 	j;
	
	i = -1;
	element = " 01NSEW";
	while (str[++i])
	{
		j = -1;
		if (!check_element(str[i], &position_element))
			ft_error("undefine element");
	}
	if (position_element > 1)
		ft_error("more then one staring position !");
}

void check_map(t_cubscene *cubscene)
{
	char	**chunks;
	int		i;
	int		j;

	i = -1;
	while (++i < cubscene->map_height)
	{
		chunks = ft_split(cubscene->map[i], 32);
		j = -1;
		while(chunks[++j])
		{
			check_strangers(chunks[j]);
			if (i == 0 || i == cubscene->map_height - 1)
				horizontal_walls(chunks[j]);
			else if (chunks[j][0] != '1' || chunks[j][ft_strlen(chunks[j]) - 1] != '1')
				ft_error("unclosed vertical walls");
		}
		ft_free(chunks);
	}
}

void parsing(int fd, t_cubscene *cubscene)
{
	t_lexer	*lexer;
	int		counter;

	counter = 0;
	while(1)
	{
		lexer = init_lexer(get_next_line(fd));
		if (!lexer)
			break ;
		lexer_skip_whitespace(lexer);
		if (lexer->c == '\n')
		{
			if (!cubscene->map_height)
				continue;
			ft_error("can't have empty lines inside a map -_-");
		}
		if (counter < 6)	
			except_for_the_map(cubscene, lexer), counter++;
		else
			add_lines(cubscene , ft_strtrim(lexer->contents, "\n"));
		free(lexer->contents);
		free(lexer);
	}
	check_map(cubscene);
	if (counter != 6)
		ft_error("missing identifier");
	if (!cubscene->map_height)
		ft_error("missing map -_-");
}

int main(int argc, char **argv)
{
	t_cubscene *cubscene;

	if (argc != 2)
		ft_error(strerror(EINVAL));
	cubscene = new_cubscene();
	parsing(extension_check(argv[1]), cubscene);
	printf("NO %s\n", cubscene->texture->path[NO]);
	printf("SO %s\n", cubscene->texture->path[SO]);
	printf("WE %s\n", cubscene->texture->path[WE]);
	printf("EA %s\n", cubscene->texture->path[EA]);
	printf("Ceilling %d %d %d\n", cubscene->Ceilling->red, cubscene->Ceilling->green, cubscene->Ceilling->blue);
	printf("floor %d %d %d\n", cubscene->floor->red, cubscene->floor->green, cubscene->floor->blue);
	int i = -1;
	while (cubscene->map[++i])
		printf("%s\n", cubscene->map[i]);
    return (EXIT_SUCCESS);
}