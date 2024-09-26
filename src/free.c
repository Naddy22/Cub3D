/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:34:30 by namoisan          #+#    #+#             */
/*   Updated: 2024/09/26 15:23:17 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	exit_mlx(t_game *game)
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
