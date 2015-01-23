/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:47:44 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/22 19:07:57 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				newsphere(t_scene *scene, char **str)
{
	t_sphere	*tmp;
	int			a;
	int			b;
	int			c;

	if (scene->spheres == NULL)
	{
		scene->spheres = malloc(sizeof(t_sphere));
		scene->spheres->next = NULL;
	}
	tmp = scene->spheres;
	while (tmp->next)
		tmp = tmp->next;
	tmp->spherepos.x = ft_atoi(str[1]);
	tmp->spherepos.y = ft_atoi(str[2]);
	tmp->spherepos.z = ft_atoi(str[3]);
	tmp->radius = ft_atoi(str[4]);
	tmp->matiere = matiere_init(str[5]);
	a = ft_atoi(str[6]) << 16;
	b = ft_atoi(str[7]) << 8;
	c = ft_atoi(str[8]);
	tmp->color = a + b + c;
	tmp->next = malloc(sizeof(t_sphere));
	tmp->next->next = NULL;
}

double				get_sphere_t(t_ray ray, t_sphere sphere, double dist)
{
	double		b;
	double		c;
	double		delta;
	t_point		org;

	org = rcm_vecsum(ray.raypos, rcm_vecneg(sphere.spherepos));
	b = rcm_dotproduct(org, ray.raydir);
	c = -sphere.radius * sphere.radius + org.x * org.x + org.y *
		org.y + org.z * org.z;
	delta = b * b - c;
	if (delta < 0)
		return (dist);
	if (delta == 0.0f && -b > 0)
		return (-b);
	delta = rcm_sqrt(delta);
	if (-b + delta < -b - delta && (-b + delta) > 0)
		return (-b + delta);
	if ((-b - delta) > 0)
		return (-b - delta);
	return (dist);
}

t_point				get_sphere_normal(t_ray ray, t_sphere sphere,
						t_point intersection)
{
	return (rcm_vecscalarfactor(rcm_vecsum(intersection,
	rcm_vecneg(sphere.spherepos)), 1.0f / sphere.radius));
}

t_intersection		*spheres_cross(t_scene scene, t_ray ray, double *maxdist)
{
	double					t;
	t_intersection			*intersection;
	t_sphere				*cross;

	cross = scene.spheres;
	intersection = NULL;
	while (cross && cross->next)
	{
		t = get_sphere_t(ray, *cross, *maxdist);
		if (t < *maxdist)
		{
			if (intersection == NULL)
				intersection = malloc(sizeof(t_intersection));
			*intersection = file_intersection(t, ray, cross->color,
				cross->matiere);
			intersection->normal = get_sphere_normal(ray, *cross,
				intersection->interpos);
			intersection->object_add = (void *)cross;
			*maxdist = t;
		}
		cross = cross->next;
	}
	return (intersection);
}
