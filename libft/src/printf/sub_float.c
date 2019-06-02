/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:37:19 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:27:36 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../inc/ft_printf.h"

/*
** Those two pairs of function (bdbl/ldbl) initialize the Dragon4 algorithm
** needed values and then inject them into the good printing function according
** to the conversion flag (e or f) and the value (value < -1 || value > 1).
*/

static int	ft_sndp_ldbl(t_hint *valnum, t_hint *valdenum, int *tab, \
				t_format *format)
{
	int ret;

	if (tab[3] == 1)
	{
		if (format->conversion == 'e')
			ret = ft_getstr_supone_lde(valnum, valdenum, tab, format);
		else
			ret = ft_getstr_supone_ld(valnum, valdenum, tab, format);
	}
	else
	{
		if (format->conversion == 'e')
			ret = ft_getstr_minone_lde(valnum, valdenum, tab, format);
		else
			ret = ft_getstr_minone_ld(valnum, valdenum, tab, format);
	}
	return (ret);
}

static int	ft_res_ldbl(long double n, t_format *format)
{
	t_hint	valnum;
	t_hint	valdenum;
	int		tab[4];

	tab[0] = ft_getfirstdigit_ldbl(n);
	ft_init_numdenum_ld(&valnum, &valdenum, n, tab[0]);
	tab[2] = (((unsigned char*)&n)[9] & 0x80) >> 7;
	tab[3] = (n >= 1 || n <= -1) ? 1 : 0;
	if (format->conversion == 'e')
		tab[1] = 4 + ((format->flag_prec == 1) ? format->precision : 6) \
			+ ((tab[0] < 100) ? 2 : ft_lenint_base(tab[0], 10));
	else if (n >= 1 || n <= -1)
		tab[1] = (format->flag_prec == 1 && FPRECI == 0) ?\
			1 + tab[0] : (2 + tab[0] + format->precision);
	else
		tab[1] = (format->precision == 0 && format->flag_hash == FALSE) ?\
			1 : (2 + format->precision);
	return (ft_sndp_ldbl(&valnum, &valdenum, tab, format));
}

static int	ft_sndp_dbl(t_bint *valnum, t_bint *valdenum, int *tab, \
				t_format *format)
{
	int ret;

	if (tab[3] == 1)
	{
		if (format->conversion == 'e')
			ret = ft_getstr_supone_de(valnum, valdenum, tab, format);
		else
			ret = ft_getstr_supone_d(valnum, valdenum, tab, format);
	}
	else
	{
		if (format->conversion == 'e')
			ret = ft_getstr_minone_de(valnum, valdenum, tab, format);
		else
			ret = ft_getstr_minone_d(valnum, valdenum, tab, format);
	}
	return (ret);
}

static int	ft_res_dbl(double n, t_format *format)
{
	t_bint	valnum;
	t_bint	valdenum;
	int		tab[4];

	tab[0] = ft_getfirstdigit_d((n < 0) ? -n : n);
	ft_init_numdenum_d(&valnum, &valdenum, n, tab[0]);
	tab[2] = (*(int64_t*)&n & 0x8000000000000000) >> 63;
	tab[3] = (n >= 1 || n <= -1) ? 1 : 0;
	if (format->conversion == 'e')
		tab[1] = 4 + ((format->flag_prec == 1) ? format->precision : 6) \
			+ ((tab[0] < 100) ? 2 : ft_lenint_base(tab[0], 10));
	else if (n >= 1 || n <= -1)
		tab[1] = (format->flag_prec == 1 && FPRECI == 0) ?\
			1 + tab[0] : (2 + tab[0] + format->precision);
	else
		tab[1] = (format->precision == 0 && format->flag_hash == FALSE) ?\
			1 : (2 + format->precision);
	return (ft_sndp_dbl(&valnum, &valdenum, tab, format));
}

/*
** This function extract the float argument from the va_list, parse it (for NAN,
** zero and infinity values) and inject it in the correct (dbl/ldbl) version of
** the Dragon4 algorithm.
*/

int			ft_sub_float(t_format *format, va_list args, char *buff)
{
	double		n;
	long double	m;
	int			ret;

	if (format->len_mod == L)
	{
		m = (long double)va_arg(args, long double);
		if (UCM[0] == 0 && UCM[1] == 0 && UCM[2] == 0 && UCM[3] == 0 \
			&& UCM[4] == 1 && UCM[5] == 0 && UCM[6] == 0 && UCM[7] == 0)
			ret = ft_parse_ldbl(NAN, format, buff);
		else
			ret = ft_parse_ldbl(m, format, buff);
	}
	else
	{
		n = (double)va_arg(args, double);
		ret = ft_parse_dbl(n, format, buff);
	}
	if (ret == 0)
		ft_buff(buff, 0, 1);
	if (ret == 0)
		ret = (format->len_mod == L) ? ft_res_ldbl(m, format) : \
			ft_res_dbl(n, format);
	return (ret);
}
