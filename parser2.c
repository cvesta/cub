/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:22:32 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 22:23:06 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			parse_arg(t_cub *cub, char *str)
{
	int		a;

	a = 0;
	if (str[a] == '\n' || str[a] == '\0')
		return (1);
	while (str[a] && make_space(str[a]))
		a++;
	if (!ft_strchr("RNSEWFC1", str[a]) ||
		(ft_strchr("RNSEWFC", str[a]) && !str[a + 1]))
	{
		ft_putstr_fd(":(\nincorrect arg for map\n", 1);
		return (0);
	}
	if (str[a] == '1' && !if_arg_empty(cub, 0))
	{
		ft_putstr_fd(":(\nincorrect map position\n", 1);
		return (0);
	}
	if (!save_to_cub(cub, str, a))
		return (0);
	return (1);
}

int			save_to_cub(t_cub *cub, char *str, int i)
{
	if ((str[i] == 'R' && str[i + 1] == ' ') &&
		!parse_r(cub, str + i + 2))
		return (0);
	if ((ft_strncmp(str + i, "NO", 2) == 0 ||
	ft_strncmp(str + i, "SO", 2) == 0 ||
	ft_strncmp(str + i, "WE", 2) == 0 ||
	ft_strncmp(str + i, "EA", 2) == 0 ||
	(str[i] == 'S' && str[i + 1] == ' ')) &&
	!parse_tex(&cub->texture, str, i))
		return (0);
	if (((str[i] == 'F' && str[i + 1] == ' ') ||
	(str[i] == 'C' && str[i + 1] == ' ')) &&
	!parse_colour(cub, str + i))
		return (0);
	return (1);
}
