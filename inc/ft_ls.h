/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:55:11 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/15 16:14:37 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# define OPT_REC		1 << 0
# define OPT_ALL		1 << 1
# define OPT_LONG		1 << 2
# define OPT_NOSORT		1 << 3
# define OPT_REV		1 << 4
# define OPT_MTIME		1 << 5
# define OPT_ATIME		1 << 6
# define OPT_CTIME		1 << 7
# define OPT_XATTR		1 << 8
# define OPT_ACL		1 << 9
# define OPT_COLOR		1 << 10
# define OPT_ONLYGRP	1 << 11
# define OPT_NORECDIR	1 << 12
# define OPT_SIZESORT	1 << 13

typedef struct	s_dir
{
	char			*name;
	char			*full;
	struct stat		*fstat;
	struct passwd	*owner;
	struct group	*group;
}				t_dir;

#endif
