/* tester main — norm does not apply here */
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef SEP
# define SEP '\n'
#endif

static size_t	xlen(const char *s)
{
	size_t	i = 0;

	while (s[i])
		i++;
	return (i);
}

/* prints every line as "<len>:<raw content>" so the reference can be
** compared byte-exactly; also asserts GNL invariants */
static int	dump_fd(int fd, int max)
{
	char	*line;
	size_t	i, len;
	int		n = 0;

	while ((line = get_next_line(fd)) != NULL)
	{
		len = xlen(line);
		if (len == 0)
			return (free(line), fprintf(stderr, "empty string returned (should be NULL or contain data)\n"), 3);
		for (i = 0; i + 1 < len; i++)
			if (line[i] == SEP)
				return (free(line), fprintf(stderr, "SEP found in the MIDDLE of a returned line\n"), 3);
		printf("%zu:", len);
		fwrite(line, 1, len, stdout);
		free(line);
		if (max && ++n >= max)
			return (0);
	}
	if (get_next_line(fd) != NULL || get_next_line(fd) != NULL)
		return (fprintf(stderr, "non-NULL returned AFTER EOF\n"), 4);
	return (0);
}

static int	invalid_tests(void)
{
	char	*l;
	int		fd;

	l = get_next_line(-1);
	if (l)
		return (free(l), fprintf(stderr, "fd=-1 returned non-NULL\n"), 5);
	l = get_next_line(9999);
	if (l)
		return (free(l), fprintf(stderr, "fd=9999 returned non-NULL\n"), 5);
	fd = open("/dev/null", O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		l = get_next_line(fd);
		if (l)
			return (free(l), fprintf(stderr, "closed fd returned non-NULL\n"), 5);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	i, fd, ret;

	if (ac >= 2 && strcmp(av[1], "--invalid") == 0)
		return (invalid_tests());
	if (ac >= 2 && strcmp(av[1], "--stdin") == 0)
		return (dump_fd(0, 0));
	if (ac >= 3 && strcmp(av[1], "--partial") == 0)
	{
		fd = open(av[2], O_RDONLY);
		if (fd < 0)
			return (1);
		ret = dump_fd(fd, 3);
		close(fd);
		return (ret);
	}
	for (i = 1; i < ac; i++)
	{
		fd = open(av[i], O_RDONLY);
		if (fd < 0)
			return (fprintf(stderr, "cannot open %s\n", av[i]), 1);
		ret = dump_fd(fd, 0);
		close(fd);
		if (ret)
			return (ret);
	}
	return (0);
}
