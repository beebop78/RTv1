/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:24:23 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/18 19:00:10 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_point			get_vec(char **str)
{
	t_point new;

	new.x = ft_atoi(str[0]);
	new.y = ft_atoi(str[1]);
	new.z = ft_atoi(str[2]);
	return (new);
}

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

void		newspot(t_scene *scene, char **str)
{
	t_spot		*tmp;
	int			a;
	int			b;
	int			c;

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
	a = ft_atoi(str[4]) << 16;
	b = ft_atoi(str[5]) << 8;
	c = ft_atoi(str[6]);
	tmp->color = a + b + c;
	tmp->next = malloc(sizeof(t_spot));
	tmp->next->next = NULL;
}

int			newcamera(t_scene *scene, char **str)
{
	scene->camera.cameraray.raypos.x = ft_atoi(str[1]);
	scene->camera.cameraray.raypos.y = ft_atoi(str[2]);
	scene->camera.cameraray.raypos.z = ft_atoi(str[3]);
	scene->camera.cameraup.x = ft_atoi(str[4]);
	scene->camera.cameraup.y = ft_atoi(str[5]);
	scene->camera.cameraup.z = ft_atoi(str[6]);
	scene->camera.cameraray.raypos = rcm_vecnormalize(scene->camera.cameraray.raypos);
	scene->camera.cameradist = rcm_vecnorme(scene->camera.cameraray.raypos);
	scene->camera.cameraray.raydir = rcm_vecnormalize(rcm_vecneg(scene->camera.cameraray.raypos));
	scene->camera.cameraright = rcm_crossproduct(scene->camera.cameraray.raydir, scene->camera.cameraup);
	scene->camera.cameraup = rcm_crossproduct(scene->camera.cameraright, scene->camera.cameraray.raydir);
	scene->camera.viewplaneupleft =
		rcm_vecsum(scene->camera.cameraray.raypos, (scene->camera.cameraray.raydir));
	scene->camera.viewplaneupleft = rcm_vecsum(scene->camera.viewplaneupleft,
	rcm_vecscalarfactor(scene->camera.cameraup, WIN_Y / 2));
	scene->camera.viewplaneupleft = rcm_vecsum(scene->camera.viewplaneupleft,
	rcm_vecneg(rcm_vecscalarfactor(scene->camera.cameraright, -WIN_X / 2)));
	return (42);
}
