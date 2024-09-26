/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:34:30 by namoisan          #+#    #+#             */
/*   Updated: 2024/09/26 10:34:31 by namoisan         ###   ########.fr       */
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
