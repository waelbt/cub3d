/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubscene_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/29 18:33:00 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_cubscene	*new_cubscene(void)
{
	t_cubscene	*cubscene;
	int			i;

	i = -1;
	cubscene = (t_cubscene *) malloc(sizeof(t_cubscene));
	cubscene->texture = (t_texture *) malloc(sizeof(t_texture));
	cubscene->texture->path = (char **) malloc(sizeof(char *) * 5);
	cubscene->floor = 0;
	cubscene->canvas = NULL;
	cubscene->mlx = NULL;
	cubscene->win = NULL;
	cubscene->player = NULL;
	cubscene->map_width = 0;
	cubscene->rays = NULL;
	cubscene->counter = 0;
	cubscene->map = malloc(sizeof(char *));
	cubscene->map[0] = NULL;
	cubscene->map_height = 0;
	cubscene->frame_rate = 30;
	cubscene->ceilling = 0;
	while (++i < 4)
		cubscene->texture->path[i] = NULL;
	return (cubscene);
}

int	posi(char *str)
{
	int	counter;

	counter = -1;
	while (str[++counter])
	{
		if (str[counter] == 'N' || str[counter] == 'S'
			|| str[counter] == 'E' || str[counter] == 'W')
			return (counter);
	}
	return (-1);
}

int	norm_parsing(t_cubscene *cubscene, t_lexer *lexer, int *i)
{
	lexer_skip_whitespace(lexer);
	if (lexer->c == '\n')
	{
		if (cubscene->map_height)
			i[0] = 1;
		free_lexer(lexer);
		return (1);
	}
	if (i[0])
		ft_error("you can't have extra elements after map elements");
	if (i[1] < 6)
		except_for_the_map(cubscene, lexer, &i[1]);
	else
		add_lines(cubscene, ft_strtrim(lexer->contents, "\n"));
	free_lexer(lexer);
	return (0);
}

void	parsing(int fd, t_cubscene *cubscene)
{
	t_lexer		*lexer;
	static int	i[2];

	while (1)
	{
		lexer = init_lexer(get_next_line(fd));
		if (!lexer)
			break ;
		if (norm_parsing(cubscene, lexer, i))
			continue ;
	}
	check_map(cubscene);
	if (i[1] != 6)
		ft_error("missing identifier");
}
