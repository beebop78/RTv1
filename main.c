/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 16:57:59 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/22 18:37:35 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int main(int ac, char **av)
{
	t_env env;

	if (ac > 1)
		env.scene = parsing(av[1]);
	else
	{
		ft_putendl("Error : No input file");
		exit(0);
	}
	mlx(env);
	return (0);
}
