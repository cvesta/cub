/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:39:46 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/18 15:23:50 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *needle, size_t len)
{
	size_t	p;
	size_t	i;

	if (!*needle)
		return ((char *)str);
	p = 0;
	while (str[p] != '\0' && p < len)
	{
		if (str[p] == needle[0])
		{
			i = 1;
			while (needle[i] != '\0' && str[p + i] == needle[i] && p + i < len)
				++i;
			if (needle[i] == '\0')
				return ((char *)&str[p]);
		}
		p++;
	}
	return (0);
}
