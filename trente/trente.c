/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trente.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcargou <rcargou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 19:25:38 by rcargou           #+#    #+#             */
/*   Updated: 2014/11/25 17:11:25 by rcargou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trente.h"
#include <stdlib.h>

int line_finished(char *buff, char **new, int ret)
{
	int			len;
	char		*mem;
	int			a;
	int			lenbuff;

	lenbuff = ft_strlen(buff);
	a = -1;
	mem = ft_strchr(buff, '\n');
	len = mem - buff;
	if (!ret)
		if (ft_strlen(*new))
		{
			*buff = '\0';
			return (1);
		}
	if (!ret)
		return (0);
	if (!mem)
		*new = ft_strjoin(*new, buff);
	if (!mem)
		return (2);
	*new = ft_strjoin(*new, ft_strncpy(ft_strnew(BUFF_SIZE + 1), buff, len));
	while (++a + len <= lenbuff + 1)
		buff[a] = buff[a + len + 1];
	return (1);
}

int get_next_line(int fd, char **line)
{
	static char		*buff = 0;
	int				ret;
	char			*new;

	new = ft_strnew(1);
	*line = ft_strnew(1);
	if (!buff)
		buff = ft_strnew(BUFF_SIZE + 1);
	if (ft_strlen(buff))
		if (((line_finished(buff, line, 1))) == 1)
			return (1);
	while (!ft_strchr(buff, '\n') && (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!ft_strchr(buff, '\n'))
			new = ft_strjoin(new, buff);
	}
	if (ret < 0)
		return (ret);
	*line = ft_strjoin(*line, new);
	return (line_finished(buff, line, ret));
}
