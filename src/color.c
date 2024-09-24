#include "cub3d.h"

char	*ft_set_color(char *trim_line, char *line)
{
	int count;
	int i;
	char *result;

	count = 0;
	i = -1;
	while (trim_line[++i] != '\0')
		if (trim_line[i] == ',')
			count++;
	if (count != 2)
	{
		free(trim_line);
		free(line);
		ft_error_exit("Invalid color format\n");
	}
	result = ft_strdup(trim_line + 2);
	if (result == NULL)
		{
			free(trim_line);
			free(line);
			ft_error_exit("Malloc failed\n");
		}
	return (result);
}

static bool	ft_color_is_valid(char **split_c)
{
	int i;
	int j;


	if (!split_c[0] || !split_c[1] || !split_c[2])
		return (false);
	i = 0;
	while (split_c[i])
	{
		j = 0;
		while (split_c[i][j])
		{
			if (ft_isspace(split_c[i][j]) || !ft_isdigit(split_c[i][j]))
				return (false);
			j++;
		}
		if (ft_atoi(split_c[i]) < 0 || ft_atoi(split_c[i]) > 255)
			return (false);
		i++;
	}
	return (true);
}

static void	get_rgb(unsigned int *rgb, char **split)
{
	int i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(split[i]);
		i++;
	}
}

static char	**get_split(char *str_color)
{
	char *tmp;
	char **result;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = ft_calloc((ft_strlen(str_color)) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	while (str_color[i] != '\0')
	{
		if (str_color[i] != ' ')
		{
			tmp[j] = str_color[i];
			j++;
		}
		i++;
	}
	result = ft_split(tmp, ',');
	free (tmp);
	return (result);
}

void	convert_color(t_game *game)
{
	char			**floor;
	char			**ceiling;
	unsigned int	rgb[3];

	floor = get_split(game->color[FLOOR]);
	ceiling = get_split(game->color[CEILING]);
	if (!floor || !ceiling)
	{
		free(floor);
		free(ceiling);
		ft_free_error("Malloc failed\n", game);
	}
	if (ft_color_is_valid(floor) != true || ft_color_is_valid(ceiling) != true)
	{
		free(floor);
		free(ceiling);
		ft_free_error("Invalid color\n", game);
	}
	get_rgb(rgb, floor);
	game->f_rgba = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
	get_rgb(rgb, ceiling);
	game->c_rgba = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
	ft_free_split(floor); 
	ft_free_split(ceiling);
}
