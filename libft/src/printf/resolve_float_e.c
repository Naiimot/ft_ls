/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_float_e.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:53:41 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:27:58 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../inc/ft_printf.h"

/*
** Those function handle the 'e' conversion, printing the number as one digit
** before coma float multiply by a power of ten. X.XXXXXe+XX
** Same algo as for 'f' conversion.
** Four versions : dbl/ldbl * sup or equal to one/inferior to one
*/

int			ft_getstr_supone_de(t_bint *valnum, t_bint *valdenum, int *tab, \
				t_format *format)
{
	int		ret;
	int		tmp;
	t_bool	pt;
	char	str[tab[1]];

	ret = 0;
	str[ret] = '0';
	pt = 0;
	while (str[ret] == '0' || (pt = 0))
	{
		str[ret] = ft_getnextdigit_dbl(valnum, valdenum);
		(str[ret] == '0') ? tab[0]-- : 1;
	}
	tmp = ft_pre_printing_float(format, tab[1], tab[2]);
	if ((format->precision != 0 || format->flag_hash == TRUE) && (pt = 1))
		str[++ret] = '.';
	while (++ret < FPRECI + 1 + (int)pt)
		str[ret] = ft_getnextdigit_dbl(valnum, valdenum);
	if (ft_round_e(str, ret, valnum, valdenum) == TRUE)
		ft_postround(&tab[0], &tmp, &ret);
	ft_expo(str, tab, &ret);
	write(g_fd, str, ret);
	ret = ft_post_printing(ret + tmp, format);
	return (ret);
}

int			ft_getstr_supone_lde(t_hint *valnum, t_hint *valdenum, int *tab, \
				t_format *format)
{
	int		ret;
	int		tmp;
	t_bool	pt;
	char	str[tab[1]];

	ret = 0;
	str[ret] = '0';
	pt = 0;
	while (str[ret] == '0' || (pt = 0))
	{
		str[ret] = ft_getnextdigit_ldbl(valnum, valdenum);
		(str[ret] == '0') ? tab[0]-- : 1;
	}
	tmp = ft_pre_printing_float(format, tab[1], tab[2]);
	if ((format->precision != 0 || format->flag_hash == TRUE) && (pt = 1))
		str[++ret] = '.';
	while (++ret < FPRECI + 1 + (int)pt)
		str[ret] = ft_getnextdigit_ldbl(valnum, valdenum);
	if (ft_round_ld_e(str, ret, valnum, valdenum) == TRUE)
		ft_postround(&tab[0], &tmp, &ret);
	ft_expo(str, tab, &ret);
	write(g_fd, str, ret);
	ret = ft_post_printing(ret + tmp, format);
	return (ret);
}

int			ft_getstr_minone_de(t_bint *valnum, t_bint *valdenum, int *tab, \
				t_format *format)
{
	int		ret;
	int		tmp;
	t_bool	pt;
	char	str[tab[1]];

	ret = 0;
	str[ret] = '0';
	pt = 0;
	while (str[ret] == '0' || (pt = 0))
		str[ret] = ft_getnextdigit_dbl(valnum, valdenum);
	tmp = ft_pre_printing_float(format, tab[1], tab[2]);
	if ((format->precision != 0 || format->flag_hash == TRUE) && (pt = 1))
		str[++ret] = '.';
	while (++ret < FPRECI + 1 + (int)pt)
		str[ret] = ft_getnextdigit_dbl(valnum, valdenum);
	if (ft_round_e(str, ret, valnum, valdenum) == TRUE)
		ft_postround(&tab[0], &tmp, &ret);
	ft_expo(str, tab, &ret);
	write(g_fd, str, ret);
	ret = ft_post_printing(ret + tmp, format);
	return (ret);
}

int			ft_getstr_minone_lde(t_hint *valnum, t_hint *valdenum, int *tab, \
				t_format *format)
{
	int		ret;
	int		tmp;
	t_bool	pt;
	char	str[tab[1]];

	ret = 0;
	str[ret] = '0';
	pt = 0;
	while (str[ret] == '0' || (pt = 0))
		str[ret] = ft_getnextdigit_ldbl(valnum, valdenum);
	tmp = ft_pre_printing_float(format, tab[1], tab[2]);
	if ((format->precision != 0 || format->flag_hash == TRUE) && (pt = 1))
		str[++ret] = '.';
	while (++ret < FPRECI + 1 + (int)pt)
		str[ret] = ft_getnextdigit_ldbl(valnum, valdenum);
	if (ft_round_ld_e(str, ret, valnum, valdenum) == TRUE)
		ft_postround(&tab[0], &tmp, &ret);
	ft_expo(str, tab, &ret);
	write(g_fd, str, ret);
	ret = ft_post_printing(ret + tmp, format);
	return (ret);
}
