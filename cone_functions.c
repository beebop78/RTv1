/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 19:10:41 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/20 19:19:53 by rcargou          ###   ########.fr       */
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
	new->radius = ft_atoi(str[7]);
	new->color = ft_atoi(str[9]) << 16;
	new->color += (ft_atoi(str[10]) << 8);
	new->color += ft_atoi(str[11]);
	new->matiere = matiere_init(str[8]);
	new->next = malloc(sizeof(t_cone));
	new->next->next = NULL;
}

double					get_cone_t(t_ray ray, t_cone cone, double maxdist)
{


}

t_point					get_cone_normal(t_ray ray, t_cone cone, t_point intersection)
{

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
		t = get_cone_t(ray, *cross, *maxdist);
		if (t < *maxdist)
		{
			if (intersection == NULL)
				intersection = malloc(sizeof(t_intersection));
			*intersection = file_intersection(t, ray, cross->color, cross->matiere);
			intersection->normal = get_cone_normal(ray, *cross, intersection->interpos);
			intersection->object_add =  (void *)cross;
			*maxdist = t;
		}
		cross = cross->next;
	}
	return (intersection);
}
