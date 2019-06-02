/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:13:28 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:32:29 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (dst && src && size)
	{
		while (dst[i] && i < size)
			i++;
		while (src[j] && j + i < size - 1)
		{
			dst[i + j] = src[j];
			j++;
		}
		if (i + j < size)
			dst[i + j] = '\0';
	}
	return (i + ft_strlen(src));
}
