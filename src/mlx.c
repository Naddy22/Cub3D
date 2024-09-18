#include "cub3d.h"

void	mlx(t_game *game)
{
	game->mlx_win = mlx_init(W_WIDTH, W_HEIGHT, "---Cub3d---", true);
	if (!game->mlx_win)
		ft_free_error("MLX init\n", game);
	mlx_loop(game->mlx_win);
	//draw_view(game);
}