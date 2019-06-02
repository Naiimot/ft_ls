/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_opeup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:37:59 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/20 15:17:59 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Store in 'result' the result of 'n + m'
*/

void		ft_add_bint(t_bint *result, const t_bint *n, const t_bint *m)
{
	t_bint			carry;
	t_bint			shifted;
	unsigned char	i;

	i = 0;
	while (i < 17)
	{
		carry[i] = (*n)[i] & (*m)[i];
		(*result)[i] = (*n)[i] ^ (*m)[i];
		i++;
	}
	while (ft_bint_difzero(&carry))
	{
		ft_bintcpy(&shifted, &carry);
		ft_lshift(&shifted, 1);
		i = 0;
		while (i < 17)
		{
			carry[i] = (*result)[i] & shifted[i];
			(*result)[i] ^= shifted[i];
			i++;
		}
	}
}

/*
** Store in 'result' the result of 'n * m'
*/

static void	ft_mult_bint(t_bint *result, t_bint *n, t_bint *m)
{
	t_bint	tmp;

	ft_bint_settozero(&tmp);
	while (ft_bint_difzero(m))
	{
		if (((*m)[16]) & 0x1)
			ft_add_bint(&tmp, &tmp, n);
		ft_lshift(n, 1);
		ft_rshift(m, 1);
	}
	ft_bintcpy(result, &tmp);
}

/*
** Store in 'result' the result of the multiplication of 'n' by an integer
*/

void		ft_mult_binti(t_bint *result, const t_bint *n, int m)
{
	t_bint	tmp;

	ft_bint_settozero(&tmp);
	while (m-- > 0)
	{
		ft_add_bint(&tmp, &tmp, n);
	}
	ft_bintcpy(result, &tmp);
}

/*
** Store in 'result' the result 'result * n^pow'
*/

void		ft_pwd_bint(t_bint *result, int n, int pow)
{
	t_bint	tmp;
	t_bint	temp;

	if (pow == 0)
		return ;
	ft_bint_settozero(&tmp);
	tmp[16] = n;
	while (pow-- > 1)
	{
		ft_bint_settozero(&temp);
		temp[16] = n;
		ft_mult_bint(&tmp, &tmp, &temp);
	}
	ft_mult_bint(result, result, &tmp);
}
