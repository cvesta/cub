/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:31:07 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/31 15:07:07 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_r(t_cub *cub, char *str)
{
	char	**arr;
	int		width;
	int		height;

	if (!(arr = ft_split(str, ' ')))
		return (0);
	if (!check_r(arr))
	{
		clear_arr(arr);
		return (0);
	}
	width = ft_atoi(arr[0]);
	height = ft_atoi(arr[1]);
	if (!check_empty_r(width, height, cub) || !check_max_r(width, height, arr))
	{
		clear_arr(arr);
		return (0);
	}
	cub->width = width;
	cub->height = height;
	clear_arr(arr);
	return (1);
}

int 	check_r(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (!check_number(arr[i]) || (ft_strlen(arr[i]) > 1 && arr[i][0] ==
		'0'))
		{
			ft_putstr_fd("error\nscreen extension is incorrect for R\n", 1);
			return (0);
		}
		i++;
	}
	if (i != 2)
	{
		ft_putstr_fd("error\ninvalid number of arguments for R\n", 1);
		return (0);
	}
	return (1);
}

int		check_empty_r(int width, int height, t_cub *cub)
{
	if (width <= 0 || height <= 0)
	{
		ft_putstr_fd("error\nscreen extension is incorrect for R\n", 1);
		return (0);
	}
	if (cub->width != -1 || cub->height != -1)
	{
		ft_putstr_fd("error\nnot empty R\n", 1);
		return (0);
	}
	return (1);
}

int		check_max_r(int width, int height, char **arr)
{
	if ((ft_strlen(arr[0]) > 10 || ft_strlen(arr[1]) > 10) ||
		(ft_strlen(arr[0]) > 1 && width < 1) ||
		(ft_strlen(arr[1]) > 1 && height < 1))
	{
		ft_putstr_fd("error\nmax int excess\n", 1);
		return (0);
	}
	return (1);
}