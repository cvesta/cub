/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:28:30 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/30 16:53:16 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_argc(int ac, char *map, char *save)
{
	if (ac == 1)
		return (ft_putstr_fd("error\nnot enough arguments\n", 1));
	if (ac == 2)
	{
		if (ft_strncmp(map + ft_strlen(map) - 4, ".cub", 4) != 0)
			return (ft_putstr_fd("error\ninvalid file extension\n", 1));
	}
	if (ac == 3)
	{
		if (ft_strncmp(save, "--save", 6) != 0)
			return (ft_putstr_fd("error\ninvalid value for '--save'\n", 1))
	}
	if (ac > 3)
		return (ft_putstr_fd("error\ntoo many arguments", 1));
	return (1);
}

int		check_empty_arg(t_cub *cub, int map)
{
	if ((cub->width == -1) || (cub->height == -1) || (cub->down == -1) ||
	(cub->up == -1) || (cub->textures.north == 0) || (cub->textures.south ==
	0) || (cub->textures.west == 0) || (cub->textures.east == 0) ||
	(cub->textures.sprite == 0))
	{
		if (map && (cub->map == 0))
			ft_putstr_fd(("error\nnot enough map arguments\n", 1));
		return (0);
	}
	return (1);
}

int		check_number(char *num)
{
	int		i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}
