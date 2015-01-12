/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:47:44 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/12 20:00:39 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			get_sphere_t(t_ray ray, t_sphere sphere, int dist)
{
	double		t1;
	double		t2;
	double		b;
	double		c;
	double		*tab;
	double		delta;
	int			nsolutions;
	t_point		org;

	org = rcm_vecsum(ray.raypos, rcm_vecneg(sphere.spherepos));
	b = rcm_dotproduct(org, ray.raydir);
	c = -sphere.radius * sphere.radius + org.x * org.x + org.y * org.y + org.z * org.z;
	delta = b * b - c;
	if (delta < 0)
		return (dist);
	if (delta == 0)
		return (-b);
	delta = rcm_sqrt(delta);
	if (-b + delta < -b - delta)
		return (-b + delta);
	return (-b - delta);
}

t_point			get_sphere_normal(t_ray ray, t_sphere sphere, t_point intersection)
{
	return (rcm_vecscalarfactor(rcm_vecsum(intersection, rcm_vecneg(sphere.spherepos)), 1.0f / sphere.radius));
}
