/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_uint64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:01:46 by tdelabro          #+#    #+#             */
/*   Updated: 2019/03/02 21:20:52 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

uint64_t		ft_pwd_uint64(uint64_t n, int pow)
{
	uint64_t	res;

	res = n;
	if (pow < 0 || n == 0)
		return (0);
	if (pow == 0)
		return (1);
	if (pow == 1)
		return (n);
	while (pow > 1)
	{
		res = res * n;
		pow--;
	}
	return (res);
}
