/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:19:41 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/07 18:00:47 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	size_t			i;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = 0;
	a = (unsigned char *)s;
	while (i < n)
	{
		if (*a == ch)
			return (a);
		a++;
		i++;
	}
	return (NULL);
}
