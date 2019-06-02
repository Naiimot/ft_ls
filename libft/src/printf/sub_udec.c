/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_udec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 23:36:12 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/20 16:22:14 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Function to print unsigned integer in base ten.
*/

static int	ft_get_len_udec(uintmax_t num, t_format *format)
{
	int	len;

	if (num == 0 && !(format->flag_prec == TRUE && format->precision == 0))
		return (1);
	len = 0;
	while ((num != 0) && (++len))
		num = num / 10;
	return (len);
}

static int	ft_getudec(uintmax_t n, char *buff, int len)
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
			rev[--tmp] = '0' + (n % 10);
			n = n / 10;
		}
		while (tmp < len)
			ret += ft_buff(buff, rev[tmp++], 0);
	}
	return (ret);
}

static int	ft_print_udec(t_format *format, int len, char *buff, uintmax_t num)
{
	int				ret;
	int				tmp;

	ret = 0;
	FFZERO = (FFZERO == 1 && FFLEFT == 0 && format->flag_prec == 0) ? 1 : 0;
	tmp = (format->flag_prec == TRUE && FPRECI > len) ? FPRECI : len;
	if (format->flag_zero == TRUE || format->flag_left == TRUE)
		while (format->flag_zero == TRUE && ret < format->field_width - tmp)
			ret += ft_buff(buff, '0', 0);
	else
		while (format->field_width > tmp && ret < format->field_width - tmp)
			ret += ft_buff(buff, ' ', 0);
	while (format->flag_prec == TRUE && len < tmp--)
		ret += ft_buff(buff, '0', 0);
	if (num == 0 && format->flag_prec == TRUE && format->precision == 0)
		return (ret);
	ret += ft_getudec(num, buff, len);
	if (format->flag_left == TRUE)
		while (ret < format->field_width)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}

uintmax_t	ft_lenmod_u(t_len_mod tlen, va_list args)
{
	uintmax_t	n;

	if (tlen == hh)
		n = (unsigned char)va_arg(args, int);
	else if (tlen == h)
		n = (unsigned short)va_arg(args, int);
	else if (tlen == l)
		n = (unsigned long)va_arg(args, long);
	else if (tlen == ll)
		n = (unsigned long long)va_arg(args, long long);
	else if (tlen == j)
		n = (uintmax_t)va_arg(args, long long);
	else if (tlen == z)
		n = (size_t)va_arg(args, size_t);
	else
		n = (unsigned int)va_arg(args, int);
	return (n);
}

int			ft_sub_udec(t_format *format, va_list args, char *buff)
{
	uintmax_t	num;
	int			ret;
	int			len;

	num = ft_lenmod_u(format->len_mod, args);
	len = ft_get_len_udec(num, format);
	ret = ft_print_udec(format, len, buff, num);
	return (ret);
}
