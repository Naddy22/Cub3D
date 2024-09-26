/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:34:59 by namoisan          #+#    #+#             */
/*   Updated: 2024/09/26 16:19:20 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(t_game *game)
{
	static int	x = -1;
	int			diff;
	int			new_pos;

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

void	move(t_game *game, t_vect dir, double speed)
{
	t_vect	new_pos;
	t_vect	hitbox;

	new_pos = vect_sum(game->perp.pos, scal_product(speed, dir));
	hitbox = vect_sum(game->perp.pos, scal_product(speed * 1.1, dir));
	if (get_map_tile(game->map, (int)hitbox.x, (int)hitbox.y, game->map_h) != '0')
		return ;
	game->perp.pos = new_pos;
	draw_walls(game);
	draw_minimap(&game->perp, game->minimap[0], game->map, game->map_h);
}

void	rotate_player(t_game *game, double speed)
{
	game->perp.dir = rotate(game->perp.dir, speed);
	game->perp.fov = rotate(game->perp.fov, speed);
	draw_walls(game);
	draw_minimap_perp(&game->perp, game->minimap[1]);
}

void	player_key(void *param)
{
	t_game	*game;
	double	speed_norm;

	game = param;
	speed_norm = FPS * game->mlx_win->delta_time;
	if (game->mouse_key == true)
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
}

void	general_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx_win);
		if (keydata.key == MLX_KEY_M)
		{
			if (game->mouse_key == false)
			{
				mlx_set_cursor_mode(game->mlx_win, MLX_MOUSE_DISABLED);
				game->mouse_key = true;
			}
			else
			{
				mlx_set_cursor_mode(game->mlx_win, MLX_MOUSE_NORMAL);
				game->mouse_key = false;
			}
		}
	}
}
