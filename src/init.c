/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:34:39 by namoisan          #+#    #+#             */
/*   Updated: 2024/09/26 14:49:11 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->backgr = mlx_new_image(game->mlx_win, W_WIDTH, W_HEIGHT);
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			if (y < W_HEIGHT / 2)
				mlx_put_pixel(game->backgr, x, y, game->c_rgba);
			else
				mlx_put_pixel(game->backgr, x, y, game->f_rgba);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx_win, game->backgr, 0, 0);
}

void	set_textures(t_game *game)
{
	int	directions;

	directions = 0;
	while (directions < 4)
	{
		game->wall_tex[directions] = mlx_load_png(game->tex_path[directions]);
		if (game->wall_tex[directions] == NULL)
			ft_free_error("Failed to load PNG\n", game);
		directions++;
	}
}

void	init_minimap(t_game *game)
{
	game->minimap[0] = mlx_new_image(game->mlx_win, MM_WIDTH, MM_WIDTH);
	game->minimap[1] = mlx_new_image(game->mlx_win, MM_WIDTH, MM_WIDTH);
	mlx_image_to_window(game->mlx_win, game->minimap[0], 0, 0);
	mlx_image_to_window(game->mlx_win, game->minimap[1], 0, 0);
	draw_minimap(&game->perp, game->minimap[0], game->map, game->map_h);
	draw_minimap_perp(&game->perp, game->minimap[1]);
}

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
