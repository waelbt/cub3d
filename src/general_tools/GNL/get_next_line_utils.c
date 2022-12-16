/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 10:44:17 by lchokri           #+#    #+#             */
/*   Updated: 2022/12/16 19:26:04 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*free_it(char **ptr, char **pt)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
	}
	return (NULL);
}

char	*ft_edited_strdup(const char *s1, char X)
{
	int		i;
	char	*p;

	i = 0;
	if (!s1)
		return (ft_edited_strdup("", '\0'));
	while (s1[i] && s1[i] != X)
		i++;
	p = malloc(sizeof(char) * i + 2);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && s1[i] != X)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = s1[i];
	p[++i] = '\0';
	return ((char *)p);
}

char	*ft_edited_strjoin(char **s1, char *s2)
{
	char	*str;
	size_t	i;
	int		j;

	j = 0;
	i = -1;
	if (!*s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(*s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[0][++i])
		str[i] = s1[0][i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free_it(s1, NULL);
	return (str);
}
