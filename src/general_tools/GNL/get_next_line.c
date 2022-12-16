/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:40:19 by lchokri           #+#    #+#             */
/*   Updated: 2022/12/16 19:26:04 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <string.h>*/

#include "../../includes/get_next_line.h"
#ifdef BUFFER_SIZE

/*
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' )
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s1, char X)
{
	int		i;
	char	*p;

	i = 0;
	if (!s1)
		return(ft_strdup("", '\0'));
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

char	*ft_strjoin(char **s1, char *s2)
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
*/
char	*ft_keep_going(char **saved)
{
	char	*tmp;
	char	*toret;

	toret = ft_edited_strdup(*saved, '\n');
	if (ft_strchr(*saved, '\n'))
	{
		tmp = *saved;
		*saved = ft_edited_strdup(ft_strchr(*saved, '\n') + 1, '\0');
		free_it(&tmp, NULL);
	}
	else
		free_it(saved, NULL);
	return (toret);
}
// recoding my func got me thinking:
// 1 - i have to return null in case buff wasn't allocated.
// 2- there's no need to cast in strdup's return.
// 3- same for strchr, but ik hadik hit kant 3andi const f prototype so ye

char	*get_next_line(int fd)
{
	char		*buf;
	char		*toret;
	static char	*saved = NULL;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!saved)
		saved = ft_edited_strdup(saved, '\0');
	ret = 1;
	while (ft_strchr(saved, '\n') == 0 && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (free_it(&saved, &buf));
		buf[ret] = '\0';
		saved = ft_edited_strjoin(&saved, buf);
	}
	toret = ft_keep_going(&saved);
	free_it(&buf, NULL);
	if (*toret == '\0')
		return (free_it(&toret, &saved));
	return (toret);
}
#endif
/*
#include <stdio.h>
#include <fcntl.h>

int main()
{
char *s;
	int fd = open("get_next_line.c", O_RDONLY);
	int i = 0;
	while(i<12)
	{
		s = get_next_line(fd);
		printf("%s", s);
		free(s);
		i++;
	}
	while(1)
		continue ;
	system("leaks ./a.out");
	return (0);
}*/
