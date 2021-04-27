/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:27:40 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/31 17:10:24 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			parse_tex(t_textures *texture, char *str, int a)
{
	char	*way;
	int		z;

	z = a + 2;
	while (str[z] && make_space(str[z]))
		z++;
	way = str + z;
	if (!if_tex_empty(texture, str, a))
		return (0);
	if (!check_path(way) && !check_extension(way))
		return (0);
	if ((ft_strncmp(str + a, "NO", 2) == 0) && !texture->north)
		texture->north = ft_strdup(way);
	if ((ft_strncmp(str + a, "SO", 2) == 0) && !texture->south)
		texture->south = ft_strdup(way);
	if ((ft_strncmp(str + a, "WE", 2) == 0) && !texture->west)
		texture->west = ft_strdup(way);
	if ((ft_strncmp(str + a, "EA", 2) == 0) && !texture->east)
		texture->east = ft_strdup(way);
	if ((str[a] == 'S' && str[a + 1] == ' ') && !texture->s)
		texture->s = ft_strdup(way);
	return (1);
}

int			if_tex_empty(t_textures *texture, char *str, int i)
{
	if ((ft_strncmp(str + i, "NO", 2) == 0 && texture->north) ||
		(ft_strncmp(str + i, "SO", 2) == 0 && texture->south) ||
		(ft_strncmp(str + i, "WE", 2) == 0 && texture->west) ||
		(ft_strncmp(str + i, "EA", 2) == 0 && texture->east))
	{
		ft_putstr_fd(":(\ntex is empty\n", 1);
		return (0);
	}
	if ((str[i] == 'S' && str[i + 1] == ' ') && texture->s)
	{
		ft_putstr_fd(":(\ntex is empty\n", 1);
		return (0);
	}
	return (1);
}

int			check_path(char *way)
{
	int		fd;

	fd = open(way, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(":(\nno such file or dir\n", 1);
		return (0);
	}
	close(fd);
	return (1);
}

int			check_extension(char *way)
{
	if (ft_strncmp(way + ft_strlen(way) - 4, ".xpm", 4) != 0)
	{
		ft_putstr_fd(":(\nincorrect extension\n", 1);
		return (0);
	}
	return (1);
}
