/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 15:31:02 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/17 15:43:38 by rcargou          ###   ########.fr       */
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

