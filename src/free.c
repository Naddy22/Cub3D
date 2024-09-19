#include "cub3d.h"

void	ft_free_game(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 2)
		ft_free_verif((void *)&game->color[i]);
	i = -1;
	while (++i < 4)
		ft_free_verif((void *)&game->tex_path[i]);
	ft_free_split(game->map);
}

void	ft_free_all(t_game *game)
{
	ft_free_game(game);
}