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

# define W_WIDTH 500
# define W_HEIGHT 200

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
	int		map_x;
	int		map_y;
	t_vect	dir;
	double	delta_x;
	double	delta_y;
	double	ray_dist_x;
	double	ray_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	fov_dist;
}	t_ray;

typedef struct s_line
{
	int	x;
	int	h;
	int	y_0;
	int	y_end;
}	t_line;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	t_vect	dir;
	t_vect	fov;
}	t_player;

typedef struct s_game
{
	char	**map;
}	t_game;

// parsing.c
void	parsing(char *file, t_game *game);

// error.c
void	error_exit(char *error);

// raycasting.c & camera.c
t_ray	*init_ray(t_ray *ray, const t_player *perp, double cam_x);
void	cast_ray(const char **map, t_player *perp, t_ray *ray);

#endif