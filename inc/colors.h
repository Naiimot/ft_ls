#ifndef COLORS_H
# define COLORS_H

# define C_REGULAR		"\033[37m"
# define C_EXEC			"\033[31m"
# define C_DIR			"\033[1;36m"
# define C_CPERIPH		"\033[34m\033[43m"
# define C_BPERIPH		"\033[34m\033[46m"
# define C_SLINK		"\033[35m"
# define C_SOCKET		"\033[32m"
# define C_PIPE			"\033[33m"
# define C_USTICKY		"\033[30m\033[41m"
# define C_GSTICKY		"\033[30m\033[46m"
# define C_DIR_WO_S		"\033[30m\033[42m"
# define C_DIR_WO_NS	"\033[30m\033[43m"
# define C_EOC			"\033[0m"

char	*ft_colorize(char *perms, unsigned int options);

#endif
