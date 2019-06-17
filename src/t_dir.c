/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:07:17 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/17 19:26:15 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir.h"

void		ft_del_tdir(t_dir *dir)
{
	free(dir->name);
	free(dir->full);
	free(dir->fstat);
	ft_bzero(dir, sizeof(t_dir));
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

void		ft_gen_tdir(t_dir *tmp, char *path, char *name)
{
	tmp->name = ft_strdup(ft_get_only_name(name));
	if (path == NULL)
		tmp->full = ft_strdup(name);
	else
	{
		if (ft_strequ(path, "/") == 1)
			tmp->full = ft_strjoin(path, name);
		else
			tmp->full = ft_strjoinsep(path, name, '/');
	}
	tmp->fstat = (struct stat*)malloc(sizeof(struct stat));
}

t_bool		ft_gen_fstat(t_dir *tmp)
{
	if (lstat(tmp->full, tmp->fstat) == -1)
	{
		ft_dprintf(2, "ls: %s: %s\n", tmp->full, strerror(errno));
		ft_del_tdir(tmp);
		return (FALSE);
	}
	return (TRUE);
}

void		ft_make_tdir(t_list **lst, char *path, char *name,\
				const unsigned int options)
{
	t_dir			tmp;

	ft_gen_tdir(&tmp, path, name);
	ft_initial_list(lst, tmp, options);
}
