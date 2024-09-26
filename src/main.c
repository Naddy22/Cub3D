/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:34:45 by namoisan          #+#    #+#             */
/*   Updated: 2024/09/26 10:48:02 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc == 2)
	{
		parsing(argv[1], &game);
		mlx(&game);
		ft_free_game(&game);
	}
	else
		ft_error_exit("Usage: ./cub3D [file.cub]\n");
	return (0);
}
