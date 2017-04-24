/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:39:24 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/23 18:21:49 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_fd	*ft_fd_add(t_fd **head, int fd)
{
	t_fd	*new;
	t_fd	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	if (temp == NULL)
	{
		new = (t_fd *)malloc(sizeof(t_fd));
		new->fd = fd;
		new->ptr = NULL;
		new->stock = NULL;
		new->next = *head;
		*head = new;
	}
	return (*head);
}

int		ft_strlen_n(char *str)
{
	if (*str == '\n' || *str == '\0')
		return (0);
	return (1 + ft_strlen_n(str + 1));
}

void	fill_line(char **line, t_fd *temp, int *r, t_fd *t)
{
	int		i;

	i = 0;
	*line = ft_realloc(*line, ft_strlen_n(temp->ptr));
	ft_bzero(*line, ft_strlen_n(temp->ptr));
	while (*(temp->ptr) != '\n' && *(temp->ptr) != '\0')
	{
		(*line)[i] = *(temp->ptr);
		temp->ptr = temp->ptr + 1;
		i++;
	}
	*r = 1;
	t->ptr = t->ptr + 1;
}

void	free_things(t_fd **head, t_fd *cur, char **buff, int ret)
{
	t_fd	*temp;

	temp = NULL;
	if (ret == 0 && cur->stock)
	{
		if (cur == *head)
			*head = cur->next;
		else
		{
			temp = *head;
			while (temp->next != cur)
				temp = temp->next;
			temp->next = cur->next;
		}
		free(cur->stock);
		cur->stock = NULL;
		free(cur);
	}
	free(*buff);
	buff = NULL;
}

int		get_next_line(const int fd, char **line)
{
	static t_fd	*head;
	t_fd		*t;
	char		*b;
	int			r;
	char		*tofree;

	t = ft_fd_add(&head, fd);
	if (!line || !(*line = ft_strnew(1)))
		return (-1);
	b = ft_strnew(BUFF_SIZE);
	while ((r = read(t->fd, b, BUFF_SIZE)) > 0)
	{
		tofree = t->stock;
		t->stock = (t->stock) ? ft_strjoin(t->stock, b) : ft_strjoin("\0", b);
		free(tofree);
		t->ptr = t->stock;
		ft_bzero(b, BUFF_SIZE);
	}
	if (r < 0)
		return (-1);
	(t->ptr && (ft_strlen(t->ptr) > 0 || *(t->ptr) == '\n')) ?
		fill_line(line, t, &r, t) : free(*line);
	free_things(&head, t, &b, r);
	return (r);
}
