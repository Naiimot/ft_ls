/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_dirs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:16:13 by tdelabro          #+#    #+#             */
/*   Updated: 2019/06/15 16:16:18 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ORDER_DIRS_H
# define ORDER_DIRS_H

# include "ft_ls.h"
# include <sys/types.h>
# include <sys/stat.h>

void		by_lct(t_list **lst, t_dir dir, const unsigned int options);
void		by_lat(t_list **lst, t_dir dir, const unsigned int options);
void		by_lmt(t_list **lst, t_dir dir, const unsigned int options);

#endif
