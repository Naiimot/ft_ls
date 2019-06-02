/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:41:03 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:05:21 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	if (dst && src)
	{
		i = 0;
		while (src[i] && i < len)
		{
			dst[i] = src[i];
			i++;
		}
		if (i != len)
		{
			while (i < len)
			{
				dst[i] = '\0';
				i++;
			}
		}
	}
	return (dst);
}
