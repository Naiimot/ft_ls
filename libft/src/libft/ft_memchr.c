/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:07:48 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:18:03 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*cur;

	if (s && n)
	{
		cur = (void*)s;
		while (n--)
		{
			if (*(unsigned char*)cur == (unsigned char)c)
				return (cur);
			cur++;
		}
	}
	return (NULL);
}
