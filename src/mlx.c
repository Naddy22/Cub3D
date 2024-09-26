/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:34:59 by namoisan          #+#    #+#             */
/*   Updated: 2024/09/26 11:42:08 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	mouse_move(t_game *game)
{
	static int	x = -1;
	int			diff;
	int new_pos;

	if (x == -1)
	{
		mlx_get_mouse_pos(game->mlx_win, &x, &diff);
		return (0);
	}
	mlx_get_mouse_pos(game->mlx_win, &new_pos, &diff);
	diff = x - new_pos;
	x = new_pos;
	return (diff);
}

static void	exit_mlx(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_delete_texture(game->wall_tex[i]);
	mlx_delete_image(game->mlx_win, game->backgr);
	mlx_delete_image(game->mlx_win, game->foregr);
	mlx_delete_image(game->mlx_win, game->minimap[0]);
	mlx_delete_image(game->mlx_win, game->minimap[1]);
	mlx_terminate(game->mlx_win);
}

void	move(t_game *game, t_vect dir, double speed)
{
	t_vect	new_pos;
	t_vect	hitbox;

	new_pos = vect_sum(game->perp.pos, scal_product(speed, dir));
	hitbox = vect_sum(game->perp.pos, scal_product(speed * 1.1, dir));
	if (game->map[(int)hitbox.y][(int)hitbox.x] == '1')
		return ;
	game->perp.pos = new_pos;
	draw_walls(game);
	draw_minimap(&game->perp, game->minimap[0], game->map, game->map_height);
}

void	rotate_player(t_game *game, double speed)
{
	game->perp.dir = rotate(game->perp.dir, speed);
	game->perp.fov = rotate(game->perp.fov, speed);
	draw_walls(game);
	draw_minimap_perp(&game->perp, game->minimap[1]);
}

static void	player_key(void *param)
{
	t_game	*game;
	double	speed_norm;

	game = param;
	speed_norm = FPS * game->mlx_win->delta_time;
	rotate_player(game, mouse_move(game) * (-MOUSE_SPEED));
	if (mlx_is_key_down(game->mlx_win, MLX_KEY_W))
		move(game, game->perp.dir, SPEED * speed_norm);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_S))
		move(game, game->perp.dir, -SPEED * speed_norm);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_D))
		move(game, rotate(game->perp.dir, M_PI_2), SPEED * speed_norm);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_A))
		move(game, rotate(game->perp.dir, -M_PI_2), SPEED * speed_norm);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_RIGHT))
		rotate_player(game, ROT_SPEED * speed_norm);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_LEFT))
		rotate_player(game, -ROT_SPEED * speed_norm);
	else if (mlx_is_key_down(game->mlx_win, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_win);
}

// mlx_loop_hook(game->mlx_win, draw_walls, game);
void	mlx(t_game *game)
{
	game->mlx_win = mlx_init(W_WIDTH, W_HEIGHT, "---Cub3d---", true);
	if (!game->mlx_win)
		ft_free_error("MLX init\n", game);
	mlx_set_cursor_mode(game->mlx_win, MLX_MOUSE_DISABLED);
	draw_floor_and_ceiling(game);
	set_textures(game);
	game->foregr = mlx_new_image(game->mlx_win, W_WIDTH, W_HEIGHT);
	mlx_image_to_window(game->mlx_win, game->foregr, 0, 0);
	draw_walls(game);
	init_minimap(game);
	mlx_loop_hook(game->mlx_win, player_key, game);
	mlx_loop(game->mlx_win);
	exit_mlx(game);
}
