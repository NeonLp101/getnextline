#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac > 1)
		fd = open(av[1], 0);
	else
		fd = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}