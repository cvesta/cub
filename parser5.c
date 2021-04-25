/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:29:35 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/01 15:54:54 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		save_color(t_cub *cub, char *str, char **arr)
{
	char	*tr;
	char	*tg;
	char	*tb;

	tr = ft_strtrim(arr[0], " ");
	tg = ft_strtrim(arr[1], " ");
	tb = ft_strtrim(arr[2], " ");

	if (!check_color_max_min(tr) || !check_color_max_min(tg) ||
	!check_color_max_min(tb))
		return (0);
	if (ft_strncmp(str, "F", 1) == 0)
		cub->down = turn_hex(0, ft_atoi(tr), ft_atoi(tg), ft_atoi(tb));
	if (ft_strncmp(str, "C", 1) == 0)
		cub->down = turn_hex(0, ft_atoi(tr), ft_atoi(tg), ft_atoi(tb));
	free(tr);
	free(tg);
	free(tb);
	return (1);
}

int		check_color_max_min(char *color)
{
	int		i;

	i = ft_atoi(color);
	if(!(i >= 0 && i <= 255))
	{
		ft_putstr_fd("error\nwrong color\n", 1);
		return (0);
	}
	if (ft_strlen(color) > 1 && i < 1)
	{
		ft_putstr_fd("error\nthe value exceeds the max\n", 1);
		return (0);
	}
	if (ft_strlen(color) > 10)
	{
		ft_putstr_fd("error\nthe value exceeds the max\n", 1);
	}
	return (1);
}

int		check_empty_color(t_cub *cub, char *str)
{
	if (((ft_strncmp(str, "F", 1) == 0) && (cub->down != -1)) || ((ft_strncmp
	(str, "C", 1) == 0) && (cub->down != -1)))
	{
		ft_putstr_fd("error\n, not empty color\n", 1);
		return (0);
	}
	return (1);
}

int		check_color(char **arr)
{
	int		i;
	char	*line;

	i = 0;
	while (arr[i])
	{
		if (!(line = ft_strtrim(arr[i++], " ")))
			return (0);
		if (!ft_strlen(line) || !check_number(line) ||(line[0] == '0' &&
		ft_strlen(line) > 1))
		{
			ft_putstr_fd("error\nincorrect extension for color\n", 1);
			free (line);
			return (0);
		}
		free (line);
	}
	if (i != 3)
	{
		ft_putstr_fd("error\nincorrect nuber of arguments for color\n", 1);
		return (0);
	}
	return (1);
}

int		parse_color(t_cub *cub, char *str)
{
	char	**arr;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
		if (str[i++] == ',')
			count++;
		if (count > 2)
		{
			ft_putstr_fd("error\ninvalid number of arguments for color\n", 1);
			return (0);
		}
	if (!(arr = ft_split(str + 1, ',')))
		return (0);
	if (!check_color(arr) || !check_empty_color(cub, str) || !save_color(cub,
																	 str, arr))
	{
		clear_arr(arr);
		return (0);
	}
	clear_arr(arr);
	return (1);
}