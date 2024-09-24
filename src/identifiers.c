#include "cub3d.h"

static int ft_set_identifier(char **texture, char *id, char *line)
{
	char *trim;
	
	trim = ft_strtrim(line, " \t\n\v\f\r");
	if (*texture != NULL)
	{
		free(trim);
		free(line);
		ft_error_exit("Map identifier can't be defined twice\n");
	}
	if (!ft_strncmp(trim, "F ", 2) || !ft_strncmp(trim, "C ", 2))
		*texture = ft_set_color(trim, line);
	else if (ft_strncmp(trim, id, 3) == 0)
	{
		*texture = ft_strtrim(trim + 3, " ");
		if (*texture == NULL)
		{
			free(trim);
			free(line);
			ft_error_exit("Malloc failed\n");
		}
	}
	free(trim);
	return (SUCCESS);
}

int	ft_get_identifiers(t_game *game, char *line)
{
	if (ft_strnstr(line, "NO", ft_strlen(line)))
		return (ft_set_identifier(&game->tex_path[NORTH], "NO ", line));
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		return (ft_set_identifier(&game->tex_path[SOUTH], "SO ", line));
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		return (ft_set_identifier(&game->tex_path[WEST], "WE ", line));
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		return (ft_set_identifier(&game->tex_path[EAST], "EA ", line));
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		return (ft_set_identifier(&game->color[FLOOR], "F ", line));
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		return (ft_set_identifier(&game->color[CEILING], "C ", line));
	return (-1);
}

static int ft_open_texture(char *texture)
{
	int fd;

	if (texture == NULL)
		return (FAIL);
	fd = open(texture, O_RDONLY);
	if (fd < 0)
		return (FAIL);
	close(fd);
	return (SUCCESS);
}

bool	ft_is_valid_path(t_game *game)
{
	if (ft_open_texture(game->tex_path[NORTH]) != SUCCESS)
		return (false);
	if (ft_open_texture(game->tex_path[SOUTH]) != SUCCESS)
		return (false);
	if (ft_open_texture(game->tex_path[WEST]) != SUCCESS)
		return (false);
	if (ft_open_texture(game->tex_path[EAST]) != SUCCESS)
		return (false);
	return (true);
}