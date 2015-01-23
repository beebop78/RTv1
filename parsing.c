/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 18:59:53 by rcargou           #+#    #+#             */
/*   Updated: 2015/01/22 18:33:22 by rcargou          ###   ########.fr       */
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
	if (error == 0 || !(*str))
		return (NULL);
	return (str);
}

t_scene			select_func(char **splited_str, int len, t_scene new,
					int *camok)
{
	if (!ft_strcmp(splited_str[0], "SPHERE") && len >= 10)
		newsphere(&new, splited_str);
	else if (!ft_strcmp(splited_str[0], "SPOT") && len >= 8)
		*camok += newspot(&new, splited_str);
	else if (!ft_strcmp(splited_str[0], "PLAN") && len >= 12)
		newplan(&new, splited_str);
	else if (!ft_strcmp(splited_str[0], "CAMERA") && len >= 9)
		*camok += newcamera(&new, splited_str);
	else if (!ft_strcmp(splited_str[0], "CYLINDER") && len >= 14)
		newcylinder(&new, splited_str);
	else if (!ft_strcmp(splited_str[0], "CONE") && len >= 13)
		newcone(&new, splited_str);
	return (new);
}

t_scene			parsing(char *path)
{
	t_scene		new;
	char		*str;
	char		**splited_str;
	int			camok;
	int			len;

	camok = 0;
	new.spheres = NULL;
	new.spots = NULL;
	new.plans = NULL;
	new.cylinders = NULL;
	while ((str = reader(path)) != NULL)
	{
		splited_str = ft_strsplit(str, ' ');
		len = ft_tabstrlen(splited_str);
		new = select_func(splited_str, len, new, &camok);
	}
	if (camok < (84))
		exit(0);
	return (new);
}
