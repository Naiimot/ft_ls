#include "ldisplay.h"

static char		*ft_6month(t_dir *dir, unsigned int options)
{
	char	*str;
	time_t	dif;

	if (options & OPT_ATIME)
		str = ctime(&dir->fstat->st_atime);
	else if (options & OPT_CTIME)
		str = ctime(&dir->fstat->st_ctime);
	else
		str = ctime(&dir->fstat->st_mtime);
	str[16] = '\0';
	if (options & OPT_ATIME)
		dif = time(NULL) - dir->fstat->st_atime;
	else if (options & OPT_CTIME)
		dif = time(NULL) - dir->fstat->st_ctime;
	else
		dif = time(NULL) - dir->fstat->st_mtime;
	if (dif < -15778800 || dif > 15778800)
	{
		str[11] = ' ';
		ft_strncpy(&str[12], &str[20], 4);
	}
	return (str);
}

static char		ft_xattr_acl(const char* path, t_xattr_acl *storage)
{
	storage->sxattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	storage->acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (storage->sxattr > 0)
		return ('@');
	else if (storage->acl != NULL)
		return ('+');
	else
	{
		storage->sxattr = 0;
		return (' ');
	}
}

void	ft_ldisplay(t_dir *dir, int *max_len, char *perms, unsigned int options)
{
	struct passwd	*owner;
	struct group	*group;
	char			buff[PATH_MAX];
	t_xattr_acl		storage;
	ssize_t			len;

	owner = getpwuid(dir->fstat->st_uid);
	group = getgrgid(dir->fstat->st_gid);
	ft_printf("%s%c%*d %-*s%-*s", perms,\
		ft_xattr_acl(dir->full, &storage), max_len[0], dir->fstat->st_nlink,\
		max_len[1], (options & OPT_ONLYGRP) ?  "" : owner->pw_name,\
		max_len[2], group->gr_name);
	if (perms[0] == 'c')
		ft_printf("%3d, %3d %s %s%s%s", dir->fstat->st_rdev >> 24 & 0xff,\
		dir->fstat->st_rdev & 0xffffff, ft_6month(dir, options) + 4,\
			ft_colorize(perms, options), dir->name, C_EOC);
	else
		ft_printf("%*d %s %s%s%s", max_len[3], dir->fstat->st_size,\
			ft_6month(dir, options) + 4, ft_colorize(perms, options), dir->name, C_EOC);
	if (S_ISLNK(dir->fstat->st_mode))
	{
		if ((len = readlink(dir->full, buff, sizeof(buff)-1)) != -1)
			buff[len] = '\0';
		ft_printf(" -> %s", buff);
	}
	ft_printf("\n");
	ft_print_xattr_acl(dir->full, &storage, options, S_ISDIR(dir->fstat->st_mode));
}
