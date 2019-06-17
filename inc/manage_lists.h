/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:19:54 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/17 19:23:54 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGE_LISTS_H
# define MANAGE_LISTS_H

# include "libft.h"
# include "ft_ls.h"
# include <sys/types.h>
# include <sys/stat.h>

void	ft_order_dirs(t_list *tab_lst[2], const unsigned int options);
t_bool	ft_gen_fstat(t_dir *tmp);

#endif
