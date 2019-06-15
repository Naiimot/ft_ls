/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xattr_acl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:15:09 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/15 16:15:53 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XATTR_ACL_H
# define XATTR_ACL_H

# include "ft_ls.h"
# include "ft_printf.h"
# include <sys/xattr.h>
# include <sys/acl.h>

typedef struct	s_xattr_acl
{
	acl_t	acl;
	ssize_t	sxattr;
}				t_xattr_acl;

void			ft_print_entry(acl_entry_t entry, int i, t_bool isdir);

#endif
