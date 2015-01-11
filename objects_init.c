/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:24:23 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/11 21:35:57 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matiere matiere_init(char *str)
{
	t_matiere new;
	if (!ft_strcmp(str, "PLASTIQUE"))
	{
		new.i = 1;
		new.opacite = 1;
	}
	return (new);
}

void newsphere(t_scene *scene, char **str)
{
	t_sphere *tmp;

	if(ft_tabstrlen(str) < 8)
		return ;
	tmp = scene->spheres;
	while(tmp)
		tmp = tmp->next;
	tmp->spherepos.x = ft_atoi(str[1]);
	tmp->spherepos.y = ft_atoi(str[2]);
	tmp->spherepos.z = ft_atoi(str[3]);
	tmp->radius = ft_atoi(str[4]);
	tmp->matiere = matiere_init(str[5]);
	tmp->color = (ft_atoi(str[6]) << 8 + ft_atoi(str[7]) << 4 + ft_atoi(str[8]));
}
