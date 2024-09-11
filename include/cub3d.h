#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "vect.h"
# include <stdbool.h>

// define de base
# define SUCCESS 0
# define FAIL 1
# define ERROR 2

enum e_wall_side
{
	SOUTH = -3,
	WEST = -1,
	EAST,
	NORTH,
};

// typedef struct s_map
// {
// 	char	**data;
// }	t_map;

typedef struct s_ray
{
	int		mapX;
	int		mapY;
	t_vect	dir;
	double	deltaX;
	double	deltaY;
	double	sideDistX;
	double	sideDistY;
	int		stepX;
	int		stepY;
	int		side;
}	t_ray;

typedef struct s_player
{
	double	posX;
	double	posY;
	t_vect	dir;
	t_vect	fov;
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