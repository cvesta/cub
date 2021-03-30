/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:22:32 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/30 18:47:51 by cvesta           ###   ########.fr       */
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
	if (!)
}

int
