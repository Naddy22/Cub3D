/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:35:14 by namoisan          #+#    #+#             */
/*   Updated: 2024/09/26 16:19:42 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
		c == '\r')
		return (true);
	return (false);
}

char	get_map_tile(char **map, int x, int y, int m)
{
	if (y < 0 || y >= m || x < 0 || x >= (int)ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}

bool	is_line_empty(char *line)
{
	while (*line)
	{
		if (ft_isspace(*line) == false)
			return (false);
		line++;
	}
	return (true);
}
