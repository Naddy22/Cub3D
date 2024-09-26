/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:34:45 by namoisan          #+#    #+#             */
/*   Updated: 2024/09/26 14:45:32 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
		ft_error_exit("Usage: ./cub3D [file.cub]\n");
	parsing(argv[1], &game);
	mlx(&game);
	ft_free_game(&game);
	return (0);
}
