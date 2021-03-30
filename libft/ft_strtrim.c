/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 16:34:16 by cvesta            #+#    #+#             */
/*   Updated: 2020/11/16 19:33:32 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	length;
	char	*ss;

	if (!s1 || !set)
		return (NULL);
	length = 0;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (s1[length] != '\0')
		length++;
	while (length && ft_strchr(set, s1[length]))
		length--;
	ss = ft_substr((char *)s1, 0, length + 1);
	return (ss);
}
