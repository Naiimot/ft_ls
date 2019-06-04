/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:26:10 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/28 13:11:46 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>
#include <string.h>

static int		ft_store_options(int ac, char **av, unsigned char *options, char *ret)
{
	int				i;
	int				j;

	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		j = 0;
		while (av[i][++j])
		{
			if (ft_strchr(VALID_OPTIONS, (int)av[i][j]) == NULL)
				*ret = av[i][j];
			if (av[i][j] == 'R')
				*options = *options | 1;
			else if (av[i][j] == 'a')
				*options = *options | 2;
			else if (av[i][j] == 'l')
				*options = *options | 4;
			else if (av[i][j] == 'r')
				*options = *options | 8;
			else if (av[i][j] == 't')
				*options = *options | 16;
		}
		i++;
	}
	*ret = 0;
	return (i);
}

void			ft_del_tdir(t_dir *dir)
{
	free(dir->name);
	free(dir->full);
	free(dir->fstat);
}

t_dir			ft_gen_tdir(char *path, char *name)
{
	t_dir	new;
	
	if (path == NULL)
	{
		new.name = ft_strdup(name);
		new.full = ft_strdup(name);
	}
	else
	{
		new.name = ft_strdup(name);
		if (ft_strequ(path, "/") == 1)
			new.full = ft_strjoin(path, name);
		else
			new.full = ft_strjoinsep(path, name, '/');
	}
	if (!(new.fstat = (struct stat*)malloc(sizeof(struct stat))))
		return (new);
	if (stat(new.full, new.fstat) == -1)
		ft_dprintf(2, "ls: %s: %s\n", new.full, strerror(errno));
	return (new);
}

int				main(int ac, char **av)
{
	unsigned char	options;
	char			c;
	t_list			*lst_dir;
	int				i;

	options = 0;
	i = ft_store_options(ac, av, &options, &c);
	if (c  != '\0')
	{
		ft_dprintf(2, "ls: illegal option -- %c\nusage: ls [-%s] [file ...]\n",\
			c, VALID_OPTIONS);
		return (-1);
	}
	if (i == ac)
		ft_insert_dir(&lst_dir, ft_gen_tdir(NULL, "."), options);
	else
		while (i < ac)
			ft_insert_dir(&lst_dir, ft_gen_tdir(NULL, av[i++]), options);
	ft_ls(lst_dir, options, FALSE);
	return (0);
}
