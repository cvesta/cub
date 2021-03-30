/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 22:30:32 by cvesta            #+#    #+#             */
/*   Updated: 2021/01/12 18:50:22 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

static int		linebuf(char **line, char *buf)
{
	char		*temp;

	temp = *line;
	if (!(*line = ft_strjoin(*line, buf)))
		return (-1);
	ft_free(&temp);
	return (0);
}

static int		ost_check(char *ost, char **line)
{
	char		*p_n;

	p_n = NULL;
	if (ost)
	{
		if ((p_n = ft_strchr(ost, '\n')))
		{
			*p_n = '\0';
			if (!(*line = ft_strdup(ost)))
				return (-1);
			ft_strcpy(ost, ++p_n);
			return (1);
		}
		else
		{
			if (!(*line = ft_strdup(ost)))
				return (-1);
			return (0);
		}
	}
	else if (!(*line = ft_strdup("")))
		return (-1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			r_b;
	char		*p_n;
	static char	*ost = NULL;
	int			flag;

	flag = 0;
	r_b = 0;
	p_n = NULL;
	if ((fd < 0) || (BUFFER_SIZE <= 0) || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	if ((flag = ost_check(ost, line)) != 1)
		ft_free(&ost);
	while (!p_n && !flag && (r_b = read(fd, buf, BUFFER_SIZE)))
	{
		buf[r_b] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			if (!(ost = ft_strdup(++p_n)))
				return (-1);
		}
		linebuf(line, buf);
	}
	return ((flag == 1 || r_b) ? 1 : 0);
}
