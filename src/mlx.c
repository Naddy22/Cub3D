#include "cub3d.h"

static void	exit_mlx(t_game *game)
{
	int i;

	ft_free_all(game);
	i = -1;
	while (++i < 4)
		mlx_delete_texture(game->wall_tex[i]);
	mlx_delete_image(game->mlx_win, game->backgr);
	mlx_delete_image(game->mlx_win, game->foregr);
	mlx_terminate(game->mlx_win);
	exit(EXIT_SUCCESS);
}

void	move(t_game *game, t_vect dir, double speed)
{
	t_vect new_pos;

	new_pos = vect_sum(game->perp.pos, scal_product(speed, dir));
	// if (game->map[(int)new_pos.y][(int)new_pos.x] != '1')
	// {
	// 	game->perp.pos = new_pos;
	// }
	if (game->map[(int)game->perp.pos.y][(int)(new_pos.x + (dir.x * 0.1))] != '1')
		game->perp.pos.x = new_pos.x;
	if (game->map[(int)(new_pos.y + (dir.y * 0.1))][(int)game->perp.pos.x] != '1')
		game->perp.pos.y = new_pos.y;
}

void	rotate_player(t_game *game, double speed)
{
	game->perp.dir = rotate(game->perp.dir, speed);
	game->perp.fov = rotate(game->perp.fov, speed);
}

static void	player_key(void *param)
{
	t_game *game;

	game = param;
	if (mlx_is_key_down(game->mlx_win, MLX_KEY_W))
		move(game, game->perp.dir, SPEED);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_S))
		move(game, game->perp.dir, -SPEED);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_D))
		move(game, rotate(game->perp.dir, M_PI_2), SPEED);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_A))
		move(game, rotate(game->perp.dir, -M_PI_2), SPEED);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_RIGHT))
		rotate_player(game, ROT_SPEED);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_LEFT))
		rotate_player(game, -ROT_SPEED);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_ESCAPE))
	{
		ft_putstr_fd("Game exited successfully\n", 1);
		exit_mlx(game);
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
	mlx_loop_hook(game->mlx_win, player_key, game);
	mlx_loop(game->mlx_win);
	exit_mlx(game);
}