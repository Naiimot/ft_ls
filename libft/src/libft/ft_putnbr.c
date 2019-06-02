/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:00:55 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:02:12 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

void	ft_putnbr(int n)
{
	if (n >= 0 && n <= 9)
		ft_putchar(n + 48);
	else if (n < 0)
	{
		ft_putchar('-');
		if (n == INT_MIN)
		{
			ft_putchar('2');
			ft_putnbr(147483648);
		}
		else
			ft_putnbr(-1 * n);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
	}
}
