/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:01:55 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/15 16:07:11 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "acl.h"

static void		ft_get_name(id_t id, int type, char **to_print)
{
	struct passwd	*pwd;
	struct group	*grp;

	if (type == ID_TYPE_UID)
	{
		to_print[0] = "user";
		pwd = getpwuid(id);
		if (pwd != NULL)
			to_print[1] = pwd->pw_name;
	}
	else if (type == ID_TYPE_GID)
	{
		to_print[0] = "group";
		grp = getgrgid(id);
		if (grp != NULL)
			to_print[1] = grp->gr_name;
	}
	else
	{
		to_print[0] = "???";
		to_print[1] = "unknow";
	}
}

static t_bool	ft_print_perms(acl_entry_t entry, t_bool isdir,\
					char *specific[2][6], char **all)
{
	acl_permset_t	permset;
	int				i;
	t_bool			first;

	first = TRUE;
	i = 1;
	if (acl_get_permset(entry, &permset) != 0)
		return (first);
	while (i < 14)
	{
		if (acl_get_perm_np(permset, 1 << i) == 1)
		{
			if (first == TRUE)
				first = FALSE;
			else
				ft_printf("%c", ',');
			if (i < 7)
				ft_printf("%s", (isdir == 1) ?\
					specific[0][i - 1] : specific[1][i - 1]);
			else
				ft_printf("%s", all[i - 7]);
		}
		i++;
	}
	return (first);
}

static void		ft_print_inheritance(acl_entry_t entry, t_bool first)
{
	acl_flagset_t	flagset;
	int				i;

	if (acl_get_flagset_np(entry, &flagset) == 0)
	{
		i = 4;
		while (++i < 9)
		{
			if (acl_get_flag_np(flagset, 1 << i))
			{
				if (first == TRUE)
					first = FALSE;
				else
					ft_printf("%c", ',');
				if (i == 5)
					ft_printf("%s", "file_inherit");
				else if (i == 6)
					ft_printf("%s", "directory_inherit");
				else if (i == 7)
					ft_printf("%s", "limit_inherit");
				else if (i == 8)
					ft_printf("%s", "only_inherit");
			}
		}
	}
}

static void		ft_get_perms(acl_entry_t entry, t_bool isdir)
{
	char	*specific[2][6];
	char	*all[7];

	specific[0][0] = "list";
	specific[0][1] = "add_file";
	specific[0][2] = "search";
	specific[0][3] = "delete";
	specific[0][4] = "add_subdirectory";
	specific[0][5] = "delete_child";
	specific[1][0] = "read";
	specific[1][1] = "write";
	specific[1][2] = "execute";
	specific[1][3] = "delete";
	specific[1][4] = "append";
	all[0] = "readattr";
	all[1] = "writeattr";
	all[2] = "readexattr";
	all[3] = "writeexattr";
	all[4] = "readsecurity";
	all[5] = "writesecurity";
	all[6] = "chown";
	ft_print_inheritance(entry, ft_print_perms(entry, isdir, specific, all));
	ft_printf("\n");
}

void			ft_print_entry(acl_entry_t entry, int i, t_bool isdir)
{
	acl_tag_t	tag;
	uuid_t		*uu;
	char		*to_print[4];
	id_t		id;
	int			id_type;

	uu = acl_get_qualifier(entry);
	mbr_uuid_to_id(*uu, &id, &id_type);
	ft_get_name(id, id_type, to_print);
	acl_free(uu);
	acl_get_tag_type(entry, &tag);
	if (tag == ACL_EXTENDED_ALLOW)
		to_print[2] = "allow";
	else if (tag == ACL_EXTENDED_DENY)
		to_print[2] = "deny";
	ft_printf(" %d: %s:%s %s ", i, to_print[0], to_print[1], to_print[2]);
	ft_get_perms(entry, isdir);
}
