/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:38:29 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/13 16:33:15 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	a;
	size_t	b;

	if (!s1 || !s2)
		return (NULL);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	s3 = (char *)malloc(sizeof(*s1) * (a + b + 1));
	if (!s3)
		return (NULL);
	a = 0;
	b = 0;
	while (s1[a])
		s3[b++] = s1[a++];
	a = 0;
	while (s2[a])
		s3[b++] = s2[a++];
	s3[b] = '\0';
	return (s3);
}
