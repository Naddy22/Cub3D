#include "cub3d.h"

void	mlx(t_game *game)
{
	game->mlx_win = mlx_init(W_WIDTH, W_HEIGHT, "---Cub3d---", true);
	if (!game->mlx_win)
		ft_free_error("MLX init\n", game);
	game->foregr = mlx_new_image(game->mlx_win, W_WIDTH, W_HEIGHT);
	mlx_image_to_window(game->mlx_win, game->foregr, 0, 0);
	mlx_loop_hook(game->mlx_win, draw_walls, game);
	mlx_loop(game->mlx_win);
	//draw_view(game);
}