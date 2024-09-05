#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <stdbool.h>

// define de base
# define SUCCESS 0
# define FAIL 1
# define ERROR 2

typedef struct s_map
{

}	t_map;

typedef struct s_game
{

}	t_game;

//parsing.c
void	parsing(char *file, t_game *game);

//error.c
void	error_exit(char *error);

#endif