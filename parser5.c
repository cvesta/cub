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

int		check_color(char **arr)
{
	int		i;
	char	*line;

	i = 0;
	while (arr[i])
	{
		if (!(line = ft_strtrim(arr[i++], " ")))
			return (0);
	}
}

int		parse_color(t_cub *cub, char *str)
{
	char	**arr;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
		if (str[i++] = ',')
			count++;
		if (count > 2)
		{
			ft_putstr_fd("error\ninvalid number of arguments for color\n", 1);
			return (0);
		}
	if (!(arr = ft_split(str + 1, ',')))
		return (0);
	if (!check_color(arr))
}