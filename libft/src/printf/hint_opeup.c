/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hint_opeup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 19:58:05 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/15 16:22:05 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

uint64_t	ft_pwd_uint64(uint64_t n, int pow)
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

/*
** Store in 'result' the result of 'n + m'
*/

void		ft_add_hint(t_hint *result, const t_hint *n, const t_hint *m)
{
	t_hint	carry;
	t_hint	shifted;
	short	i;

	i = -1;
	while (++i < 258)
	{
		carry[i] = (*n)[i] & (*m)[i];
		(*result)[i] = (*n)[i] ^ (*m)[i];
	}
	while (ft_hint_difzero(&carry))
	{
		ft_hintcpy(&shifted, &carry);
		ft_hint_lshift(&shifted, 1);
		i = -1;
		while (++i < 258)
		{
			carry[i] = (*result)[i] & shifted[i];
			(*result)[i] ^= shifted[i];
		}
	}
}

/*
** Store in 'result' the result of 'n * m'
*/

static void	ft_mult_hint(t_hint *result, t_hint *n, t_hint *m)
{
	t_hint	tmp;

	ft_hint_settozero(&tmp);
	while (ft_hint_difzero(m))
	{
		if ((*m)[257] & 0x1)
			ft_add_hint(&tmp, &tmp, n);
		ft_hint_lshift(n, 1);
		ft_hint_rshift(m, 1);
	}
	ft_hintcpy(result, &tmp);
}

/*
** Store in 'result' the result of the multiplication of 'n' by an integer
*/

void		ft_mult_hinti(t_hint *result, const t_hint *n, int m)
{
	t_hint	tmp;

	ft_hint_settozero(&tmp);
	while (m-- > 0)
	{
		ft_add_hint(&tmp, &tmp, n);
	}
	ft_hintcpy(result, &tmp);
}

/*
** Store in 'result' the result 'result * n^pow'
*/

void		ft_pwd_hint(t_hint *result, int n, int pow)
{
	t_hint	tmp;
	t_hint	temp;

	if (pow == 0)
		return ;
	ft_hint_settozero(&tmp);
	tmp[257] = n;
	while (pow-- > 1)
	{
		ft_hint_settozero(&temp);
		temp[257] = n;
		ft_mult_hint(&tmp, &tmp, &temp);
	}
	ft_mult_hint(result, result, &tmp);
}
