/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:50:53 by tdelabro          #+#    #+#             */
/*   Updated: 2019/03/02 21:50:11 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

int				get_next_line(const int fd, char **line);

typedef struct	s_fd
{
	char	*str;
	char	*remain;
	int		fd;
	int		ret;
}				t_fd;

#endif
