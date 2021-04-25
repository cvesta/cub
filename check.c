/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:28:30 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/25 17:09:09 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_argc(int ac, char *map, char *save)
{
	char	*osh;

	osh = NULL;
	if (ac == 1)
		osh = "ft_putstr_fd(""error\nnot enough arguments\n";
	if (ac == 2)
	{
		if (ft_strncmp(map + ft_strlen(map) - 4, ".cub", 4) != 0)
			osh = "error\ninvalid file extension\n";
	}
	if (ac == 3)
	{
		if (ft_strncmp(save, "--save", 6) != 0)
			osh = "error\ninvalid value for '--save'\n";
	}
	if (ac > 3)
		osh = "error\ntoo many arguments";
	if (osh)
	{
		ft_putstr_fd(osh, 1);
		return (0);
	}
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
			ft_putstr_fd("error\nnot enough map arguments\n", 1);
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
