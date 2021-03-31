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

int		parse_tex(t_textures *textures, char *str, int i)
{
	char	*path;
	int		j;

	j = i + 2;
	while (str[j] && make_space(str[j]))
		j++;
	path = str + j;
	if (!check_empty_tex(textures, str, i))
		return (0);
	if (check_path(path) && check_extension(path))
		return (0);
	if ((ft_strncmp(str + i, "NO", 2) == 0) && !textures->north)
		textures->north = ft_strdup(path);
	if ((ft_strncmp(str + i, "SO", 2) == 0) && !textures->south)
		textures->south = ft_strdup(path);
	if ((ft_strncmp(str + i, "WE", 2) == 0) && !textures->west)
		textures->west = ft_strdup(path);
	if ((ft_strncmp(str + i, "EA", 2) == 0) && !textures->east)
		textures->east = ft_strdup(path);
	if ((str[i] == 'S' && str[i + 1] == ' ') && !textures->sprite)
		textures->sprite = ft_strdup(path);
	return (1);
}

int		check_empty_tex(t_textures *textures, char *str, int i)
{
	if ((ft_strncmp(str + i, "NO", 2) == 0 && textures->north) ||
		(ft_strncmp(str + i, "SO", 2) == 0 && textures->south) ||
		(ft_strncmp(str + i, "WE", 2) == 0 && textures->west) ||
		(ft_strncmp(str + i, "EA", 2) == 0 && textures->east))
	{
		ft_putstr_fd("error\nnot empty tex\n", 1);
		return (0);
	}
	if ((str[i] == 'S' && str[i + 1] == ' ') && textures->sprite)
	{
		ft_putstr_fd("error\nnot empty tex\n", 1);
		return (0);
	}
	return (1);
}

int		check_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("error\nno such file or directory\n", 1);
		return (0);
	}
	close(fd);
	return (1);
}

int		check_extension(char *path)
{
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) != 0)
	{
		ft_putstr_fd("error\ninvalid file extension\n", 1);
		return (0);
	}
	return (1);
}
