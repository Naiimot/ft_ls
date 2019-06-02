/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:32:44 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:19:17 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	if (dst && src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char*)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}
