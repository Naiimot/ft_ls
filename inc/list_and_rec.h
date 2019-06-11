/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_and_rec.h		                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:55:11 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/27 21:25:56 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_AND_REC_H

# define LIST_AND_REC_H

# include "libft.h"
# include "ft_printf.h"
# include "ft_ls.h"
# include <sys/types.h> 
# include <sys/stat.h> 
# include <errno.h>
# include <string.h>
# include <dirent.h>

void	ft_display(t_list *lst, unsigned int options, t_bool dirs);
void	ft_insert_dir(t_list **lst, t_dir dir, const unsigned int options);
void	ft_del_tdir(t_dir *dir);
void	ft_list_and_rec(t_list *lst_dir, unsigned int options, t_bool header);
t_bool	ft_fill_fstat(t_dir *tmp, char *path, char *name);

#endif
