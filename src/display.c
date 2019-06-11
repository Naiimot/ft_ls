/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:30:05 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/02 23:16:15 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static void	ft_get_type(struct stat *fstat, char *perms)
{
	if (S_ISREG(fstat->st_mode))
		perms[0] ='-';
	else if (S_ISDIR(fstat->st_mode))
		perms[0] ='d';
	else if (S_ISCHR(fstat->st_mode))
		perms[0] ='c';
	else if (S_ISBLK(fstat->st_mode))
		perms[0] ='b';
	else if (S_ISLNK(fstat->st_mode))
		perms[0] ='l';
	else if (S_ISFIFO(fstat->st_mode))
		perms[0] ='p';
	else if (S_ISSOCK(fstat->st_mode))
		perms[0] ='s';
}

static void	ft_get_perms(struct stat *fstat, char *perms)
{
	ft_get_type(fstat, perms);
	perms[1] = (fstat->st_mode & S_IRUSR) ? 'r' : '-';
	perms[2] = (fstat->st_mode & S_IWUSR) ? 'w' : '-';
	if (fstat->st_mode & S_ISUID)
		perms[3] = (fstat->st_mode & S_IXUSR) ? 's' : 'S';
	else
		perms[3] = (fstat->st_mode & S_IXUSR) ? 'x' : '-';
	perms[4] = (fstat->st_mode & S_IRGRP) ? 'r' : '-';
	perms[5] = (fstat->st_mode & S_IWGRP) ? 'w' : '-';
	if (fstat->st_mode & S_ISGID)
		perms[6] = (fstat->st_mode & S_IXGRP) ? 's' : 'S';
	else
		perms[6] = (fstat->st_mode & S_IXGRP) ? 'x' : '-';
	perms[7] = (fstat->st_mode & S_IROTH) ? 'r' : '-';
	perms[8] = (fstat->st_mode & S_IWOTH) ? 'w' : '-';
	if (fstat->st_mode & S_ISVTX)
		perms[9] = (fstat->st_mode & S_IXOTH) ? 't' : 'T';
	else
		perms[9] = (fstat->st_mode & S_IXOTH) ? 'x' : '-';
	perms[10] = '\0';
}

static void	ft_len_fields(t_dir *dir, int *field_sizes, struct passwd *owner,\
				struct group *group)
{
	int	tmp;

	owner = getpwuid(dir->fstat->st_uid);
	group = getgrgid(dir->fstat->st_gid);
	field_sizes[4] += dir->fstat->st_blocks;
	if ((tmp = ft_lenint_base(dir->fstat->st_nlink, 10)) > field_sizes[0])
		field_sizes[0] = tmp;
	if ((tmp = ft_strlen(owner->pw_name)) > field_sizes[1])
		field_sizes[1] = tmp;
	if ((tmp = ft_strlen(group->gr_name)) > field_sizes[2])
		field_sizes[2] = tmp;
	if ((tmp = ft_lenint_base(dir->fstat->st_size, 10))\
		> field_sizes[3])
		field_sizes[3] = tmp;
}

static void	ft_get_field_sizes(t_list *lst, int *field_sizes)
{
	t_list			*h;
	struct passwd	*owner;
	struct group	*group;

	h = lst;
	ft_bzero(field_sizes, sizeof(int) * 5);
	owner = NULL;
	group = NULL;
	while (h)
	{
		ft_len_fields(h->content, field_sizes, owner, group);
		h = h->next;
	}
}

void		ft_display(t_list *lst, unsigned int options, t_bool dirs)
{
	t_list	*head;
	int		field_sizes[5];
	char	perms[11];

	ft_get_field_sizes(lst, field_sizes);
	if ((options & 4) == 4 && dirs == TRUE)
		ft_printf("total %d\n", field_sizes[4]);
	head = lst;
	while (head)
	{
		ft_get_perms(((t_dir*)head->content)->fstat, perms);
		if ((options & 2) == 2 || ((t_dir*)head->content)->name[0] != '.')
		{
			if ((options & 4) == 4)
				ft_ldisplay(head->content, field_sizes, perms,  options);
			else
				ft_printf("%s%s%s\n", ft_colorize(perms, options),\
					((t_dir*)head->content)->name, C_EOC);
		}
		ft_del_tdir(head->content);
		head = head->next;
	}
	ft_lstclear(&lst);
}
