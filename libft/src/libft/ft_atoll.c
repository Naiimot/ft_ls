/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 18:25:56 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 21:32:53 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	num = 0;
	sign = -1;
	if (str)
	{
		while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
			i++;
		if (str[i] == '-')
			sign = 1;
		if (str[i] == '+' || str[i] == '-')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			num = num * 10 - (str[i] - 48);
			i++;
		}
	}
	return (sign * num);
}
