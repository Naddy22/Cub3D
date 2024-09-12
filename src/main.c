#include "cub3d.h"

int main(int argc, char **argv)
{
	t_game game;

	if (argc == 2)
	{
		parsing(argv[1], &game);
	}
	else
		ft_error_exit("Usage: ./cub3D [file.cub]\n");
	return (0);
}