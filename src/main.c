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

#include "main.h"

static int	ft_store_options(int ac, char **av, unsigned char *options,\
				char *ret)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		j = 0;
		while (av[i][++j])
		{
			if (ft_strchr(VALID_OPTIONS, av[i][j]) == NULL)
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
	return (i);
}

static int	ft_handle_options(int ac, char **av, unsigned char *options)
{
	char	c;
	int		i;

	*options = 0;
	c = '\0';
	i = ft_store_options(ac, av, options, &c);
	if (c  != '\0')
	{
		ft_dprintf(2, "ls: illegal option -- %c\nusage: ls [-%s] [file ...]\n",\
			c, VALID_OPTIONS);
		return (-1);
	}
	return (i);
}

static void	ft_print_file_and_dir(t_list **tab_lst, unsigned char options)
{
	ft_display(tab_lst[0], options, FALSE);
	if (tab_lst[0] && tab_lst[1])
		ft_printf("\n");
	ft_list_and_rec(tab_lst[1], options, (tab_lst[0]) ? TRUE : FALSE);
	ft_lstclear(&tab_lst[0]);
}

int				main(int ac, char **av)
{
	unsigned char	options;
	t_list			*tab_lst[2];
	int				i;
	t_dir			tmp;

	if ((i = ft_handle_options(ac, av, &options)) == -1)
			return (-1);
	ft_bzero(tab_lst, sizeof(t_list*) * 2);
	if (i == ac)
		ft_insert_dir(&tab_lst[1], ft_gen_tdir(NULL, "."), options);
	else
		while (i < ac)
			if (ft_fill_fstat(&tmp, NULL, av[i++]) == TRUE) 
				ft_insert_dir((S_ISDIR(tmp.fstat->st_mode)) ?\
					&tab_lst[1] : &tab_lst[0], tmp, options);
	ft_print_file_and_dir(tab_lst, options);
	return (0);
}
