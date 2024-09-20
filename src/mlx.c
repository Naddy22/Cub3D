#include "cub3d.h"

void	move(t_game *game, t_vect dir, double speed)
{
	t_vect new_pos;

	new_pos = vect_sum(game->perp.pos, scal_product(speed, dir));
	if (game->map[(int)new_pos.y][(int)new_pos.x] != '1')
	{
		game->perp.pos = new_pos;
	}
}

static void	player_key(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
			move(game, game->perp.dir, SPEED);
		else if (keydata.key == MLX_KEY_S)
			move(game, game->perp.dir, -SPEED);
	}
}

void	mlx(t_game *game)
{
	game->mlx_win = mlx_init(W_WIDTH, W_HEIGHT, "---Cub3d---", true);
	if (!game->mlx_win)
		ft_free_error("MLX init\n", game);
	draw_floor_and_ceiling(game);
	set_textures(game);
	game->foregr = mlx_new_image(game->mlx_win, W_WIDTH, W_HEIGHT);
	mlx_image_to_window(game->mlx_win, game->foregr, 0, 0);
	mlx_loop_hook(game->mlx_win, draw_walls, game);
	printf("game->perp.pos.x: %f, game->perp.pos.y: %f\n", game->perp.pos.x, game->perp.pos.y);
	printf("game->perp.dir.x: %f, game->perp.dir.y: %f\n", game->perp.dir.x, game->perp.dir.y);
	mlx_key_hook(game->mlx_win, player_key, game);
	mlx_loop(game->mlx_win);
	mlx_terminate(game->mlx_win);
}