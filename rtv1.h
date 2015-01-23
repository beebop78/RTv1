/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 14:32:06 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/22 19:01:35 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "rc_lib/rc_math/rc_math.h"
# include "rc_lib/libft/libft.h"
# include "trente/trente.h"
# include "object.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# define WIN_X 900
# define WIN_Y 700
# define N_FORMS 4
# define ATT 50

typedef struct			s_img
{
	void				*img;
	char				*img_addr;
	int					bytesperpix;
	int					ppl;
	int					endian;
}						t_img;
typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_scene				scene;
	t_img				image;
}						t_env;
t_intersection			*cone_cross(t_scene scene, t_ray ray, double *maxdist);
void					newsphere(t_scene *scene, char **str);
double					get_sphere_t(t_ray ray, t_sphere sphere, double dist);
t_point					get_sphere_normal(t_ray ray, t_sphere sphere,
							t_point i);
int						newspot(t_scene *scene, char **str);
int						newcamera(t_scene *scene, char **str);
int						get_next_line(int fd, char **str);
t_scene					parsing(char *path);
t_intersection			file_intersection(double t, t_ray ray, int color,
						t_matiere matiere);
t_intersection			*spheres_cross(t_scene scene, t_ray ray, double *c);
int						get_light(t_intersection *intersection, t_env env);
t_intersection			*get_intersection(t_env env, t_ray ray,
						t_intersection *(**f)(t_scene, t_ray, double*));
void					newsphere(t_scene *scene, char **str);
void					ft_put_pxl_img(int x, int y, t_env *env, int color);
t_matiere				matiere_init(char *str);
void					display_vector(t_point vec);
void					newplan(t_scene *scene, char **str);
t_intersection			*plans_cross(t_scene scene, t_ray ray, double *maxdist);
void					snailfills(int *coord, int t);
void					anti_aliasing(t_env env);
t_point					reflected_ray(t_point lightray, t_point normal);
int						specular(t_intersection intersection, t_spot spot,
						int color, t_env env);
t_point					get_vec(char **str);
void					newcylinder (t_scene *scene, char **str);
t_point					get_cylinder_normal(t_ray ray, t_cylinder
							cylinder, t_point intersection);
t_intersection			*cylinder_cross(t_scene scene, t_ray ray,
							double *maxdist);
int						shadow_ray(t_intersection intersection, t_env env,
						t_spot spot, int a);
void					newcone (t_scene *scene, char **str);
#endif
