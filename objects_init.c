/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:24:23 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/12 20:56:58 by rcargou          ###   ########.fr       */
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
	t_sphere	*tmp;
	int			a;
	int			b;
	int			c;

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
	a = ft_atoi(str[6]) << 16;
	b = ft_atoi(str[7]) << 8;
	c = ft_atoi(str[8]);
	tmp->color = a + b + c;
	tmp->next = malloc(sizeof(t_sphere));
	tmp->next->next = NULL;
}

void		newspot(t_scene *scene, char **str)
{
	t_spot *tmp;
	int a;
	int b;
	int c;

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
	scene->camera.cameradist = rcm_vecnorme(scene->camera.cameraray.raypos);
	scene->camera.cameraray.raydir = rcm_vecnormalize(rcm_vecneg(scene->camera.cameraray.raypos));
	scene->camera.cameraup = rcm_rotmatrice(scene->camera.cameraray.raydir, -1.57, 0.0f, 0.0f);
	scene->camera.cameraright = rcm_rotmatrice(scene->camera.cameraray.raydir, 0.0f, 1.57, 0.0f);
	scene->camera.viewplaneupleft = rcm_vecsum(scene->camera.cameraray.raypos, (scene->camera.cameraray.raydir));
	scene->camera.viewplaneupleft = rcm_vecsum(scene->camera.viewplaneupleft,
	rcm_vecscalarfactor(scene->camera.cameraup, WIN_Y / 2 * scene->camera.cameradist));
	scene->camera.viewplaneupleft = rcm_vecsum(scene->camera.viewplaneupleft,
	rcm_vecneg(rcm_vecscalarfactor(scene->camera.cameraright, -WIN_X / 2 * scene->camera.cameradist)));
	return (42);
}
