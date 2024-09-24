#include "cub3d.h"

void	ft_error_exit(char *error)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	ft_free_error(char *error, t_game *game)
{
	ft_free_game(game);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	exit(EXIT_FAILURE);
}
