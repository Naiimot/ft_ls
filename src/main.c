/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:26:10 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/16 23:47:44 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	ft_store_options_2(char c, unsigned int *options)
{
	if (c == 'f')
		*options = *options | OPT_NOSORT | OPT_ALL;
	else if (c == 'r')
		*options = *options | OPT_REV;
	else if (c == 'S')
		*options = *options | OPT_SIZESORT;
	else if (c == 't')
		*options = *options | OPT_MTIME;
	else if (c == 'u')
		*options = *options | OPT_ATIME;
	else if (c == 'c')
		*options = *options | OPT_CTIME;
	else if (c == '@')
		*options = *options | OPT_XATTR;
	else if (c == 'e')
		*options = *options | OPT_ACL;
	else if (c == 'G')
		*options = *options | OPT_COLOR;
	else if (c == 'g')
		*options = *options | OPT_LONG | OPT_ONLYGRP;
	else if (c == 'd')
		*options = *options | OPT_NORECDIR | OPT_ALL;
}

static int	ft_store_options(int ac, char **av, unsigned int *options,\
				char *ret)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		if (ft_strcmp(av[i], "--") == 0)
			return (i + 1);
		j = 0;
		while (av[i][++j])
		{
			if (ft_strchr(VALID_OPTIONS, av[i][j]) == NULL)
				*ret = av[i][j];
			if (av[i][j] == 'R')
				*options = *options | OPT_REC;
			else if (av[i][j] == 'a')
				*options = *options | OPT_ALL;
			else if (av[i][j] == 'l')
				*options = *options | OPT_LONG;
			else
				ft_store_options_2(av[i][j], options);
		}
		i++;
	}
	return (i);
}

static int	ft_handle_options(int ac, char **av, unsigned int *options)
{
	char	c;
	int		i;

	*options = 0;
	c = '\0';
	i = ft_store_options(ac, av, options, &c);
	if (c != '\0')
	{
		ft_dprintf(2, "ls: illegal option -- %c\nusage: ls [-%s] [file ...]\n",\
			c, VALID_OPTIONS);
		return (-1);
	}
	return (i);
}

static void	ft_print_file_and_dir(t_list **tab_lst, const unsigned int options)
{
	t_bool	flistexist;
	
	flistexist = (tab_lst[0]) ? TRUE : FALSE;

	if (ft_display(tab_lst[0], options, FALSE) && tab_lst[1])
		ft_printf("\n");
	ft_list_and_rec(tab_lst[1], options, flistexist);
}

static void	ft_split_args(t_list *tab_lst[2], const unsigned int options)
{
	t_list	*prev;
	t_list	*head;
	t_list	*next;

	head = tab_lst[0];
	prev = NULL;
	while (head)
	{
		next = head->next;
		if (!(options & OPT_NORECDIR)\
			&& ((t_dir*)head->content)->fstat
			&& S_ISDIR(((t_dir*)head->content)->fstat->st_mode))
		{
			if (prev)
				prev->next = head->next;
			else
				tab_lst[0] = tab_lst[0]->next;
			ft_lstappend(&tab_lst[1], head); 
		}
		else
			prev = head;
		head = next;
	}
}

int			main(int ac, char **av)
{
	unsigned int	options;
	t_list			*tab_lst[2];
	int				i;
	t_dir			tmp;

	if ((i = ft_handle_options(ac, av, &options)) == -1)
		return (1);
	ft_bzero(tab_lst, sizeof(t_list*) * 2);
	if (i == ac)
	{
		ft_gen_tdir(&tmp, NULL, ".");
		ft_gen_fstat(&tmp);
		ft_lstadd((options & OPT_NORECDIR) ? &tab_lst[0] : &tab_lst[1],\
			ft_lstnew(&tmp, sizeof(t_dir)));
	}
	else
	{
		while (i < ac)
		{
			ft_gen_tdir(&tmp, NULL, av[i++]);
			ft_initial_list(&tab_lst[0], tmp, options);
		}
		ft_get_args_stat(tab_lst[0]);
		ft_order_dirs(&tab_lst[0], options);
		ft_split_args(tab_lst, options);
	}
	ft_print_file_and_dir(tab_lst, options);
	return (0);
}
