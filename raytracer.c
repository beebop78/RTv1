/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 21:53:36 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/16 17:47:38 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				init_func_tab(t_intersection *(**f)(t_scene, t_ray, double*))
{
	f[0] = spheres_cross;
	f[1] = plans_cross;
}

t_intersection		file_intersection(double t, t_ray ray, int color, t_matiere matiere1)
{
	t_intersection			intersection;

	intersection.interpos = rcm_vecsum(rcm_vecscalarfactor(ray.raydir, t), ray.raypos);
	intersection.matiere = matiere1;
	intersection.color = color;
	intersection.dist = t;
	return (intersection);
}

t_intersection		*get_intersection(t_env env, t_ray ray,
	t_intersection *(*f[])(t_scene, t_ray, double*))
{
	int					i;
	double				maxdist;
	t_intersection		*intersection;
	t_intersection		*object;

	i = 0;
	object = NULL;
	maxdist = 2000;
	while (i < N_FORMS)
	{
		intersection = NULL;
		intersection = f[i](env.scene, ray, &maxdist);
		if(intersection != NULL)
			object = intersection;
		i++;
	}
	return (object);
}

void				render(t_env env, int x, int y)
{


}

void				raytracer(t_env env)
{
	int					x;
	int					y;
	int					color;
	t_ray				ray;
	t_intersection		*intersection;
	t_intersection		*(**f)(t_scene, t_ray, double*);

	y = -1;
	ray.raydir = env.scene.camera.cameraray.raydir;
	f = malloc(sizeof(*f) * N_FORMS);
	init_func_tab(f);
	env.scene.func = f;
	while (++y < WIN_Y)
	{
		x = -1;
		while (++x < WIN_X)
		{
			color = 0;
			ray.raypos = rcm_vecsum(env.scene.camera.viewplaneupleft,
				rcm_vecscalarfactor(env.scene.camera.cameraright, (x - WIN_X)));
			ray.raypos = rcm_vecsum(ray.raypos,
				rcm_vecscalarfactor(env.scene.camera.cameraup, (y - WIN_Y)));
			intersection = get_intersection(env, ray, f);
			if (intersection)
				color = get_light(intersection, env);
			ft_put_pxl_img(x, y, &env, color);
			mlx_pixel_put(env.mlx, env.win, x, y, color);
		}
	}
}
