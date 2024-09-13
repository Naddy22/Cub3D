#include "cub3d.h"

static bool	ft_check_file_name(char *file)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strrchr(file, '.'))
	{
		tmp = ft_strrchr(file, '.');
		if (ft_strncmp(".cub", tmp, 5) == 0)
			return (true);
	}
	return (false);
}

static char *ft_get_infos(t_game *game, int fd, int *id_count)
{
	char	*line;
	int		result;

	line = NULL;
	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, "\n", 1) != 0)
		{
			result = ft_get_identifiers(game, line);
			if (result == -1)
				return (line);
			else
				(*id_count)++;
		}
		free(line);
	}
	return (NULL);
}

void parsing(char *file, t_game *game)
{
	int		fd;
	char	*map_line;
	int		id_count;

	id_count = 0;
	ft_bzero(game, sizeof(t_game));
	if (ft_check_file_name(file) != true)
		ft_error_exit("Filename must end with .cub\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error_exit("Opening file\n");
	map_line = ft_get_infos(game, fd, &id_count);
	if (!map_line || id_count != 6 || ft_is_valid_path(game) != true)
	{
		close(fd);
		ft_free_game(game);
		ft_error_exit("Identifiers invalid\n");
	}
	convert_color(game);
}
