#include "cub3d.h"
#include <math.h>

static double	scal_project(t_vect rayDir, t_vect perpDir, double ray_dist)
{
	double	angleCos;

	angleCos = dot_product(rayDir, perpDir);
	angleCos /= scalar(rayDir) * scalar(perpDir);
	return (ray_dist * angleCos);
}

t_ray	*init_ray(t_ray *ray, const t_player *perp, double cameraX)
{
	ray->mapX = (int)perp->posX;
	ray->mapY = (int)perp->posY;
	ray->dir = vect_sum(perp->dir, scal_product(cameraX, perp->fov));
	ray->deltaX = HUGE_VALF;
	if (ray->dir.x != 0)
		ray->deltaX = fabs(1 / ray->dir.x);
	ray->deltaY = HUGE_VALF;
	if (ray->dir.y != 0)
		ray->deltaY = fabs(1 / ray->dir.y);
	ray->sideDistX = (perp->posX - ray->mapX) * ray->deltaX;
	if (ray->dir.x >= 0)
		ray->sideDistX = ray->deltaX - ray->sideDistX;
	ray->sideDistY = (perp->posY - ray->mapY) * ray->deltaY;
	if (ray->dir.y >= 0)
		ray->sideDistY = ray->deltaY - ray->sideDistY;
	ray->stepX = (int)copysign(1e0, ray->dir.x);
	ray->stepY = (int)copysign(1e0, ray->dir.y);
	return (ray);
}

double	cast_ray(const char **map, t_player *perp, t_ray *ray)
{
	double	ray_dist;

	while (true)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->mapX += ray->stepX;
			ray->sideDistX += ray->deltaX;
			ray->side = 1;
		}
		else
		{
			ray->mapY += ray->stepY;
			ray->sideDistY += ray->deltaY;
			ray->side = 3;
		}
		if (map[ray->mapX][ray->mapY] != '0')
			break ;
	}
	if (ray->side == 1)
		ray_dist = ray->sideDistX - ray->deltaX;
	else
		ray_dist = ray->sideDistY - ray->deltaY;
	return (scal_project(ray->dir, perp->dir, ray_dist));
}
