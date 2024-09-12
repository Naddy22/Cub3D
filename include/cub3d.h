#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

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
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*f_color;
	char	*c_color;
}	t_game;

//parsing.c
void	parsing(char *file, t_game *game);

//error.c
void	ft_error_exit(char *error);

//identifiers.c
int		ft_get_identifiers(t_game *game, char *line);
bool	ft_is_valid_path(t_game *game);

//color.c
char	*ft_set_color(char *trim_line, char *line);

//free.c
void	ft_free_game(t_game *game);
void	ft_free_all(t_game *game);

#endif