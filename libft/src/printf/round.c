/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:59:02 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:23:24 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../inc/ft_printf.h"

/*
** Four function that vary around the same intent. Roudind the floats.
** We round according to precision.
** If the next digit is '5' and nothing after, we round to the nearest even.
*/

t_bool	ft_round_e(char *num, int len, t_bint *valnum, t_bint *valdenum)
{
	int		tmp;

	tmp = ft_div_bint(valnum, valnum, valdenum);
	ft_mult_binti(valnum, valnum, 10);
	if (tmp == 5 && !(tmp = 0))
	{
		while (ft_bint_difzero(valnum) == TRUE && tmp == 0)
		{
			tmp = ft_div_bint(valnum, valnum, valdenum);
			ft_mult_binti(valnum, valnum, 10);
		}
		tmp = (tmp == 0 && num[len - 1] % 2 == 0) ? 0 : 6;
	}
	if (tmp > 5)
	{
		while (--len >= 0 && (num[len] == '9' || num[len] == '.'))
			num[len] = (num[len] == '.') ? '.' : '0';
		(num[0] == '0') ? num[1] = '0' : 1;
		(num[0] == '0') ? num[0] = '.' : 1;
		if (len != -1)
			num[len] += 1;
		else
			return (write(g_fd, "1", 1));
	}
	return (0);
}

t_bool	ft_round_ld_e(char *num, int len, t_hint *valnum, t_hint *valdenum)
{
	int		tmp;

	tmp = ft_div_hint(valnum, valnum, valdenum);
	ft_mult_hinti(valnum, valnum, 10);
	if (tmp == 5 && !(tmp = 0))
	{
		while (ft_hint_difzero(valnum) == TRUE && tmp == 0)
		{
			tmp = ft_div_hint(valnum, valnum, valdenum);
			ft_mult_hinti(valnum, valnum, 10);
		}
		tmp = (tmp == 0 && num[len - 1] % 2 == 0) ? 0 : 6;
	}
	if (tmp > 5)
	{
		while (--len >= 0 && (num[len] == '9' || num[len] == '.'))
			num[len] = (num[len] == '.') ? '.' : '0';
		(num[0] == '0') ? num[1] = '0' : 1;
		(num[0] == '0') ? num[0] = '.' : 1;
		if (len != -1)
			num[len] += 1;
		else
			return (write(g_fd, "1", 1));
	}
	return (0);
}

t_bool	ft_round(char *num, int len, t_bint *valnum, t_bint *valdenum)
{
	int		tmp;

	tmp = ft_div_bint(valnum, valnum, valdenum);
	ft_mult_binti(valnum, valnum, 10);
	if (tmp == 5 && !(tmp = 0))
	{
		while (ft_bint_difzero(valnum) == TRUE && tmp == 0)
		{
			tmp = ft_div_bint(valnum, valnum, valdenum);
			ft_mult_binti(valnum, valnum, 10);
		}
		tmp = (tmp == 0 && num[len - 1] % 2 == 0) ? 0 : 6;
	}
	if (tmp > 5)
	{
		while (--len >= 0 && (num[len] == '9' || num[len] == '.'))
			num[len] = (num[len] == '.') ? '.' : '0';
		if (len != -1)
			num[len] += 1;
		else
			return (write(g_fd, "1", 1));
	}
	return (0);
}

t_bool	ft_round_ld(char *num, int len, t_hint *valnum, t_hint *valdenum)
{
	int		tmp;

	tmp = ft_div_hint(valnum, valnum, valdenum);
	ft_mult_hinti(valnum, valnum, 10);
	if (tmp == 5 && !(tmp = 0))
	{
		while (valnum && tmp == 0)
		{
			tmp = ft_div_hint(valnum, valnum, valdenum);
			ft_mult_hinti(valnum, valnum, 10);
		}
		tmp = (tmp == 0 && num[len - 1] % 2 == 0) ? 0 : 6;
	}
	if (tmp > 5)
	{
		while (--len >= 0 && (num[len] == '9' || num[len] == '.'))
			num[len] = (num[len] == '.') ? '.' : '0';
		if (len != -1)
			num[len] += 1;
		else
			return (write(g_fd, "1", 1));
	}
	return (0);
}
