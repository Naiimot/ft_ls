/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:15:22 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:15:00 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	int *mem;

	if ((mem = (int*)malloc(size)) == NULL)
		return (NULL);
	ft_bzero(mem, size);
	return ((void*)mem);
}
