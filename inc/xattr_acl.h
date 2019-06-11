#ifndef XATTR_ACL_C
# define XATTR_ACL_C

# include "ft_ls.h"
# include "ft_printf.h"
# include <sys/xattr.h>
# include <sys/acl.h>

typedef struct	s_xattr_acl
{
	acl_t	acl;
	ssize_t	sxattr;
}				t_xattr_acl;

void		ft_pacl(acl_t acl, t_bool isdir);

#endif
