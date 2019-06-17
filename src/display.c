/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:30:05 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/17 20:24:49 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static void	ft_get_type(struct stat *fstat, char *perms)
{
	if (S_ISREG(fstat->st_mode))
		perms[0] = '-';
	else if (S_ISDIR(fstat->st_mode))
		perms[0] = 'd';
	else if (S_ISCHR(fstat->st_mode))
		perms[0] = 'c';
	else if (S_ISBLK(fstat->st_mode))
		perms[0] = 'b';
	else if (S_ISLNK(fstat->st_mode))
		perms[0] = 'l';
	else if (S_ISFIFO(fstat->st_mode))
		perms[0] = 'p';
	else if (S_ISSOCK(fstat->st_mode))
		perms[0] = 's';
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

static void	ft_get_field_sizes_2(struct stat *fstat, int *field_sizes,\
				unsigned int options)
{
	struct passwd	*owner;
	struct group	*group;
	int				tmp;

	owner = getpwuid(fstat->st_uid);
	group = getgrgid(fstat->st_gid);
	if ((tmp = ft_lenint_base(fstat->st_nlink, 10)) > field_sizes[0])
		field_sizes[0] = tmp;
	if (!(options & OPT_ONLYGRP))
	{
		if (!(owner))
		{
			if ((tmp = ft_lenint_base(fstat->st_uid, 10)) > field_sizes[1])
				field_sizes[1] = tmp;
		}
		else if ((tmp = ft_strlen(owner->pw_name)) > field_sizes[1])
			field_sizes[1] = tmp;
	}
	if (!(group) && (tmp = ft_lenint_base(fstat->st_gid, 10)) > field_sizes[2])
		field_sizes[2] = tmp;
	else if ((tmp = ft_strlen(group->gr_name)) > field_sizes[2])
		field_sizes[2] = tmp;
	if ((tmp = ft_lenint_base(fstat->st_size, 10)) > field_sizes[3])
		field_sizes[3] = tmp;
}

static void	ft_get_field_sizes(t_list *lst, int *field_sizes,\
				unsigned int options, t_bool dirs)
{
	t_list	*h;

	h = lst;
	ft_bzero(field_sizes, sizeof(int) * 5);
	while (h)
	{
		if (((t_dir*)h->content)->fstat)
		{
			field_sizes[4] += ((t_dir*)h->content)->fstat->st_blocks;
			if (options & OPT_LONG)
				ft_get_field_sizes_2(((t_dir*)h->content)->fstat, field_sizes,\
					options);
		}
		h = h->next;
	}
	field_sizes[0] += 1;
	if (!(options & OPT_ONLYGRP))
		field_sizes[1] += 2;
	field_sizes[2] += 2;
	if ((options & OPT_LONG) && dirs == TRUE)
		ft_printf("total %d\n", field_sizes[4]);
}

t_bool		ft_display(t_list *lst, unsigned int options, t_bool dirs)
{
	t_list	*head;
	int		field_sizes[5];
	char	perms[11];
	t_bool	printed;

	printed = FALSE;
	ft_get_field_sizes(lst, field_sizes, options, dirs);
	head = lst;
	while (head)
	{
		if (((t_dir*)head->content)->fstat && (printed = TRUE))
		{
			ft_get_perms(((t_dir*)head->content)->fstat, perms);
			if ((options & OPT_ALL) || ((t_dir*)head->content)->name[0] != '.')
			{
				(options & OPT_LONG) ? ft_ldisplay(head->content, field_sizes,\
					perms, options) : ft_printf("%s%s%s\n", ft_colorize(perms,\
					options), ((t_dir*)head->content)->name, C_EOC);
			}
			ft_del_tdir(head->content);
		}
		head = head->next;
	}
	ft_lstclear(&lst);
	return (printed);
}
