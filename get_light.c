/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 17:21:08 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/22 18:59:02 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				shadow_ray(t_intersection intersection, t_env env,
					t_spot spot, int option)
{
	t_ray				ray;
	t_intersection		*new;
	double				len1;
	double				len2;

	len1 = rcm_vecsquarelength(rcm_vecsub(spot.spotpos, intersection.interpos));
	ray.raypos = intersection.interpos;
	ray.raydir = rcm_vecnormalize(rcm_vecsum(spot.spotpos,
		rcm_vecneg(ray.raypos)));
	new = get_intersection(env, ray, env.scene.func);
	if (new)
	{
		len2 = rcm_vecsquarelength(rcm_vecsub(spot.spotpos, new->interpos));
		if ((new->object_add != intersection.object_add ||
			option) && (len2 < len1))
		{
			free(new);
			return (1);
		}
		free(new);
	}
	return (0);
}

int				get_light(t_intersection *intersection, t_env env)
{
	t_spot		*cross;
	int			color;
	t_point		lightvector;
	double		angle;
	double		shadowray;

	color = 0;
	cross = env.scene.spots;
	while (cross->next)
	{
		lightvector = rcm_vecnormalize(rcm_vecsum(intersection->interpos,
			rcm_vecneg(cross->spotpos)));
		shadowray = 0.7 * shadow_ray(*intersection, env, *cross, 0);
		angle = rcm_dotproduct(rcm_vecneg(intersection->normal), lightvector);
		color = color_add((cross->color & color),
		color_setbright(intersection->color, angle - shadowray));
		color = color_setbright(color, 1.0f / (intersection->dist) * 20
			* env.scene.att);
		if (angle > 0)
			color = color_add(color, specular(*intersection, *cross, 0, env));
		cross = cross->next;
	}
	free(intersection);
	return (color);
}
