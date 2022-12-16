/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:01:18 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 19:26:04 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_is_not_iqual(char const *s, char c)
{
	size_t	len;
	int		i;
	size_t	stock;

	i = 0;
	stock = 0;
	len = ft_strlen(s);
	while (len--)
	{
		if (s[i] != c)
			stock++;
		i++;
	}
	if (stock == ft_strlen(s))
		return (1);
	return (0);
}

static int	last_handle(char const *s1, char const *set)
{
	size_t	len;

	len = ft_strlen(s1) - 1;
	while (len)
	{
		if (ft_is_not_iqual(set, s1[len]))
			return (len);
		len--;
	}
	return (0);
}

static int	first_handle(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (i < (ft_strlen(s1) - 1))
	{
		if (ft_is_not_iqual(set, s1[i]))
			return (i);
		i++;
	}
	return (ft_strlen(s1));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	first;
	size_t	last;

	if (!s1)
		return (0);
	first = first_handle(s1, set);
	last = last_handle(s1, set);
	if (last == 0 && first == ft_strlen(s1))
	{
		ptr = (char *) malloc(1);
		ptr[0] = '\0';
		return (ptr);
	}
	ptr = ft_substr(s1, first, (last - first + 1));
	if (!ptr)
		return (0);
	return (ptr);
}
/*
int main(void)
{
	//char *s1 = "  \t \t \n   \n\n\n\t";
	//printf("%d \n",first_handle(s1," \n\t"));
	//printf("%d \n",last_handle(s1," \n\t"));
	printf("%s", ft_strtrim("1234", ""));
}
*/
