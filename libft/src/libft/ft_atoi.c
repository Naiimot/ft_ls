/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:48:23 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 21:32:30 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int i;
	int sign;
	int num;

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
