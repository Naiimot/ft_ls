#ifndef ORDER_DIRS_H
# define ORDER_DIRS_H

# include "ft_ls.h"
# include <sys/types.h> 
# include <sys/stat.h> 

void		by_lct(t_list **lst, t_dir dir, const unsigned int options);
void		by_lat(t_list **lst, t_dir dir, const unsigned int options);
void		by_lmt(t_list **lst, t_dir dir, const unsigned int options);

#endif
