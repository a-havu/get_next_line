/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:23:50 by ahavu             #+#    #+#             */
/*   Updated: 2024/12/02 16:04:52 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join(char *next_line, char *stash)
{
	char *tmp;

	tmp = ft_strjoin(next_line, stash);
	//printf("tmp: %s\n", tmp);
	printf("stash: %s\n", stash);
	return (tmp);
}

static char	*fill_buf(int fd, char *next_line)
{
	static char	*stash;
	int			bytes_read;
	
	stash = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!stash)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, stash, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(stash);
			return (NULL);
		}
		next_line = join(next_line, stash);
		//printf("next_line: %s\n", next_line);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (next_line);
}

char *get_next_line(int fd)
{
    static char	*next_line;
    
	if (!fd)
		return (NULL);
	next_line = ft_calloc(70, sizeof(char));
	if (!next_line)
		return (NULL);
	next_line = fill_buf(fd, next_line);
    return(next_line);
}

int main()
{
	int	fd;
	char *nextl;
	int	count = 0;

	fd = open("test.txt", O_RDONLY);
	if (!fd)
		return (-1);
	while (1)
	{
		nextl = get_next_line(fd);
		if (nextl == NULL)
			break ;
		count++;
		printf("[%d]: %s\n", count, nextl);
		nextl = NULL;
		free(nextl);
	}
	close(fd);
	return (0);
}