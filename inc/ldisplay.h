/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldisplay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:13:46 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/15 16:14:02 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LDISPLAY_H
# define LDISPLAY_H

# include "ft_ls.h"
# include "ft_printf.h"
# include "xattr_acl.h"
# include "colors.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>

void		ft_print_xattr_acl(const char *path, t_xattr_acl *storage,\
				unsigned int options, t_bool isdir);

#endif
