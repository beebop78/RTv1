/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 15:31:02 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/17 16:22:59 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_point			reflected_ray(t_point lightray, t_point normal)
{
	t_point		new;
	t_point		tmp;
	double		dtmp;

	new = lightray;
	dtmp =  2 * rcm_dotproduct(normal, lightray);
	tmp = rcm_vecscalarfactor(normal, dtmp);
	new = rcm_vecsub(new, tmp);
	return (new);
}

int				specular(t_intersection intersection, t_spot spot, int color)
{
	t_point		source;
	t_point		reflected;
	double		triche;

	source = rcm_vecnormalize(rcm_vecsub(intersection.interpos, spot.spotpos));
	reflected = reflected_ray(source, intersection.normal);
	triche = (rcm_dotproduct(rcm_vecneg(source), reflected));
	if (triche < 0)
		return (color);
	return (color_add(color, color_setbright(spot.color,
		(triche * triche * triche * triche))));
}
