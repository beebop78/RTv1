/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 14:29:15 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/22 19:24:10 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				newcylinder(t_scene *scene, char **str)
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
	new->len = ft_atoi(str[12]);
	new->matiere = matiere_init(str[8]);
	new->next = malloc(sizeof(t_cylinder));
	new->next->next = NULL;
}

double				get_cylinders_t(t_ray ray, t_cylinder cylinder,
									double maxdist, t_point tmp)
{
	double		value[4];
	t_point		deltap;

	tmp = rcm_vecsub(ray.raydir, rcm_vecscalarfactor(cylinder.lign.raydir,
		rcm_dotproduct(ray.raydir, cylinder.lign.raydir)));
	value[0] = rcm_dotproduct(tmp, tmp);
	deltap = rcm_vecsub(ray.raypos, cylinder.lign.raypos);
	value[1] = 2 * rcm_dotproduct(tmp, rcm_vecsub(deltap,
		rcm_vecscalarfactor(cylinder.lign.raydir,
		rcm_dotproduct(deltap, cylinder.lign.raydir))));
	tmp = (rcm_vecsub(deltap, rcm_vecscalarfactor(cylinder.lign.raydir,
		rcm_dotproduct(deltap, cylinder.lign.raydir))));
	value[2] = rcm_dotproduct(tmp, tmp) - cylinder.radius * cylinder.radius;
	value[4] = value[1] * value[1] - 4 * value[0] * value[2];
	if (value[4] == 0 && -value[1] / (2 * value[0]) > 0)
		return (-value[1] / (2 * value[0]));
	if (value[4] == 0)
		return (maxdist);
	value[4] = sqrt(value[4]);
	if ((-value[1] + value[4]) / (2 * value[0]) > 0 && (-value[1] + value[4]) /
		(2 * value[0]) < (-value[1] - value[4]) / (2 * value[0]))
		return ((-value[1] + value[4]) / (value[0] * 2));
	else if (((-value[1] - value[4]) / (2 * value[0])) > 0)
		return ((-value[1] - value[4]) / (2 * value[0]));
	return (maxdist);
}

t_point				get_cylinder_normal(t_ray ray, t_cylinder cylinder,
						t_point intersection)
{
	t_point			normal;

	normal = rcm_vecsub(intersection, cylinder.lign.raypos);
	normal = rcm_vecsub(normal, rcm_vecproject(normal, cylinder.lign.raydir));
	return ((rcm_vecnormalize(normal)));
}

int					finite_check(t_cylinder cylinder, double t, t_ray ray)
{
	double		dist;
	t_point		tmp;
	t_point		interpos;
	t_point		narmol;

	interpos = rcm_vecsum(ray.raypos, rcm_vecscalarfactor(ray.raydir, t));
	narmol = rcm_vecscalarfactor(get_cylinder_normal(ray, cylinder,
		interpos), -(cylinder.radius));
	tmp = rcm_vecsum(interpos, narmol);
	dist = rcm_vecnorme(rcm_vecsub(cylinder.lign.raypos, tmp));
	if (dist > (cylinder.len))
		return (0);
	return (1);
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
		t = get_cylinders_t(ray, *cross, *maxdist, ray.raypos);
		if (t < *maxdist && (finite_check(*cross, t, ray) || cross->len < 0))
		{
			if (intersection == NULL)
				intersection = malloc(sizeof(t_intersection));
			*intersection = file_intersection(t, ray, cross->color,
				cross->matiere);
			intersection->normal = get_cylinder_normal(ray, *cross,
				intersection->interpos);
			intersection->object_add = (void *)cross;
			*maxdist = t;
		}
		cross = cross->next;
	}
	return (intersection);
}
