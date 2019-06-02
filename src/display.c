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

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

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

static void	ft_ldisplay(t_dir *dir, int *max_len)
{
	struct stat		fstat;
	char			perms[11];
	struct passwd	*owner;
	struct group	*owner_group;
	char			*mtime;

	stat(dir->full, &fstat);
	ft_get_perms(&fstat, perms);
	owner = getpwuid(fstat.st_uid);
	owner_group = getgrgid(fstat.st_gid);
	mtime = ctime(&fstat.st_mtime);
	mtime[16] = '\0';
	ft_printf("%s  %*d %-*s  %-*s  %*d %s %s\n",\
		perms, max_len[0], fstat.st_nlink, max_len[1], owner->pw_name,\
		max_len[2], owner_group->gr_name, max_len[3], fstat.st_size,\
		mtime + 4, dir->name);
}

void		ft_get_mandatories(t_list *lst, int *total, int *max_len)
{
	t_list			*head;
	struct stat		fstat;
	int				tmp;
	struct passwd	*owner;
	struct group	*owner_group;

	head = lst;
	*total = 0;
	ft_bzero(max_len, sizeof(int) * 4);
	while (head)
	{
		if (stat(((t_dir*)head->content)->full, &fstat) == -1)
			ft_dprintf(2, "ls: %s: %s\n", ((t_dir*)head->content)->full, strerror(errno));
		owner = getpwuid(fstat.st_uid);
		owner_group = getgrgid(fstat.st_gid);
		*total += fstat.st_blocks;
		if ((tmp = ft_lenint_base(fstat.st_nlink, 10)) > max_len[0])
			max_len[0] = tmp;
		if ((tmp = ft_strlen(owner->pw_name))> max_len[1])
			max_len[1] = tmp;
		if ((tmp = ft_strlen(owner_group->gr_name))> max_len[2])
			max_len[2] = tmp;
		if ((tmp = ft_lenint_base(fstat.st_size, 10))> max_len[3])
			max_len[3] = tmp;
		head = head->next;
	}
}
void		ft_display(t_list *lst, unsigned char options)
{
	t_list	*head;
	int		total;
	int		max_len[4];

	ft_get_mandatories(lst, &total, max_len);
	ft_printf("total %d\n", total);
	head = lst;
	while (head)
	{
		if ((options & 2) == 2 || ((t_dir*)head->content)->name[0] != '.')
		{
			if ((options & 4) == 4)
				ft_ldisplay(head->content, max_len);
			else
				ft_printf("%s\n", ((t_dir*)head->content)->name);
		}
		ft_del_tdir(head->content);
		head = head->next;
	}
}
