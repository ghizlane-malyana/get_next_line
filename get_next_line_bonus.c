/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:01:31 by gmalyana          #+#    #+#             */
/*   Updated: 2024/01/25 20:52:02 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_copy(char *line, char *return_line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i])
	{
		return_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		return_line[i++] = '\n';
	return_line[i] = '\0';
	return (return_line);
}

char	*ft_read_buff(int fd, char *line)
{
	char	*finline;
	int		buff;

	buff = 1;
	while (buff)
	{
		finline = (char *)malloc((size_t)BUFFER_SIZE + 1);
		if (!finline)
			return (free(line), line = NULL, NULL);
		buff = read(fd, finline, BUFFER_SIZE);
		if (buff <= 0)
			return (free(finline), finline = NULL, line);
		finline[buff] = '\0';
		line = ft_strjoin(line, finline);
		free(finline);
		if (!line)
			return (NULL);
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*rest;
	char		*return_line;
	int			i;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || read(fd, line, 0) < 0)
		return (free(line[fd]), line[fd] = NULL, NULL);
	line[fd] = ft_read_buff(fd, line[fd]);
	if (!line[fd] || !*line[fd])
		return (free(line[fd]), line[fd] = NULL, NULL);
	i = 0;
	while (line[fd][i] != '\n' && line[fd][i])
		i++;
	if (line[fd][i] == '\n')
		i++;
	return_line = (char *)malloc(i + 1);
	if (!return_line)
		return (free(line[fd]), line[fd] = NULL, NULL);
	return_line = ft_copy(line[fd], return_line);
	rest = ft_strdup(line[fd] + i);
	free(line[fd]);
	line[fd] = ft_strdup(rest);
	return (free(rest), return_line);
}
