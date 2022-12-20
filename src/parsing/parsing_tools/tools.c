/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:38:35 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/20 17:39:46 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void		ft_free(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void		ft_error(char *raison)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(raison, 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

int			extension_check(char *file)
{
	int fd;
	char *extension;

	extension = ft_strrchr(file, '.');
	if (!extension)
		ft_error("extension need to on .ber format");
	if (ft_strlen(extension) == ft_strlen(file))
		ft_error("extension need a name -_-");
	fd = open(file, 0);
	if (fd < 0)
		ft_error(strerror(EBADF));
	return fd;
}


int str_isdigit(char *str)
{
	int i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if(!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	color_check(char *str)
{
	int number;

	if (!str_isdigit(str))
		ft_error("invalid color");
	number = ft_atoi(str);
	if (number < 0 || number > 255)
		ft_error("out of range");
	return (number);
}
