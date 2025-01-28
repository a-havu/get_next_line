#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

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
		{
			printf("%s", nextl);
			break ;
		}
		count++;
		printf("|%d| %s", count, nextl);
		free (nextl);
	}
	close(fd);
	return (0);
}