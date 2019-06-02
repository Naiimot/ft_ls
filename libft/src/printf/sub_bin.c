/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:51:13 by tdelabro          #+#    #+#             */
/*   Updated: 2019/02/20 16:12:17 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

/*
** Print an integer as binary.
*/

static int	ft_get_len_bin(uintmax_t num, t_format *format)
{
	int	len;

	if (num == 0 && !(format->flag_prec == TRUE && format->precision == 0))
		return (1);
	len = 0;
	while ((num != 0) && (++len))
		num = num / 2;
	return (len);
}

static int	ft_getbin(uintmax_t n, char *buff, int len)
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
			rev[--tmp] = '0' + (n % 2);
			n = n / 2;
		}
		while (tmp < len)
			ret += ft_buff(buff, rev[tmp++], 0);
	}
	return (ret);
}

static int	ft_print_bin(t_format *format, int len, char *buff, uintmax_t num)
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
	ret += ft_getbin(num, buff, len);
	if (format->flag_left == TRUE)
		while (ret < format->field_width)
			ret += ft_buff(buff, ' ', 0);
	return (ret);
}

int			ft_sub_bin(t_format *format, va_list args, char *buff)
{
	uintmax_t	num;
	int			ret;
	int			len;

	num = ft_lenmod_u(format->len_mod, args);
	len = ft_get_len_bin(num, format);
	ret = ft_print_bin(format, len, buff, num);
	return (ret);
}
