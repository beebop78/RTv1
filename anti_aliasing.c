/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 01:54:36 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/17 14:35:07 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int get_color(t_img image, int x, int y, int tmp2)
{
	unsigned char		a;
	unsigned char		b;
	unsigned char		c;
	int					new;
	int					tmp;

	if (image.endian)
	{
		a = image.img_addr[x * image.bytesperpix / 8 + y * image.pixperline];
		b = image.img_addr[x * image.bytesperpix / 8 + y * image.pixperline + 1];
		c = image.img_addr[x * image.bytesperpix / 8 + y * image.pixperline + 2];
	}
	else
	{
		a = image.img_addr[x * image.bytesperpix / 8 + y * image.pixperline + 2];
		b = image.img_addr[x * image.bytesperpix / 8 + y * image.pixperline + 1];
		c = image.img_addr[x * image.bytesperpix / 8 + y * image.pixperline];
	}
	new = a;
	tmp = b;
	tmp2 = c;
	return ((new << 16) + (tmp << 8) + tmp2);
}

void anti_aliasing(t_env env)
{
	int x;
	int y;
	int c1;
	int c2;

	y = 10;
	while (++y < WIN_Y)
	{
		x = 10;
		while (++x < WIN_X)
		{
			c1 = get_color(env.image, x, y, 0);
			c2 = get_color(env.image, x - 1, y - 1, 0);
			if (color_diff(c1, c2) > 200)
			{
				mlx_pixel_put(env.mlx, env.win, x, y, color_average(c1, c2));
				ft_put_pxl_img(x, y, &env, color_average(c1, c2));
			}
	}
	}
}
