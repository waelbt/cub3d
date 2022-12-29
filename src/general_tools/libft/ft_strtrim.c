/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:18:23 by lchokri           #+#    #+#             */
/*   Updated: 2022/12/29 16:24:17 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		l;
	char	*p;

	if (!s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	l = ft_strlen(s1);
	while (l > 0 &&ft_strchr(set, s1[l - 1]))
		l--;
	p = malloc((l + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, l + 1);
	return (p);
}
