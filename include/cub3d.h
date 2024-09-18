#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "vect.h"
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

// define de base
# define SUCCESS 0
# define FAIL 1
# define ERROR 2

# define W_WIDTH 1920
# define W_HEIGHT 1080

enum e_wall_side
{
	SOUTH,
	WEST,
	EAST,
	NORTH,
};

enum	e_color
{
	FLOOR,
	CEILING,
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
	char		**map;
	char		*wall_tex[4];
	char		*color[2];
	int			f_rgba;
	int			c_rgba;
	mlx_t		*mlx_win;
	mlx_image_t	*background;
}	t_game;

// parsing.c
void	parsing(char *file, t_game *game);

// error.c
void	ft_error_exit(char *error);
void	ft_free_error(char *error, t_game *game);

// identifiers.c
int		ft_get_identifiers(t_game *game, char *line);
bool	ft_is_valid_path(t_game *game);

// color.c
char	*ft_set_color(char *trim_line, char *line);
void	convert_color(t_game *game);

// free.c
void	ft_free_game(t_game *game);
void	ft_free_all(t_game *game);

// raycasting.c & camera.c
t_ray	*init_ray(t_ray *ray, const t_player *perp, double cam_x);
void	cast_ray(const char **map, t_player *perp, t_ray *ray);

//utils.c
bool	ft_isspace(char c);

//mlx.c
void	mlx(t_game *game);

#endif