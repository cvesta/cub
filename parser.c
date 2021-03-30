/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:09:29 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/30 15:43:01 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_map(int fd, t_cub *cub)
{
	char	*line;
	int		i;

	i = 1;
	while (get_next_line(fd, &line))
	{
		if (!())
	}
}

int		parser(t_cub *cub, char *map)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (!read_map(fd, cub) || )
	if (fd == -1)
	{
		ft_putstr_fd("error\nno such file or directory\n", 1);
		return (0);
	}
}