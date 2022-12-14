/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:07:27 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 19:26:04 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	char		*p;

	i = 0;
	p = (char *) s;
	while (i <= ft_strlen(s))
	{
		if (*(p + i) == (char )c)
			return (p + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char s[] = "tripouille";
	printf("%s \n",ft_strchr(s, 't' + 256));
	printf("%s",strchr(s, 't' + 256));
}
*/