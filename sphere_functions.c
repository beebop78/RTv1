/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:47:44 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/12 12:36:13 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			get_sphere_t(t_ray ray, t_sphere sphere)
{
	double		t;
	double		b;
	double		c;
	int			nsolutions;
	t_point		org;

	org = rcm_vecsum(ray.raypos, rcm_vecneg(sphere.spherepos));
	b = rcm_dotproduct(org, ray.raydir);
	c = -sphere.radius * -sphere.radius + rcm_vecnorme(org) * rcm_vecnorme(org);
	t = rcm_min(rcm_2dequation(0.25, b, c, &nsolutions), nsolutions);
	if (nsolutions)
		return (&t);
	return (NULL);
}

t_point			get_sphere_normal(t_ray ray, t_sphere sphere, t_point intersection)
{
	return (rcm_vecsum(intersection, rcm_vecneg(sphere.spherepos)));
}
