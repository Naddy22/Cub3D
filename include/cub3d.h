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
# define FOV 8e-1
# define SPEED 0.1
# define ROT_SPEED 0.05

typedef enum e_side
{
	SOUTH = 0,
	EAST,
	NORTH,
	WEST,
}	t_side;

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

typedef struct s_parsing
{
	char	*tex_paths[4];
}	t_parsing;

typedef struct s_line
{
	double	wall_x;
	double	scale;
	int		x;
	int		h;
	int		y;
	int		y_0;
	int		y_end;
	t_side	wall;
}	t_line;

typedef struct s_player
{
	t_vect	pos;
	t_vect	dir;
	t_vect	fov;
}	t_player;

typedef struct s_game
{
	char			**map;
	char			*tex_path[4];
	char			*color[2];
	int				f_rgba;
	int				c_rgba;
	mlx_t			*mlx_win;
	mlx_texture_t	*wall_tex[4];
	mlx_image_t		*backgr;
	mlx_image_t		*foregr;
	t_player		perp;
}	t_game;

// parsing.c
void	parsing(char *file, t_game *game);
int		parse_map(int fd, char *map_line, t_game *game);

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

// raycasting.c
void	draw_walls(void *param);

//utils.c
bool	ft_isspace(char c);

//mlx.c
void	mlx(t_game *game);

//init.c
void	draw_floor_and_ceiling(t_game *game);
void	set_textures(t_game *game);

#endif