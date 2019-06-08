#include "xattr_acl.h"

static char	ft_acl(t_dir *dir)
{
	acl_t acl;

	acl = acl_get_file(dir->full, ACL_TYPE_EXTENDED);
	if (acl != NULL)
		return ('+');
	else
		return (' ');
}

char		ft_xattr_acl(t_dir *dir)
{
	ssize_t ret;
	
	ret = listxattr(dir->full, NULL, 0, XATTR_NOFOLLOW);
	if (ret > 0)
		return ('@');
	else
		return (ft_acl(dir));
}
