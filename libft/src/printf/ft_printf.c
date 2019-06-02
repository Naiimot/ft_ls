/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:22:00 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:26:08 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../inc/ft_printf.h"

int g_fd = 1;

/*
** The two substitutes functions are in reality the same.
** It match the conversion character with the corresponding function.
*/

static int	ft_sub_two(t_format *format, va_list args, char *buff)
{
	int	(*pf[7])(t_format *format, va_list args, char *buff);
	int	ret;

	pf[0] = ft_sub_dec;
	pf[1] = ft_sub_uoctal;
	pf[2] = ft_sub_udec;
	pf[3] = ft_sub_uhex;
	pf[4] = ft_sub_float;
	pf[5] = ft_sub_bin;
	pf[6] = ft_sub_unknown;
	if (format->conversion == 'i' || format->conversion == 'd')
		ret = (pf[0])(format, args, buff);
	else if (format->conversion == 'o')
		ret = (pf[1])(format, args, buff);
	else if (format->conversion == 'u')
		ret = (pf[2])(format, args, buff);
	else if (format->conversion == 'x' || format->conversion == 'X')
		ret = (pf[3])(format, args, buff);
	else if (format->conversion == 'f' || format->conversion == 'e')
		ret = (pf[4])(format, args, buff);
	else if (format->conversion == 'b')
		ret = (pf[5])(format, args, buff);
	else
		ret = (pf[6])(format, args, buff);
	return (ret);
}

static int	ft_substitute(t_format *format, va_list args, char *buff)
{
	int	(*pf[4])(t_format *format, va_list args, char *buff);
	int	ret;

	pf[0] = ft_sub_char;
	pf[1] = ft_sub_string;
	pf[2] = ft_sub_address;
	pf[3] = ft_sub_percent;
	if (format->conversion == 'c')
		ret = (pf[0])(format, args, buff);
	else if (format->conversion == 's')
		ret = (pf[1])(format, args, buff);
	else if (format->conversion == 'p')
		ret = (pf[2])(format, args, buff);
	else if (format->conversion == '%')
		ret = (pf[3])(format, args, buff);
	else
		ret = ft_sub_two(format, args, buff);
	return (ret);
}

/*
** We store each segment of the original string in a spetial structure.
** If the segment contain a '%', a conversion must be done so we store all the
** informations (flags, width, precision, size, type) we have on the
** appropriate structure's variable.
*/

static int	ft_dispatch(const char *str, va_list args, char *buff)
{
	int			ret[3];
	size_t		s;
	t_format	*tmp;

	ret[0] = 0;
	ret[1] = 1;
	ret[2] = 0;
	while (str[ret[2]] && ((ret[0] < 0) ? ret[1] = -1 : 1))
	{
		s = ft_size_word(&str[ret[2]]);
		tmp = ft_iniformat(&str[ret[2]], s, args);
		if ((ret[2] += s) && tmp->conversion == '\0')
		{
			ft_buff(buff, '0', 1);
			ret[0] += write(g_fd, tmp->buffer, tmp->buf_size - 1);
		}
		else
			ret[0] += ft_substitute(tmp, args, buff);
		ft_memdel((void**)&(tmp->buffer));
		ft_memdel((void**)&tmp);
		if (str[ret[2] - 1] == '\0')
			break ;
	}
	ft_buff(buff, 0, 1);
	return ((ret[1] == 1) ? ret[0] : ret[1]);
}

/*
** We store the converted string to be printed in a stack buffer.
** This buffer is printed in the stdout when it's full and at the end of the
** function. This way we never keep in memory more than PFBUFF characters.
**
** If the converted strig is larger than INT_MAX we return 1.
*/

int			ft_printf(const char *format, ...)
{
	va_list		args;
	int			ret;
	char		buff[PFBUF];

	va_start(args, format);
	ret = ft_dispatch(format, args, buff);
	va_end(args);
	return (ret);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	va_list		args;
	int			ret;
	char		buff[PFBUF];

	g_fd = fd;
	va_start(args, format);
	ret = ft_dispatch(format, args, buff);
	va_end(args);
	return (ret);
}
