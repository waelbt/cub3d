/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:13:56 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/20 19:28:55 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "cub3D.h"

typedef struct color	t_color;
typedef struct cubscene	t_cubscene;

typedef struct LEXER_STRUCT
{
	char			c;
	int				i;
	char			*contents;
}	t_lexer;

t_lexer	*init_lexer(char *contents);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
void	lexer_skip_comma(t_lexer *lexer);
t_color	*get_color(t_lexer *lexer);
void	fill_textures(t_cubscene *cubscene, t_lexer *lexer, char *find);
void	except_for_the_map(t_cubscene *cubscene, t_lexer *lexer, int *counter);
char	*lexer_get_current_char_as_string(t_lexer *lexer);
char	*filter(t_lexer *lexer, int (*condition)(t_lexer *));
void	skip_space_comma(t_lexer *lexer);
int		identifier(t_lexer *lexer);
int		identifier_value(t_lexer *lexer);
// int		identifier_texture_value(t_lexer *lexer);
int		identifier_color(t_lexer *lexer);

#endif