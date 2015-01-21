/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 14:29:15 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/20 19:11:32 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		newcylinder (t_scene *scene, char **str)
{
	t_cylinder *new;

	if (!scene->cylinders)
	{
		scene->cylinders = malloc(sizeof(t_cylinder));
		scene->cylinders->next = NULL;
	}
	new = scene->cylinders;
	while (new && new->next)
		new = new->next;
	new->lign.raypos = get_vec(&(str[1]));
	new->lign.raydir = rcm_vecnormalize(get_vec(&(str[4])));
	new->radius = ft_atoi(str[7]);
	new->color = ft_atoi(str[9]) << 16;
	new->color += (ft_atoi(str[10]) << 8);
	new->color += ft_atoi(str[11]);
	new->matiere = matiere_init(str[8]);
	new->next = malloc(sizeof(t_cylinder));
	new->next->next = NULL;
}

double		get_cylinders_t(t_ray ray, t_cylinder cylinder, double maxdist)
{
	double		a;
	double		b;
	double		c;
	t_point		tmp;
	t_point		deltap;
	double		delta;

	tmp = rcm_vecsub(ray.raydir, rcm_vecscalarfactor(cylinder.lign.raydir,
		rcm_dotproduct(ray.raydir, cylinder.lign.raydir)));
	a = rcm_dotproduct(tmp, tmp);
	deltap = rcm_vecsub(ray.raypos, cylinder.lign.raypos);
	b = 2 * rcm_dotproduct(tmp, rcm_vecsub(deltap, rcm_vecscalarfactor(cylinder.lign.raydir,
		rcm_dotproduct(deltap, cylinder.lign.raydir))));
	tmp = (rcm_vecsub(deltap, rcm_vecscalarfactor(cylinder.lign.raydir, rcm_dotproduct(deltap,
		cylinder.lign.raydir))));
	c = rcm_dotproduct(tmp, tmp) - cylinder.radius * cylinder.radius;
	delta  = b * b - 4 * a * c;
	if (delta == 0 && -b / (2 * a) > 0)
		return (-b / (2 * a));
	if(delta > 0)
	{
		delta = sqrt(delta);
		if ((-b + delta) / (2 * a) > 0 && (-b + delta) / (2 * a) < (-b - delta) / (2 * a))
			return ((-b + delta) / (2 * a));
		else if (((-b - delta) / (2 * a))  > 0)
			return ((-b - delta) / (2 * a));
	}
	return (maxdist);
}

t_point			get_cylinder_normal(t_ray ray, t_cylinder cylinder, t_point intersection)
{
	t_point			normal;

	normal = rcm_vecsub(intersection, cylinder.lign.raypos);
	normal = rcm_vecsub(normal, rcm_vecproject(normal, cylinder.lign.raydir));
	return ((rcm_vecnormalize(normal)));
}


t_intersection		*cylinder_cross(t_scene scene, t_ray ray, double *maxdist)
{
	double					t;
	t_intersection			*intersection;
	t_cylinder				*cross;

	cross = scene.cylinders;
	intersection = NULL;
	while (cross && cross->next)
	{
		t = get_cylinders_t(ray, *cross, *maxdist);
		if (t < *maxdist)
		{
			if (intersection == NULL)
				intersection = malloc(sizeof(t_intersection));
			*intersection = file_intersection(t, ray, cross->color, cross->matiere);
			intersection->normal = get_cylinder_normal(ray, *cross, intersection->interpos);
			intersection->object_add =  (void *)cross;
			*maxdist = t;
		}
		cross = cross->next;
	}
	return (intersection);
}













