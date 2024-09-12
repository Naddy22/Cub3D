#include "cub3d.h"
#include <math.h>

static double	scal_project(t_vect ray_dir, t_vect perp_dir, double ray_dist)
{
	double	cos_angle;

	cos_angle = dot_product(ray_dir, perp_dir);
	cos_angle /= scalar(ray_dir) * scalar(perp_dir);
	return (ray_dist * cos_angle);
}

t_ray	*init_ray(t_ray *ray, const t_player *perp, double cam_x)
{
	double	ray_dir_len;

	ray->map_x = (int)perp->pos_x;
	ray->map_y = (int)perp->pos_y;
	ray->dir = vect_sum(perp->dir, scal_product(cam_x, perp->fov));
	ray_dir_len = scalar(ray->dir);
	ray->delta_x = HUGE_VALF;
	if (ray->dir.x != 0)
		ray->delta_x = fabs(ray_dir_len / ray->dir.x);
	ray->delta_y = HUGE_VALF;
	if (ray->dir.y != 0)
		ray->delta_y = fabs(ray_dir_len / ray->dir.y);
	ray->ray_dist_x = (perp->pos_x - ray->map_x) * ray->delta_x;
	if (ray->dir.x >= 0)
		ray->ray_dist_x = ray->delta_x - ray->ray_dist_x;
	ray->ray_dist_y = (perp->pos_y - ray->map_y) * ray->delta_y;
	if (ray->dir.y >= 0)
		ray->ray_dist_y = ray->delta_y - ray->ray_dist_y;
	ray->step_x = (int)copysign(1e0, ray->dir.x);
	ray->step_y = (int)copysign(1e0, ray->dir.y);
	return (ray);
}

void	cast_ray(const char **map, t_player *perp, t_ray *ray)
{
	double	ray_dist;

	while (true)
	{
		if (ray->ray_dist_x < ray->ray_dist_y)
		{
			ray->map_x += ray->step_x;
			ray->ray_dist_x += ray->delta_x;
			ray->side = 1;
		}
		else
		{
			ray->map_y += ray->step_y;
			ray->ray_dist_y += ray->delta_y;
			ray->side = 3;
		}
		if (map[ray->map_x][ray->map_y] != '0')
			break ;
	}
	if (ray->side == 1)
		ray_dist = ray->ray_dist_x - ray->delta_x;
	else
		ray_dist = ray->ray_dist_y - ray->delta_y;
	ray->fov_dist = scal_project(ray->dir, perp->dir, ray_dist);
}

void	perp_scan(t_game *game, t_player *perp)
{
	t_ray	ray;
	t_line	line;
	double	cam_x;

	line.x = -1;
	while (++line.x < W_WIDTH)
	{
		cam_x = 2 * line.x / (double)W_WIDTH - 1;
		cast_ray(game->map, perp, init_ray(&ray, perp, cam_x));
		line.h = (int)(W_HEIGHT / ray.fov_dist);
		line.y_0 = ft_max(W_HEIGHT / 2 - line.h / 2, 0);
		line.y_end = W_HEIGHT - line.y_0 - 1;
	}
}
