#include "vect.h"
#include <math.h>

double	scalar(t_vect v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y));
}

t_vect	scal_product(double scal, t_vect v1)
{
	v1.x *= scal;
	v1.y *= scal;
	return (v1);
}

double	dot_product(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

t_vect	vect_sum(t_vect v1, t_vect v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return (v1);
}

// Positive angle for clockwise rotation
t_vect	rotate(t_vect v1, double angle)
{
	t_vect	v2;

	v2.x = v1.x * cos(angle) - v1.y * sin(angle);
	v2.y = v1.x * sin(angle) + v1.y * cos(angle);
	return (v2);
}
