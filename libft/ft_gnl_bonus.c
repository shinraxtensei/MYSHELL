/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:36:06 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strdel(char **saved)
{
	free(saved[0]);
	saved[0] = NULL;
}

int	empty_line(char **line)
{
	*line = (char *)malloc(sizeof(char) * 1);
	**line = '\0';
	return (0);
}

static void	fill_static(char *buf, char **saved)
{
	char	*temp;

	if (!*saved)
		*saved = ft_strdup(buf);
	else
	{
		temp = ft_strjoin(*saved, buf);
		free(*saved);
		*saved = temp;
	}
}

static int	create_line(char **line, char **saved)
{
	int		i;
	char	*cache;

	i = 0;
	while (saved[0][i] != '\n' && saved[0][i] != '\0')
		i++;
	if (saved[0][i] == '\n')
		*line = ft_substr(*saved, 0, i);
	if (saved[0][i] == '\0')
	{
		*line = ft_substr(*saved, 0, i);
		ft_strdel(saved);
		return (0);
	}
	else
	{
		cache = ft_strdup(*saved + (i + 1));
		free(*saved);
		*saved = cache;
		if (*saved[0] == '\0')
			ft_strdel(saved);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*saved[1024];
	int			ret;

	if ((read(fd, 0, 0) == -1) || fd < 0 || fd >= 1024
		|| !line || BUFFER_SIZE < 1)
		return (-1);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		fill_static(buf, &saved[fd]);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	if (!ret && !saved[fd])
		return (empty_line(line));
	return (create_line(line, &saved[fd]));
}
