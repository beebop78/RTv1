/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:24:23 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/12 13:08:32 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matiere	matiere_init(char *str)
{
	t_matiere new;
	if (!ft_strcmp(str, "PLASTIQUE"))
	{
		new.i = 1;
		new.opacite = 1;
	}
	return (new);
}

void		newsphere(t_scene *scene, char **str)
{
	t_sphere *tmp;

	if(ft_tabstrlen(str) < 9)
		return ;
	if (scene->spheres == NULL)
	{
		scene->spheres = malloc(sizeof(t_sphere));
		scene->spheres->next = NULL;
	}
	tmp = scene->spheres;
	while(tmp->next)
		tmp = tmp->next;
	tmp->spherepos.x = ft_atoi(str[1]);
	tmp->spherepos.y = ft_atoi(str[2]);
	tmp->spherepos.z = ft_atoi(str[3]);
	tmp->radius = ft_atoi(str[4]);
	tmp->matiere = matiere_init(str[5]);
	tmp->color = (ft_atoi(str[6]) << 8 + ft_atoi(str[7]) << 4 + ft_atoi(str[8]));
	tmp->next = malloc(sizeof(t_sphere));
	tmp->next->next = NULL;
}

void		newspot(t_schene *scene, char **str)
{
	t_spot *tmp;

	if (ft_tabstrlen(str) < 7)
		return ;
	if (scene->spots == NULL)
	{
		scene->spots = malloc(sizeof(t_spot));
		scene->spots->next = NULL;
	}
	tmp = scene->spots;
	while (tmp->next)
		tmp = tmp->next;
	tmp->spotpos.x = ft_atoi(str[1]);
	tmp->spotpos.y = ft_atoi(str[2]);
	tmp->spotpos.z = ft_atoi(str[3]);
	tmp->color = (ft_atoi(str[4]) << 8 + ft_atoi(str[5]) << 4 + ft_atoi(str[6]));
	tmp->next = malloc(sizeof(t_spot));
	tmp->next->next = NULL;
}

void		newcamera(t_scene *scene, char **str)
{
	scene->camera.raypos.x = ft_atoi(str[1]);
	scene->camera.raypos.y = ft_atoi(str[2]);
	scene->camera.raypos.z = ft_atoi(str[3]);
	scene->camera.raydir = rcm_vecnormalize(rcm_vecneg(scene->camera.raypos));
}

