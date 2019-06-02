/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:53:27 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:12:00 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		pos;

	if (!haystack || !needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char*)haystack);
	i = 0;
	j = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[j])
		{
			pos = i;
			while (haystack[i + j] == needle[j] && needle[j] != '\0')
				j++;
			if (needle[j] == '\0')
				return (&((char*)haystack)[pos]);
			j = 0;
		}
		i++;
	}
	return (NULL);
}
