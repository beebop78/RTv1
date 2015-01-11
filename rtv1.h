/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 14:32:06 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/11 21:39:29 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "rc_lib/rc_math/rc_math.h"
# include "rc_lib/libft/libft.h"
# include "object.h"
# include <stdlib.h>
# define WIN_X 500
# define WIN_Y 400

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_scene				scene;
}						t_env;
void					newsphere(t_scene *scene, char **str);
double					get_sphere_t(t_ray ray, t_sphere sphere);
t_point					get_sphere_normal(t_ray ray, t_sphere sphere, t_point i);
#endif
