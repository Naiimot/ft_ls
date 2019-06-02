/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:55:42 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:34:02 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	if (dst && src && len)
	{
		pdst = (unsigned char*)dst;
		psrc = (unsigned char*)src;
		if (psrc < pdst)
		{
			pdst += len;
			psrc += len;
			while (len--)
				*--pdst = *--psrc;
		}
		else
			while (len--)
				*pdst++ = *psrc++;
	}
	return (dst);
}
