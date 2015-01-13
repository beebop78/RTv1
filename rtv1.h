/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 14:32:06 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/13 12:40:43 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "rc_lib/rc_math/rc_math.h"
# include "rc_lib/libft/libft.h"
# include "trente/trente.h"
# include "object.h"
# include "mlx.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# define WIN_X 400
# define WIN_Y 300
# define N_FORMS 1

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_scene				scene;
	void				*img;
	char				*img_addr;
}						t_env;
void					newsphere(t_scene *scene, char **str);
double					get_sphere_t(t_ray ray, t_sphere sphere, int dist);
t_point					get_sphere_normal(t_ray ray, t_sphere sphere, t_point i);
void					newspot(t_scene *scene, char **str);
int						newcamera(t_scene *scene, char **str);
int						get_next_line(int fd, char **str);
t_scene					parsing(char *path);
t_intersection			file_intersection(double t, t_ray ray, int color, t_matiere matiere);
t_intersection			*spheres_cross(t_scene scene, t_ray ray);
#endif
