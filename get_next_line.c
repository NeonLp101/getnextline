/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lernst <lernst@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:09:09 by lernst            #+#    #+#             */
/*   Updated: 2026/06/11 15:35:08 by lernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(stash), NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(stash, SEP))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), free(stash), NULL);
		buf[bytes] = '\0';
		stash = ft_strjoin(stash, buf);
		if (!stash)
			break ;
	}
	free(buf);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!stash || !*stash)
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != SEP)
		len++;
	if (stash[len] == SEP)
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*trim_stash(char *stash)
{
	char	*rest;
	char	*sep_pos;

	sep_pos = ft_strchr(stash, SEP);
	if (!sep_pos || !sep_pos[1])
		return (free(stash), NULL);
	rest = ft_strjoin(NULL, sep_pos + 1);
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = trim_stash(stash);
	return (line);
}
