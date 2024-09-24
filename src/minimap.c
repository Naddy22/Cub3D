#include "cub3d.h"

static void	draw_dot(mlx_image_t *img)
{
	static const int	center = MM_WIDTH / 2;

	mlx_put_pixel(img, center, center - 2, 0xFF0000FF);
	mlx_put_pixel(img, center - 1, center - 1, 0xFF0000FF);
	mlx_put_pixel(img, center, center - 1, 0xFF0000FF);
	mlx_put_pixel(img, center + 1, center - 1, 0xFF0000FF);
	mlx_put_pixel(img, center - 2, center, 0xFF0000FF);
	mlx_put_pixel(img, center - 1, center, 0xFF0000FF);
	mlx_put_pixel(img, center, center, 0xFF0000FF);
	mlx_put_pixel(img, center + 1, center, 0xFF0000FF);
	mlx_put_pixel(img, center + 2, center, 0xFF0000FF);
	mlx_put_pixel(img, center - 1, center + 1, 0xFF0000FF);
	mlx_put_pixel(img, center, center + 1, 0xFF0000FF);
	mlx_put_pixel(img, center + 1, center + 1, 0xFF0000FF);
	mlx_put_pixel(img, center, center + 2, 0xFF0000FF);
}

static void	draw_x_dir(t_player *perp, mlx_image_t *img)
{
	int	origin;
	int	x;
	int	y;
	int	step;
	int	stop;

	// printf("draw_x_dir: dir=(%f ; %f)\n", perp->dir.x, perp->dir.y);
	origin = MM_WIDTH * (perp->dir.x - perp->dir.y) / (2 * perp->dir.x);
	step = 1;
	if (perp->dir.x < 0)
		step = -1;
	x = MM_WIDTH / 2;
	stop = x + 20 * step;
	while (x != stop)
	{
		y = perp->dir.y * x / perp->dir.x + origin;
		mlx_put_pixel(img, x, y, 0x0000FFFF);
		x += step;
	}
}

static void	draw_y_dir(t_player *perp, mlx_image_t *img)
{
	int	origin;
	int	x;
	int	y;
	int	step;
	int	stop;

	// printf("draw_y_dir: dir=(%f ; %f)\n", perp->dir.x, perp->dir.y);
	origin = MM_WIDTH * (perp->dir.y - perp->dir.x) / (2 * perp->dir.y);
	step = 1;
	if (perp->dir.y < 0)
		step = -1;
	y = MM_WIDTH / 2;
	stop = y + 20 * step;
	while (y != stop)
	{
		x = perp->dir.x * y / perp->dir.y + origin;
		mlx_put_pixel(img, x, y, 0x0000FFFF);
		y += step;
	}
}

void	draw_minimap_perp(t_player *perp, mlx_image_t *img)
{
	ft_bzero(img->pixels, MM_WIDTH * MM_WIDTH * sizeof(u_int8_t) * 4);
	if (fabs(perp->dir.x) >= fabs(perp->dir.y))
		draw_x_dir(perp, img);
	else
		draw_y_dir(perp, img);
	draw_dot(img);
}

void	draw_minimap(t_player *perp, mlx_image_t *img, char **map, int m)
{
	static double	start_offset = MM_WIDTH * MM_RATIO / 2;
	t_minimap		mm;
	char			tile;

	mm.pix_start.x = perp->pos.x - start_offset;
	mm.pix_start.y = perp->pos.y - start_offset;
	mm.pix_pos.y = mm.pix_start.y;
	mm.draw_y = -1;
	while (++mm.draw_y < MM_WIDTH)
	{
		mm.draw_x = -1;
		mm.pix_pos.x = mm.pix_start.x;
		while (++mm.draw_x < MM_WIDTH)
		{
			tile = get_map_tile(map, mm.pix_pos, m);
			if (tile == ' ' || tile == '1')
				mlx_put_pixel(img, mm.draw_x, mm.draw_y, 0x000000FF);
			else
				mlx_put_pixel(img, mm.draw_x, mm.draw_y, 0xFFFFFFFF);
			mm.pix_pos.x += MM_RATIO;
		}
		mm.pix_pos.y += MM_RATIO;
	}
}
