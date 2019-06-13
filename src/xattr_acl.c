#include "xattr_acl.h"

static void		ft_pxattr(const char *path, char *buff, ssize_t size)
{
	ssize_t i;
	ssize_t last;

	i = 0;
	while (i < size)
	{
		last = i;
		i += ft_printf("	%s", &buff[i]) - 1;
		ft_printf("			%jd\n", getxattr(path, &buff[last], NULL, 0, 0,\
			XATTR_NOFOLLOW));	
		i++;
	}
}

void		ft_print_xattr_acl(const char *path, t_xattr_acl *storage,\
				unsigned int options, t_bool isdir)
{
	char	buff[storage->sxattr];

	if ((options & OPT_XATTR) == OPT_XATTR && storage->sxattr > 0)
	{
		if (storage->sxattr == listxattr(path, buff, storage->sxattr,\
			XATTR_NOFOLLOW))
			ft_pxattr(path, buff, storage->sxattr);
	}
	if ((options & OPT_ACL) == OPT_ACL && storage->acl != NULL)
		ft_pacl(storage->acl, isdir);
	acl_free(storage->acl);
}
