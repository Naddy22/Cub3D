#include "cub3d.h"

void	ft_free_game(t_game *game)
{
	int i;

	
	ft_free_split(game->wall_tex);
	ft_free_split(game->color);
}

void	ft_free_all(t_game *game)
{
	ft_free_game(game);
}