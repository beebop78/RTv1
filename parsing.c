/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 18:59:53 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/15 17:41:54 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char		*reader(char *path)
{
	static int		fd = 0;
	char			*str;
	int				error;

	if (!fd)
		fd = open(path, O_RDONLY);
	error = get_next_line(fd, &str);
	if (error < 0)
	{
		ft_putendl("Error : invalid input file");
		exit(0);
	}
	if (error == 0)
		return (NULL);
	return (str);
}

t_scene			parsing(char *path)
{
	t_scene		new;
	char		*str;
	char		**splited_str;
	int			camok;

	camok = 0;
	new.spheres = NULL;
	new.spots = NULL;
	new.plans = NULL;
	while ((str = reader(path)) != NULL)
	{
		splited_str = ft_strsplit(str, ' ');
		if (!ft_strcmp(splited_str[0], "SPHERE"))
			newsphere(&new, splited_str);
		else if (!ft_strcmp(splited_str[0], "SPOT"))
			newspot(&new, splited_str);
		else if (!ft_strcmp(splited_str[0], "PLAN"))
			newplan(&new, splited_str);
		else if (!ft_strcmp(splited_str[0], "CAMERA"))
			camok += newcamera(&new, splited_str);
	}
	if (!camok)
		exit(0);
	return (new);
}
