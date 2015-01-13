/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 21:53:36 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/13 14:31:10 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				init_func_tab(t_intersection»·»···»···»···(*f[])(t_scene, t_ray, double);)
{
	f[0] = spheres_cross;
}

t_intersection		file_intersection(double t, t_ray ray, int color, t_matiere matiere)
{
	t_intersection			intersection;

	intersection.interpos = rcm_vecsum(rcm_vecscalarfactor(ray.raydir, t), ray.pos);
	intersection.matiere = matiere;
	intersection.color = color;
	intersection.dist = t;
	return (intersection);
}

t_intersection		*get_intersection(t_env env, t_ray ray,
		t_intersection»·»···»···»···(*f[])(t_scene, t_ray, double*))
{
	int					i;
	double				maxdist;
	t_intersection		*intersection;
	t_intersection		*object;

	maxdist = 2000;
	while (i < N_FORMS)
	{
		intersection = f[i](env.scene, ray, &maxdist);
		if(intersection != NULL)
			object = intersection;
	}
	return (object);
}

int					get_light(t_intersection *intersection, t_env env)
{
	t_spot		*cross
	int			color;

	color = 0;
	cross = env.scene.spots
	while (cross != NULL)
	{

		cross = cross->next;
	}
	return (color);
}

void				raytracer(t_env env)
{
	int					x;
	int					y;
	int					color;
	t_ray				ray;
	t_intersection		*intersection;
	t_intersection		*(*f[N_FORMS])(t_scene, t_ray, double);

	color = 0;
	x = -1;
	y = -1;
	ray.raydir = env.scene.camera.cameraray.raydir;
	init_func_tab(f);
	while (++x < WIN_X)
	{
		while (++y < WIN_Y)
		{
			ray.raypos = rcm_vecsum(env.scene.viewplaneupleft,
				rcm_vecscalarfactor(env.scene.camera.cameraright, x));
			ray.raypos = rcm_vecsum(ray.raypos,
				rcm_vecscalarfactor(env.scene.camera.cameraup, -y));
			intersection = get_intersection(env, ray);
			color = get_light(intersection, t_env env);
		}
	}
}
