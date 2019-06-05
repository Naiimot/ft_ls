#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

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

static char		*ft_6month(t_dir *dir)
{
	char	*str;
	time_t	dif;

	str = ctime(&dir->fstat->st_mtime);
	str[16] = '\0';
	dif = time(NULL) - dir->fstat->st_mtime;
	if (dif < -15778800 || dif > 15778800)
	{
		str[11] = ' ';
		ft_strncpy(&str[12], &str[20], 4);
	}
	return (str);
}

void	ft_ldisplay(t_dir *dir, int *max_len)
{
	char			perms[11];
	struct passwd	*owner;
	struct group	*group;
	char			buff[PATH_MAX];
	ssize_t			len;


	ft_get_perms(dir->fstat, perms);
	owner = getpwuid(dir->fstat->st_uid);
	group = getgrgid(dir->fstat->st_gid);
	ft_printf("%s  %*d %-*s  %-*s  %*d %s %s",\
		perms, max_len[0], dir->fstat->st_nlink, max_len[1], owner->pw_name,\
		max_len[2], group->gr_name, max_len[3], dir->fstat->st_size,\
		ft_6month(dir) + 4, dir->name);
	if (S_ISLNK(dir->fstat->st_mode))
	{
		if ((len = readlink(dir->full, buff, sizeof(buff)-1)) != -1)
			buff[len] = '\0';
		ft_printf(" -> %s", buff);
	}
	ft_printf("\n");
}
