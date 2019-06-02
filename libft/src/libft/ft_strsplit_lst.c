/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:57:22 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 22:14:45 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_size_word(const char *s, char c, int *pos)
{
	int i;

	i = 0;
	while (s[*pos + i] && s[*pos + i] != c)
		i++;
	return (i);
}

static char		*ft_get_word(const char *s, char c, int *pos)
{
	int		i;
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * (ft_size_word(s, c, pos) + 1))))
		return (NULL);
	i = 0;
	while (s[*pos + i] && s[*pos + i] != c)
	{
		tmp[i] = s[*pos + i];
		i++;
	}
	tmp[i] = '\0';
	*pos = *pos + i;
	return (tmp);
}

static void		ft_end(const char *s, char c, t_list *new, char *tmp)
{
	ft_memdel((void**)&tmp);
	new->next = NULL;
	ft_strsplit_lst(s, c);
}

t_list			*ft_strsplit_lst(const char *s, char c)
{
	static int		i = 0;
	static int		*ptr = &i;
	char			*tmp;
	static t_list	*start = NULL;
	static t_list	*new = NULL;

	if (!s || !c)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (start);
	tmp = ft_get_word(s, c, ptr);
	if (start == NULL)
		if (!(new = ft_lstnew(tmp, sizeof(char) * (ft_strlen(tmp) + 1))))
			return (NULL);
	if (start != NULL)
		if (!(new->next = ft_lstnew(tmp, sizeof(char) * (ft_strlen(tmp) + 1))))
			return (NULL);
	if (start == NULL)
		start = new;
	else
		new = new->next;
	ft_end(s, c, new, tmp);
	return (start);
}
