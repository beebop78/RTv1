/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 20:44:34 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/13 11:32:36 by rcargou          ###   ########.fr       */
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
typedef struct			s_camera
{
	t_ray				cameraray;
	t_point				cameraup;
	t_point				cameraright;
	t_point				viewplaneupleft;
	double				cameradist;
}						t_camera;
typedef struct			s_sphere
{
	t_point				spherepos;
	int					radius;
	t_matiere			matiere;
	unsigned int		color;
	struct s_sphere		*next;
}						t_sphere;
typedef struct			s_plan
{
	t_matiere			matiere;
	t_point				planpos;
	t_point				plannormal;
	unsigned int		color;
	struct s_plan		*next;
}						t_plan;
typedef struct			s_spot
{
	t_point				spotpos;
	int					color;
	struct s_spot		*next;
}						t_spot;
typedef struct			s_scene
{
    t_sphere			*spheres;
    t_plan				*plans;
    t_camera			camera;
    struct s_spot		*spots;
}						t_scene;
typedef struct			s_intersection
{
	double				dist;
	t_point				interpos;
	t_point				normal;
	t_matiere			*matiere;
	int					color;
}						t_intersection;
#endif
