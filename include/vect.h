#ifndef VECT_H
# define VECT_H

typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

// retourne la grandeur du vecteur (pythagore)
double	scalar(t_vect v1);
t_vect	scal_product(double scal, t_vect v1);
double	dot_product(t_vect v1, t_vect v2);
t_vect	vect_sum(t_vect v1, t_vect v2);
t_vect	rotate(t_vect v1, double angle);

#endif