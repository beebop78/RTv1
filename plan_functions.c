/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 14:43:39 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/22 19:04:49 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					newplan(t_scene *scene, char **str)
{
	t_plan		*new;
	int			a;
	int			b;

	if (scene->plans == NULL)
	{
		scene->plans = malloc(sizeof(t_plan));
		scene->plans->next = NULL;
	}
	new = (scene->plans);
	while (new->next)
		new = new->next;
	new->planpos.x = ft_atoi(str[1]);
	new->planpos.y = ft_atoi(str[2]);
	new->planpos.z = ft_atoi(str[3]);
	new->normal.x = ft_atoi(str[4]);
	new->normal.y = ft_atoi(str[5]);
	new->normal.z = ft_atoi(str[6]);
	new->normal = rcm_vecnormalize(new->normal);
	new->matiere = matiere_init(str[7]);
	a = ft_atoi(str[8]) << 16;
	b = ft_atoi(str[9]) << 8;
	new->color = a + b + ft_atoi(str[10]);
	new->next = malloc(sizeof(t_plan));
	new->next->next = NULL;
}

double					get_plan_t(t_ray ray, t_plan *plan, double dist)
{
	double		dv;
	double		t;

	dv = rcm_dotproduct(plan->normal, ray.raydir);
	if (!dv)
		return (dist);
	t = ((-rcm_dotproduct(plan->normal, rcm_vecsum(ray.raypos,
			rcm_vecneg(plan->planpos)))) / dv);
	if (t < 1)
		return (dist);
	plan->dv = dv;
	return (t);
}

t_point					get_plan_normal(t_plan plan)
{
	if (plan.dv < 0)
		return (plan.normal);
	return (rcm_vecneg(plan.normal));
}

t_intersection			*plans_cross(t_scene scene, t_ray ray, double *maxdist)
{
	double						t;
	t_intersection				*intersection;
	t_plan						*cross;

	cross = scene.plans;
	intersection = NULL;
	while (cross && cross->next)
	{
		t = get_plan_t(ray, cross, *maxdist);
		if (t < *maxdist && t > 1)
		{
			if (intersection == NULL)
				intersection = malloc(sizeof(t_intersection));
			*intersection = file_intersection(t, ray, cross->color,
				cross->matiere);
			intersection->normal = get_plan_normal(*cross);
			intersection->object_add = (void *)cross;
			*maxdist = t;
		}
		cross = cross->next;
	}
	return (intersection);
}
