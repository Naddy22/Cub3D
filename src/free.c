#include "cub3d.h"

void	ft_free_game(t_game *game)
{
	ft_free_verif((void *)&game->so_texture);
	ft_free_verif((void *)&game->no_texture);
	ft_free_verif((void *)&game->ea_texture);
	ft_free_verif((void *)&game->we_texture);
	ft_free_verif((void *)&game->f_color);
	ft_free_verif((void *)&game->c_color);
}

void	ft_free_all(t_game *game)
{
	ft_free_game(game);
}