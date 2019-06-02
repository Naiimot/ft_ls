/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:39:34 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:15:57 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void	*cur_d;
	void	*cur_s;

	if (dst && src && n)
	{
		cur_d = (void*)dst;
		cur_s = (void*)src;
		while (n--)
		{
			*(unsigned char*)cur_d++ = *(unsigned char*)cur_s;
			if (*(unsigned char*)cur_s == (unsigned char)c)
				return (cur_d);
			cur_s++;
		}
	}
	return (NULL);
}
