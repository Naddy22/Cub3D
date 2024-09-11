#include "cub3d.h"

char	*ft_set_color(char *trim_line, char *line)
{
	int count;
	int i;
	char *result;

	count = 0;
	i = 0;
	while (trim_line != '\0')
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
