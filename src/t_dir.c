#include "t_dir.h"

void		ft_del_tdir(t_dir *dir)
{
	free(dir->name);
	free(dir->full);
	free(dir->fstat);
}

static char	*ft_get_only_name(char *str)
{
	int	i;
	int	last_slash_pos;

	last_slash_pos = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '/')
			last_slash_pos = i;
	if (last_slash_pos == 0)
		return (str);
	else if (str[last_slash_pos + 1] == '\0')
	{
		while (str[last_slash_pos - 1] != '/')
			last_slash_pos--;
		return (&str[last_slash_pos]);
	}
	else
		return (&str[last_slash_pos + 1]);
}

static t_dir		ft_gen_tdir(char *path, char *name)
{
	t_dir	new;
	
	new.name = ft_strdup(ft_get_only_name(name));
	if (path == NULL)
		new.full = ft_strdup(ft_get_only_name(name));
	else
	{
		if (ft_strequ(path, "/") == 1)
			new.full = ft_strjoin(path, name);
		else
			new.full = ft_strjoinsep(path, name, '/');
	}
	new.fstat = (struct stat*)malloc(sizeof(struct stat));
	return (new);
}

t_bool		ft_fill_fstat(t_dir *tmp, char *path, char *name)
{
	*tmp = ft_gen_tdir(path, name);
	if (lstat(tmp->full, tmp->fstat) == -1)
	{
		ft_dprintf(2, "ls: %s: %s\n", tmp->full, strerror(errno));
		ft_del_tdir(tmp);
		return (FALSE);
	}
	return (TRUE);
}
