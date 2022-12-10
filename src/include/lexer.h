/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:13:56 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/09 19:46:29 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "libft.h"
#include "cub3D.h"

typedef struct LEXER_STRUCT
{
	char			c;
	int				i;
	char			*contents;
}	t_lexer;

t_lexer	*init_lexer(char *contents);

void	lexer_advance(t_lexer *lexer);

void	lexer_skip_whitespace(t_lexer *lexer);

void lexer_skip_comma(t_lexer *lexer);

char	*lexer_get_current_char_as_string(t_lexer *lexer);

char *filter(t_lexer *lexer, int (*condition)(t_lexer *));
// t_token	*lexer_get_next_token(t_lexer *lexer);

// t_token	*lexer_collect_string(t_lexer *lexer, int type);

// char	*lexer_handle_quotes(t_lexer *lexer, int c);


void	skip_space_comma(t_lexer *lexer);

#endif