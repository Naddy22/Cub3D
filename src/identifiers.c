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
		*texture = ft_strdup(trim + 3);
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
		return (ft_set_identifier(game->no_texture, "NO ", line));
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		return (ft_set_identifier(game->so_texture, "SO ", line));
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		return (ft_set_identifier(game->we_texture, "WE ", line));
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		return (ft_set_identifier(game->ea_texture, "EA ", line));
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		return (ft_set_identifier(game->f_color, "F ", line));
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		return (ft_set_identifier(game->c_color, "C ", line));
	return (-1);
}