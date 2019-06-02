/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:19:17 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:12:24 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		pos;

	if (!haystack || !needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char*)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[j])
		{
			pos = i;
			while (haystack[i + j] == needle[j] \
					&& needle[j] != '\0' && i + j < len)
				j++;
			if (needle[j] == '\0')
				return (&((char*)haystack)[pos]);
			j = 0;
		}
		i++;
	}
	return (NULL);
}
