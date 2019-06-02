/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_dec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:25:38 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/20 16:13:02 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Print an integer in base 10.
*/

static int		ft_get_len_dec(intmax_t num, t_format *format)
{
	int			len;

	if (num == 0 && !(format->flag_prec == TRUE && format->precision == 0))
		return (1);
	len = 0;
	while ((num != 0) && (++len))
		num = num / 10;
	return (len);
}

static int		ft_getdec(intmax_t n, char *buff, int len)
{
	int		ret;
	int		tmp;
	char	rev[len];

	ret = 0;
	if (n == 0)
		ret += ft_buff(buff, '0', 0);
	else
	{
		tmp = len;
		while (n != 0)
		{
			rev[--tmp] = (n < 0) ? '0' - (n % 10) : '0' + (n % 10);
			n = n / 10;
		}
		while (tmp < len)
			ret += ft_buff(buff, rev[tmp++], 0);
	}
	return (ret);
}

static int		ft_print_dec(t_format *format, int len, char *buff,\
															intmax_t num)
{
	int	ret;

	ret = 0;
	ret += ft_pre_printing_dec(format, len, buff, (num < 0) ? 1 : 0);
	if (num == 0 && format->flag_prec == TRUE && format->precision == 0)
		return (ret);
	ret += ft_getdec(num, buff, len);
	if (format->flag_left == TRUE)
		while (ret < format->field_width)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}

static intmax_t	ft_lenmod(t_len_mod tlen, va_list args)
{
	intmax_t	n;

	if (tlen == hh)
		n = (signed char)va_arg(args, int);
	else if (tlen == h)
		n = (short)va_arg(args, int);
	else if (tlen == l)
		n = (long)va_arg(args, long);
	else if (tlen == ll)
		n = (long long)va_arg(args, long long);
	else if (tlen == j)
		n = (intmax_t)va_arg(args, long long);
	else if (tlen == z)
		n = (size_t)va_arg(args, size_t);
	else
		n = (int)va_arg(args, int);
	return (n);
}

int				ft_sub_dec(t_format *format, va_list args, char *buff)
{
	intmax_t	num;
	int			ret;
	int			len;

	num = ft_lenmod(format->len_mod, args);
	len = ft_get_len_dec(num, format);
	ret = ft_print_dec(format, len, buff, num);
	return (ret);
}
