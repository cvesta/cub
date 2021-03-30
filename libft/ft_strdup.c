/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:46:09 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/10 16:02:10 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		length;
	int		i;

	length = 0;
	i = 0;
	while (s1[length] != '\0')
		length++;
	dup = ((char*)malloc(sizeof(*dup) * length + 1));
	if (dup == 0)
		return (0);
	while (i < length)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
