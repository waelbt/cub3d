/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:38:15 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/20 17:38:16 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int		identifier(t_lexer *lexer)
{
	if (lexer->c == '\n' || lexer->c == '\0')
		ft_error("identifier without value");
	if (lexer->c == 32)
		return 0;
	return 1;
}

int		identifier_value(t_lexer *lexer)
{
	if (lexer->c == '\0')
		ft_error("invalid identifier");
	if (lexer->c == '\n')
		return 0;
	return 1;
}

// int		identifier_texture_value(t_lexer *lexer)
// {
// 	if (lexer->c == '\0')
// 		ft_error("invalid identifier");
// 	if (lexer->c == '\n')
// 		return 0;
// 	return 0;
//}

int		identifier_color(t_lexer *lexer)
{
	if (lexer->c == '\0')
		ft_error("invalid identifier");
	if (lexer->c == ',' || lexer->c == '\n' || lexer->c == 32)
		return 0;
	return 1;
}
