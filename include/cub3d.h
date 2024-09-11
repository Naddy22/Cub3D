#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <stdbool.h>

// define de base
# define SUCCESS 0
# define FAIL 1
# define ERROR 2

// typedef struct s_map
// {
// 	char	**data;
// }	t_map;

typedef struct s_ray
{
	double	sideDistX;
	double	sideDistY;
	double	dirX;
	double	dirY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		mapX;
	int		mapY;
}	t_ray;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	fovX;
	double	fovY;
}	t_player;

typedef struct s_game
{
	char	**map;
}	t_game;

//parsing.c
void	parsing(char *file, t_game *game);

//error.c
void	error_exit(char *error);

#endif