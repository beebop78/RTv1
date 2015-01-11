/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 15:18:17 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/11 21:35:33 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "rc_lib/rc_math/rc_math.h"

typedef struct			s_ray
{
	t_point				raypos;
	t_point				raydir;
}						t_ray;
typedef struct			s_matiere
{
	double				i;
	double				opacite;
}						t_matiere;
typedef struct			s_sphere
{
	t_point				spherepos;
	int					radius;
	t_matiere			matiere;
	unsigned int		color;
	double				(*gett)(t_ray, struct s_sphere);
	t_point				(*getnormal)(t_ray, struct s_sphere, t_point t);
	struct s_sphere		*next;
}						t_sphere;
typedef struct			s_plan
{
	t_matiere			matiere;
	t_point				planpos;
	t_point				plannormal;
	unsigned int		color;
	double				(*gett)(t_ray, struct s_plan);
	t_point				(*getnormal)(t_ray, struct s_plan);
	struct s_plan		*next;
}						t_plan;
typedef struct			s_spot
{
	t_point				spotpos;
	unsigned int		color;
}						t_spot;
typedef struct			s_scene
{
	t_sphere			*spheres;
	t_plan				*plans;
	t_ray				camera;
	struct s_spot		*spots;
}						t_scene;
typedef struct			s_intersection
{
	double				dist;
	t_point				interpos;
	t_point				normal;
	t_matiere			*matiere;
}						t_intersection;
#endif
