/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xattr_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:09:05 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/15 16:10:02 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xattr_acl.h"

void		ft_pacl(acl_t acl, t_bool isdir)
{
	acl_entry_t entry;
	int			i;

	i = 0;
	if (acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) != -1)
		ft_print_entry(entry, i++, isdir);
	while (acl_get_entry(acl, ACL_NEXT_ENTRY, &entry) != -1)
		ft_print_entry(entry, i++, isdir);
}

static void	ft_pxattr(const char *path, char *buff, ssize_t size)
{
	ssize_t i;
	ssize_t last;

	i = 0;
	while (i < size)
	{
		last = i;
		i += ft_printf("	%s", &buff[i]) - 1;
		ft_printf("\t%2jd\n", getxattr(path, &buff[last], NULL, 0, 0,\
			XATTR_NOFOLLOW));
		i++;
	}
}

void		ft_print_xattr_acl(const char *path, t_xattr_acl *storage,\
				unsigned int options, t_bool isdir)
{
	char	buff[storage->sxattr];

	if ((options & OPT_XATTR) == OPT_XATTR && storage->sxattr > 0)
	{
		if (storage->sxattr == listxattr(path, buff, storage->sxattr,\
			XATTR_NOFOLLOW))
			ft_pxattr(path, buff, storage->sxattr);
	}
	if ((options & OPT_ACL) == OPT_ACL && storage->acl != NULL)
		ft_pacl(storage->acl, isdir);
	acl_free(storage->acl);
}
