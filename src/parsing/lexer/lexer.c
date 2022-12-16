/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:16:39 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 20:03:06 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	if (!contents)
		return (NULL);
	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer	*lexer)
{
	if (lexer->c != '\0' && lexer->i < (int) ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

char	*lexer_get_current_char_as_string(t_lexer	*lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

void	lexer_skip_comma(t_lexer *lexer)
{
	int	counter;

	counter = 0;
	while (lexer->c == 32 || lexer->c == ',')
	{
		if (lexer->c == ',')
			counter++;
		lexer_advance(lexer);
	}
	if (counter != 1)
		ft_error("syntax error missing comma or an additional one");
}

char	*filter(t_lexer *lexer, int (*condition)(t_lexer *))
{
	char	*value;
	char	*tmp;
	char	*s;

	lexer_skip_whitespace(lexer);
	value = ft_strdup("");
	while (condition(lexer))
	{
		s = lexer_get_current_char_as_string(lexer);
		tmp = value;
		value = ft_strjoin(value, s);
		free(tmp);
		free(s);
		lexer_advance(lexer);
	}
	return (value);
}
