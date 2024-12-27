/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historical.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:23:50 by ahavu             #+#    #+#             */
/*   Updated: 2024/12/27 16:35:21 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"

static void	clean_stash(char *stash)
{
	char	*tmp_stash;
	size_t	i;

	i = 0;
	tmp_stash = ft_strchr(stash, '\n') + 1;
	if ((size_t)tmp_stash != 1)
		while (tmp_stash[i])
		{
			stash[i] = tmp_stash[i];
			i++;
		}
	while (stash[i])
		stash[i++] = '\0';
}

static char	*join(char *next_line, char stash[BUFFER_SIZE + 1])
{
	char	*tmp;

	tmp = ft_strjoin(next_line, stash);
	if (!tmp)
	{
		free (next_line);
		return (NULL);
	}
	free (next_line);
	return (tmp);
}

static char	*fill_line(int fd, char *next_line)
{
	static char	stash[BUFFER_SIZE + 1];
	int			bytes_read;

	if (stash[0])
	{
		next_line = join(next_line, stash);
		if (ft_strchr(next_line, '\n'))
		{
			clean_stash(stash);
			return(next_line);
		}
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, stash, BUFFER_SIZE);
		if (bytes_read <= 0 && !next_line[0])
		{
			free(next_line);
			return (NULL);
		}
		if (bytes_read > 0)
			next_line = join(next_line, stash);
		if (ft_strchr(next_line, '\n'))
			break ;
	}
	clean_stash(stash);
	return (next_line);
}

static char	*clean_next_line(char *next_line)
{
	int	i;

	i = 0;
	if (!next_line)
		return (NULL);
	while (next_line[i] && next_line[i] != '\n')
		i++;
	if (next_line[i] == '\n')
	{	
		i++;
		while (next_line[i])
			next_line[i++] = '\0';
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	char	*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_line = ft_calloc(1, sizeof(char));
	if (!next_line)
		return (NULL);
	next_line = fill_line(fd, next_line);
	next_line = clean_next_line(next_line);
	return (next_line);
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
	int	fd;
	char *nextl;
	int	count = 0;

	//fd = open("txt_empty.txt", O_RDONLY);
	//fd = open("txt_nonl.txt", O_RDONLY);
	//fd = open("txt_only_one.txt", O_RDONLY);
	fd = open("txt_peepshow.txt", O_RDONLY);
	//fd = open("txt_test.txt", O_RDONLY);
	//fd = 0;
	if (!fd)
		return (-1);
	while (1)
	{
		nextl = get_next_line(fd);
		if (nextl == NULL)
			break ;
		count++;
		printf("|%d| %s", count, nextl);
		free (nextl);
	}
	close(fd);
	return (0);
}