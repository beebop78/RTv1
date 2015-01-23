/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snailfills.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 18:16:14 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/22 18:55:59 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void yo(int *a, int *b, int *c, int *d)
{
	*a = WIN_X - 8;
	*b = 0;
	*c = 0;
	*d = WIN_Y - 20;
}

void snailfills(int *coord, int r)
{
	static int xmax = WIN_X - 4;
	static int xmin = 0;
	static int ymax = WIN_Y - 4;
	static int ymin = 0;

	if (r)
		yo(&xmax, &xmin, &ymin, &ymax);
	if (r)
		return ;
	if ((coord[1]) <= ymin + 4 && (coord[0]) < xmax)
		coord[0] += 4;
	else if ((coord[0]) >= xmax && (coord[1]) < ymax)
		coord[1] += 4;
	else if (coord[1] >= ymax && coord[0] > xmin + 4)
		coord[0] -= 4;
	else if (coord[0] <= (xmin + 4) && coord[1] > (ymin + 4))
		coord[1] -= 4;
	if (coord[0] == xmin + 4 && coord[1] == ymin + 4)
	{
		xmin += 4;
		ymin += 4;
		xmax -= 4;
		ymax -= 4;
	}
}
