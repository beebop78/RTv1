/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 21:53:36 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/21 18:14:39 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				init_func_tab(t_intersection *(**f)(t_scene, t_ray, double*))
{
	f[0] = spheres_cross;
	f[1] = plans_cross;
	f[2] = cylinder_cross;
	f[3] = cone_cross;
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
		{
			if (object)
				free(object);
			object = intersection;
		}
			i++;
	}
	return (object);
}

void				render(t_env env, int x1, int y1)
{
	int color;
	t_ray ray;
	t_intersection *intersection;

	ray.raydir = env.scene.camera.cameraray.raydir; 
	intersection = NULL;
	color = 0;
	ray.raypos = rcm_vecsum(env.scene.camera.viewplaneupleft,
	rcm_vecscalarfactor(env.scene.camera.cameraright, (x1 - WIN_X)));
	ray.raypos = rcm_vecsum(ray.raypos,
	rcm_vecscalarfactor(env.scene.camera.cameraup, (y1 - WIN_Y)));
	intersection = get_intersection(env, ray, env.scene.func);
	if (intersection)
		color = get_light(intersection, env);
	ft_put_pxl_img(x1 - 4, y1, &env, color);
	mlx_pixel_put(env.mlx, env.win, x1 - 4, y1, color);
}
void				call_render(t_env env, int *coord, int t, int ty)
{
	int x;
	int y;

	y = -1;
	coord[0] = 0;
	coord[1] = 0;
	snailfills(NULL, 1);
	while (++y < ((WIN_Y) / 4))
	{
		x = -1;
		while (++x < ((WIN_X) / 4))
		{
			snailfills(coord, 0);
			render(env, coord[0] + t, coord[1] + ty);
		}
	}
}

void				raytracer(t_env env)
{
	int					*coord;
	t_intersection		*(**f)(t_scene, t_ray, double*);
	int t;
	int ty;

	t = 1;
	ty = 0;
	coord = ft_memalloc(32);
	f = malloc(sizeof(*f) * N_FORMS);
	init_func_tab(f);
	env.scene.func = f;
	while (ty < 4)
	{
		t = 0;
		while (t < 4)
		{
			call_render(env, coord, t, ty);
			t++;
		}
		ty++;
	}
	anti_aliasing(env);
}
