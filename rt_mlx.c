/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 17:30:02 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/22 18:44:13 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "mlx.h"

void		ft_put_pxl_img(int x, int y, t_env *env, int color)
{
	int p;

	p = x * env->image.bytesperpix / 8 + y * env->image.ppl;
	if (env->image.endian)
	{
		env->image.img_addr[p] = (color & 0xFF0000) >> 16;
		env->image.img_addr[p + 1] = (color & 0x00FF00) >> 8;
		env->image.img_addr[p + 2] = (color & 0x0000FF);
	}
	else
	{
		env->image.img_addr[p + 2] = (color & 0xFF0000) >> 16;
		env->image.img_addr[p + 1] = (color & 0x00FF00) >> 8;
		env->image.img_addr[p] = (color & 0x0000FF);
	}
}

int			keyhook(int keycode, t_env *env)
{
	if (keycode == 65307)
		exit(0);
}

int			display_img(t_env *env)
{
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
}

void		mlx(t_env env)
{
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_X - 23, WIN_Y - 23,
		"yamete kudasai !!!");
	env.image.img = mlx_new_image(env.mlx, WIN_X, WIN_Y);
	env.image.img_addr = mlx_get_data_addr(env.image.img,
	&(env.image.bytesperpix), &(env.image.ppl), &(env.image.endian));
	raytracer(env);
	mlx_expose_hook(env.win, display_img, &env);
	mlx_key_hook(env.win, keyhook, &env);
	mlx_loop(env.mlx);
}
