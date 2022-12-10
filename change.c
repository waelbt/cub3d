
#include "src/include/cub3D.h"

int horizontal_walls(t_lexer *lexer)
{
	while(lexer->c != 32 && lexer->c)
	{
		if (lexer->c != '1' && lexer->c != 32)
			return 0;
		lexer_advance(lexer);
	}
	lexer_skip_whitespace(lexer);
	if (lexer->c)
		return 0;
	return 1;
}
int	vertical_walls_check(t_lexer lexer)
{
	while (lexer.i != 0 && lexer.c == 32)
	{
		lexer.i -= 1;
		lexer.c = lexer.contents[lexer.i];
	}
	if (lexer.c == 1)
		return 1;
	return 0;
}

int check_strangers(char c, int *counter)
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


void check_line(t_lexer *lexer)
{
	static int position_element;

	while(lexer->c)
	{
		if (lexer->c == 32 && !vertical_walls_check(*lexer))
			ft_error("vertical walls errorv");
		if (!check_strangers(lexer, &position_element))
			ft_error("undefine element");
		lexer_advance(lexer);
	}
	if (lexer->i != 0 && (lexer->contents[lexer->i - 1] != '1'
		|| lexer->contents[lexer->i - 1] != 32))
		ft_error("vertical walls error");
	if (position_element > 1)
		ft_error("more then one staring position !");
}