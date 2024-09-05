#include "cub3d.h"

static bool	check_file_name(char *file)
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

void parsing(char *file, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	if (check_file_name(file) == true)
	{
		ft_putstr_fd("Good file\n", 1);
	}
	else
		error_exit("Filename must end with .cub\n");
}