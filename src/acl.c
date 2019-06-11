#include "acl.h"

static void	ft_get_name(id_t id, int type, char	**to_print)
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


static void ft_print_perms(acl_entry_t entry, t_bool isdir,\
				char *specific[2][6], char **all)
{
	acl_permset_t	permset;
	int				i;
	t_bool			first;

	first = TRUE;
	i = 1;
	if (acl_get_permset(entry, &permset) != 0)
		return ;
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
	ft_printf("%c", '\n');
}

static void	ft_get_perms(acl_entry_t entry, t_bool isdir)
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
	ft_print_perms(entry, isdir, specific, all);
}

void print_bytes(void *ptr, int size) 
{
    unsigned char *p = ptr;
    int i;
    for (i=0; i<size; i++) {
        ft_printf("%02hhX ", p[i]);
    }
    ft_printf("\n");
}

static void	ft_print_entry(acl_entry_t entry, int i, t_bool isdir)
{
	acl_tag_t	tag;
	uuid_t		*uu;
	char		*to_print[4];
//	id_t		id;
//	int			id_type;
	
	uu = acl_get_qualifier(entry);
	print_bytes(entry, sizeof(entry));
/*	if (ft_uuid_to_id(*uu, &id, &id_type) == 0)
		ft_get_name(id, id_type, to_print);
	else
	{
		to_print[0] = "???";
		to_print[1] = "unknown";
	}*/
	acl_free(uu);
	acl_get_tag_type(entry, &tag);
	if (tag == ACL_EXTENDED_ALLOW)
		to_print[2] = "allow";
	else if (tag == ACL_EXTENDED_DENY)
		to_print[2] = "deny";
	ft_printf(" %d: %s:%s %s ", i, to_print[0], to_print[1], to_print[2]);
	ft_get_perms(entry, isdir);
}

void		ft_pacl(acl_t acl, t_bool isdir)
{
	acl_entry_t entry;
	int			i;
	
	i = 0;
	char	*txt = acl_to_text(acl, NULL);
	ft_printf("%s", txt);
	acl_free(txt);
/*
	if (acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) != -1)
		ft_print_entry(entry, i++, isdir);
	while (acl_get_entry(acl, ACL_NEXT_ENTRY, &entry) != -1)
		ft_print_entry(entry, i++, isdir);
		*/
}
