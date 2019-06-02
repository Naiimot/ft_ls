/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:44:53 by tdelabro          #+#    #+#             */
/*   Updated: 2019/05/25 21:57:38 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../inc/get_next_line.h"

static void	ft_fill_node(char *buff, t_fd *current_fd)
{
	int		ret;
	char	*tmp;

	current_fd->ret = 0;
	while ((ret = read(current_fd->fd, buff, BUFF_SIZE)) > 0)
	{
		current_fd->ret = 1;
		buff[ret] = '\0';
		tmp = current_fd->str;
		if (current_fd->str == NULL)
			current_fd->str = ft_strdup(buff);
		else
			current_fd->str = ft_strjoin(current_fd->str, buff);
		ft_memdel((void**)&tmp);
		if ((current_fd->remain = \
				ft_strchr(current_fd->str, '\n')) != NULL)
		{
			*(current_fd->remain) = '\0';
			current_fd->remain++;
			break ;
		}
	}
}

static t_fd	*ft_initfd(int fd, char *buff)
{
	t_fd	*new;

	if (!(new = ft_memalloc(sizeof(t_fd))))
		return (NULL);
	new->fd = fd;
	ft_fill_node(buff, new);
	return (new);
}

static void	ft_refill(t_fd *current_fd, char **line, char *buff)
{
	char *tmp;

	tmp = current_fd->remain;
	if ((current_fd->remain = \
			ft_strchr(current_fd->remain, '\n')) != NULL)
	{
		*(current_fd->remain)++ = '\0';
		*line = ft_strdup(tmp);
	}
	else
	{
		*line = ft_strdup(tmp);
		ft_memdel((void**)&current_fd->str);
		ft_fill_node(buff, current_fd);
		if (*line && current_fd->str)
		{
			tmp = *line;
			*line = ft_strjoin(*line, current_fd->str);
			ft_memdel((void**)&tmp);
		}
	}
}

int			get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static t_list	*lst = NULL;
	t_list			*head;

	if (fd < 0 || (read(fd, NULL, 0) == -1) || !(line) || BUFF_SIZE < 0)
		return (-1);
	head = lst;
	while (head)
	{
		if (((t_fd*)head->content)->fd == fd)
			break ;
		head = head->next;
	}
	if (head == NULL)
	{
		ft_lstadd(&lst, head = ft_lstnew(NULL, 0));
		head->content = ft_initfd(fd, buff);
		head->content_size = sizeof(t_fd);
		*line = ft_strdup(((t_fd*)head->content)->str);
	}
	else
		ft_refill(head->content, line, buff);
	if (ft_strlen(*line) > 0)
		((t_fd*)head->content)->ret = 1;
	return (((t_fd*)head->content)->ret);
}
