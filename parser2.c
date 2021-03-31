/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:22:32 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/31 19:54:39 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_arg(t_cub *cub, char *str)
{
	int 	i;

	i = 0;
	if (str[i] == '\n' || str[i] == '\0')
		return (1);
	while (str[i] && make_space(str[i]))
		i++;
	if (!ft_strchr("RNSEWFC1", str[i]) || (ft_strchr("RNSEWFC", str[i]) &&
	!str[i + 1]))
	{
		ft_putstr_fd("error\ninvalid map argument\n", 1);
		return (0);
	}
	if (str[i] == '1' && !check_empty_arg(cub, 0))
	{
		ft_putstr_fd("error\nmap position", 1);
		return (0);
	}
	if (!arg_write_cub(cub, str, i))
		return (0);
	return (1);
}

int		arg_write_cub(t_cub *cub, char *str, int i)
{
	if ((str[i] == 'R' && str[i + 1] == ' ') &&
		!parse_r(cub, str + i + 2))
		return (0);
	if ((ft_strncmp(str + i, "NO", 2) == 0 ||
		ft_strncmp(str + i, "SO", 2) == 0 ||
		ft_strncmp(str + i, "WE", 2) == 0 ||
		ft_strncmp(str + i, "EA", 2) == 0 ||
		(str[i] = 'S' && str[i + 1] == ' ')) &&
		!parse_tex(&cub->textures, str, i))
		return (0);
	if (((str[i] == 'F' && str[i + 1] == ' ') || (str[i] == 'C' && str[i + 1]
	== ' ')) && !parse_color(cub, str + i))
		return (0);
	return (1);
}
