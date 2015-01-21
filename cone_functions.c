/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 19:10:41 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/21 20:54:56 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

void		newcone (t_scene *scene, char **str)
{
	t_cone *new;

	if (!scene->cones)
	{
		scene->cones = malloc(sizeof(t_cone));
		scene->cones->next = NULL;
	}
	new = scene->cones;
	while (new && new->next)
		new = new->next;
	new->lign.raypos = get_vec(&(str[1]));
	new->lign.raydir = rcm_vecnormalize(get_vec(&(str[4])));
	new->angle = ft_atoi(str[7]);
	new->angle /= 57;
	new->color = ft_atoi(str[10]) << 16;
	new->color += (ft_atoi(str[11]) << 8);
	new->color += ft_atoi(str[12]);
	new->matiere = matiere_init(str[8]);
	new->next = malloc(sizeof(t_cone));
	new->next->next = NULL;
}

double					minposvalue(double delta, double *value, double maxdist)
{
	double tmp;
	double tmp2;

    if (delta == 0 && (-value[1] / (2 * value[0])) > 0)
        return (-value[1] / (2 * value[0]));
    if (delta < 0)
        return (maxdist);
    delta = rcm_sqrt(delta);
    tmp = (-value[1] + delta) / (2 * value[0]);
    tmp2 = (-value[1] - delta) / (2 * value[0]);
    if (tmp < tmp2 && tmp > 0)
        return (tmp);
    else if (tmp2 > 0)
        return (tmp);
    return (maxdist);
}

double					get_cone_t(t_ray ray, t_cone cone, double maxdist, double tmp2)
{
	double tmp;
	t_point deltap;
	double delta;
	double value[3];
	t_point ttmp;

	deltap = rcm_vecsub(ray.raydir, rcm_vecscalarfactor(cone.lign.raydir,
		rcm_dotproduct(ray.raydir, cone.lign.raydir)));
	tmp = rcm_dotproduct(deltap, deltap) * cos(cone.angle) * cos(cone.angle);
	ttmp = deltap;
	deltap = rcm_vecsub(ray.raypos, cone.lign.raypos);
	tmp2 = rcm_dotproduct(ray.raydir, cone.lign.raydir);
	tmp2 *= tmp2;
	tmp2 = tmp2 * sin(cone.angle) * sin(cone.angle);
	value[0] = tmp - tmp2;

	tmp2 = 2 * cos(cone.angle) * cos(cone.angle);
	value[1] = tmp2 * (rcm_dotproduct(ttmp, rcm_vecsub(deltap,
	rcm_vecscalarfactor(cone.lign.raydir, rcm_dotproduct(deltap, cone.lign.raydir)))));
	tmp2 = 2 * sin(cone.angle) * sin(cone.angle);
	value[1] -= tmp2 * rcm_dotproduct(ray.raydir, cone.lign.raydir) * rcm_dotproduct(deltap, cone.lign.raydir);

	tmp2 = rcm_dotproduct(deltap, cone.lign.raydir);
	ttmp = rcm_vecsub(deltap, rcm_vecscalarfactor(cone.lign.raydir, tmp2));
	tmp = rcm_dotproduct(ttmp, ttmp);
	tmp = tmp * cos(cone.angle) * cos(cone.angle) * 2;
	value[2] = tmp - (tmp2 * tmp2) * sin(cone.angle) * sin(cone.angle);
	delta = value[1] * value[1] - 4 * value[0] * value[2];
	return (minposvalue(delta, value, maxdist));
}

t_point					get_cone_normal(t_ray ray, t_cone cone, t_point intersection)
{
	t_point narmol;

	narmol = rcm_vecsub(intersection, cone.lign.raypos);
	narmol = rcm_vecsub(narmol, rcm_vecproject(narmol, cone.lign.raydir));
	return (rcm_vecnormalize(narmol));
}

t_intersection			*cone_cross(t_scene scene, t_ray ray, double *maxdist)
{
	double					t;
	t_intersection			*intersection;
	t_cone					*cross;

	cross = scene.cones;
	intersection = NULL;
	while (cross && cross->next)
	{
		t = get_cone_t(ray, *cross, *maxdist, 0);
		if (t < *maxdist)
		{
			if (intersection == NULL)
				intersection = malloc(sizeof(t_intersection));
			*intersection = file_intersection(t, ray, cross->color, cross->matiere);
			intersection->normal = get_cone_normal(ray, *cross, intersection->interpos);
			intersection->object_add = (void *)cross;
			*maxdist = t;
		}
		cross = cross->next;
	}
	return (intersection);
}
