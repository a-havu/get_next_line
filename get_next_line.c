/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:23:50 by ahavu             #+#    #+#             */
/*   Updated: 2024/12/30 10:54:11 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* "clean" the stash[]: if there's a newline character,
overwrite stash[] from index 0 with characters that appear after the newline character */
static void	clean_stash(char *stash)
{
	char	*tmp_stash;
	size_t	i;

	i = 0;
	tmp_stash = ft_strchr(stash, '\n');
	if (tmp_stash)
	{
		tmp_stash++;
		while (tmp_stash[i])
		{
			stash[i] = tmp_stash[i];
			i++;
		}
	}
	while (stash[i])
		stash[i++] = '\0';
}

/* join the stash to next_line by using a temporary char array */
static char	*join(char *next_line, char stash[BUFFER_SIZE + 1])
{
	char	*tmp;

	tmp = ft_strjoin(next_line, stash);
	if (!tmp)
		return (NULL);
	free (next_line);
	return (tmp);
}

/* read from the file descriptor to stash[] */
static char	*fill_line(int fd, char *next_line, char stash[BUFFER_SIZE + 1])
{
	int			bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		clean_stash(stash);
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

/* "clean" the returnable next_line from all characters that appear after a newline character - if one occurs */
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
	static char	stash[BUFFER_SIZE + 1]; // a static variable that will store the BUFFER_SIZE (+1) amount of chars
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_line = ft_calloc(1, sizeof(char)); // allocate memory for the next line to be gotten from the file descriptor
	if (!next_line)
		return (NULL);
	if (stash[0])
	{
		next_line = join(next_line, stash); // add the contents of stash[] to next_line, if stash is not empty
		if (ft_strchr(next_line, '\n'))
		{
			clean_stash(stash);
			next_line = clean_next_line(next_line);
			return (next_line);
		}
	}
	next_line = fill_line(fd, next_line, stash);
	next_line = clean_next_line(next_line);
	return (next_line);
}
