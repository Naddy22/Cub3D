#include "cub3d.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
		c == '\r')
		return (true);
	return (false);
}

char	get_map_tile(char **map, t_vect pos, int m)
{
	int	x;
	int	y;

	x = (int)pos.x;
	y = (int)pos.y;
	if (y < 0 || y >= m || x < 0 || x >= ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}