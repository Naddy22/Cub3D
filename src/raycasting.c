/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:35:09 by namoisan          #+#    #+#             */
/*   Updated: 2024/09/26 10:35:10 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// static double	scal_project(t_vect ray_dir, t_vect perp_dir, double ray_dist)
// {
// 	double	cos_angle;

// 	cos_angle = dot_product(ray_dir, perp_dir);
// 	cos_angle /= scalar(ray_dir) * scalar(perp_dir);
// 	return (ray_dist * cos_angle);
// }

t_ray	*init_ray(t_ray *ray, const t_player *perp, double cam_x)
{
	ray->map_x = (int)perp->pos.x;
	ray->map_y = (int)perp->pos.y;
	ray->dir = vect_sum(perp->dir, scal_product(cam_x, perp->fov));
	ray->delta_x = HUGE_VALF;
	if (ray->dir.x != 0)
		ray->delta_x = fabs(1 / ray->dir.x);
	ray->delta_y = HUGE_VALF;
	if (ray->dir.y != 0)
		ray->delta_y = fabs(1 / ray->dir.y);
	ray->ray_dist_x = (perp->pos.x - ray->map_x) * ray->delta_x;
	if (ray->dir.x >= 0)
		ray->ray_dist_x = ray->delta_x - ray->ray_dist_x;
	ray->ray_dist_y = (perp->pos.y - ray->map_y) * ray->delta_y;
	if (ray->dir.y >= 0)
		ray->ray_dist_y = ray->delta_y - ray->ray_dist_y;
	ray->step_x = (int)copysign(1e0, ray->dir.x);
	ray->step_y = (int)copysign(1e0, ray->dir.y);
	return (ray);
}

void	cast_ray(char **map, t_ray *ray)
{
	while (true)
	{
		if (ray->ray_dist_x < ray->ray_dist_y)
		{
			ray->map_x += ray->step_x;
			ray->ray_dist_x += ray->delta_x;
			ray->side = 2;
		}
		else
		{
			ray->map_y += ray->step_y;
			ray->ray_dist_y += ray->delta_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			break ;
	}
	if (ray->side == 2)
		ray->fov_dist = ray->ray_dist_x - ray->delta_x;
	else
		ray->fov_dist = ray->ray_dist_y - ray->delta_y;
	// ray->fov_dist = scal_project(ray->dir, perp->dir, ray_dist);
}

static uint32_t	get_color(t_game *game, t_line *line)
{
	int				tex_x;
	int				tex_y;
	int				pix_i;
	mlx_texture_t	*tex;
	uint32_t		color;

	if (line->y < line->y_0 || line->y > line->y_end)
		return (0);
	tex = game->wall_tex[line->wall];
	tex_x = line->wall_x * tex->width;
	tex_y = (int)((line->y - line->y_0) / line->scale);
	pix_i = (tex_y * tex->width + tex_x) * tex->bytes_per_pixel;
	color = tex->pixels[pix_i] << 24;
	color |= tex->pixels[pix_i + 1] << 16;
	color |= tex->pixels[pix_i + 2] << 8;
	color |= tex->pixels[pix_i + 3];
	return (color);
}

void	draw_walls(t_game *game)
{
	t_ray	ray;
	t_line	line;
	double	cam_x;

	line.x = -1;
	while (++line.x < W_WIDTH)
	{
		cam_x = 2 * line.x / (double)W_WIDTH - 1;
		cast_ray(game->map, init_ray(&ray, &game->perp, cam_x));
		line.h = (int)(W_HEIGHT / ray.fov_dist);
		line.y_0 = W_HEIGHT / 2 - line.h / 2;
		line.y_end = W_HEIGHT - line.y_0 - 1;
		if (ray.side == 1)
		{
			line.wall_x = game->perp.pos.x + ray.fov_dist * ray.dir.x;
			line.wall = 1 + ray.step_y;
		}
		else
		{
			line.wall_x = game->perp.pos.y + ray.fov_dist * ray.dir.y;
			line.wall = 2 + ray.step_x;
		}
		line.scale = (line.y_end - line.y_0) / (double)game->wall_tex[line.wall]->height;
		line.wall_x -= floor(line.wall_x);
		line.y = -1;
		while (++line.y < W_HEIGHT)
			mlx_put_pixel(game->foregr, line.x, line.y, get_color(game, &line));
	}
}
