/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_complement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:59:16 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:23:39 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../inc/ft_printf.h"

/*
** Print the remaining space after the output in case of '-' (left flag).
*/

int	ft_post_printing(int ret, t_format *format)
{
	if (format->flag_left == TRUE)
		while (ret < format->field_width)
			ret += write(g_fd, " ", 1);
	return (ret);
}

/*
** Print the right character before the output : ' ', '-' or '+'.
*/

int	ft_mod(t_format *format, char *buff, t_bool sign)
{
	int ret;

	ret = 0;
	if (sign == TRUE)
		ret += ft_buff(buff, '-', 0);
	else if (format->flag_sign == TRUE)
		ret += ft_buff(buff, '+', 0);
	else if (format->flag_space == TRUE)
		ret += ft_buff(buff, ' ', 0);
	return (ret);
}

/*
** Print '0's before the real output to reach the right precision.
** Used on iteger conversion.
*/

int	ft_endzero(t_format *format, int len, char *buff, int tmp)
{
	int ret;

	ret = 0;
	if (format->flag_prec == TRUE)
		while (len < tmp--)
			ret += ft_buff(buff, '0', 0);
	return (ret);
}

/*
** The function used pour print every characters. They are added to the buffer
** passed as argument. It is printed when full.
** The boolean argument allow to print and clear the buffer whenever we need.
*/

int	ft_buff(char *buff, char c, t_bool clear)
{
	static int i = 0;

	if (clear == TRUE)
	{
		write(g_fd, buff, i);
		i = 0;
		return (0);
	}
	else
	{
		buff[i++] = c;
		if (i == PFBUF)
		{
			write(g_fd, buff, i);
			i = 0;
		}
		return (1);
	}
}
