/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:16:02 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/17 17:49:23 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "ft_ls.h"
# include "ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>

# define VALID_OPTIONS "Ralrt@eGfugdcS"

t_bool	ft_gen_fstat(t_dir *dir);
void	ft_get_args_stat(t_list **lst);
void	ft_initial_list(t_list **lst, t_dir dir, const unsigned int options);
void	ft_gen_tdir(t_dir *tmp, char *path, char *name);
void	ft_del_tdir(t_dir *dir);
void	ft_order_dirs(t_list **lst, const unsigned options);
t_bool	ft_display(t_list *lst, unsigned int options, t_bool dirs);
void	ft_list_and_rec(t_list *lst_dir, unsigned int options, t_bool hdr);

#endif
