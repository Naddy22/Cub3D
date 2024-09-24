#include "cub3d.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
		c == '\r')
		return (true);
	return (false);
}

bool	is_line_empty(char *line)
{
	while (*line)
	{
		if (ft_isspace(*line) == false)
			return (false);
		line++;
	}
	return (true);
}