/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:39:24 by kcheung           #+#    #+#             */
/*   Updated: 2017/03/01 10:44:33 by kcheung          ###   ########.fr       */
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
		new->stock = ft_strnew(1);
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

void	fill_line(char **line, t_fd *temp)
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
}

void	free_things(t_fd *temp, char **buff, char **line, int ret)
{
	if (ret == 0 && temp->stock)
	{
		free(temp->stock);
		temp->stock = NULL;
	}
	free(*buff);
	free(*line);
}

int		get_next_line(const int fd, char **line)
{
	static t_fd	*head;
	t_fd		*temp;
	char		*buff;
	int			ret;

	temp = ft_fd_add(&head, fd);
	ret = 0;
	if (!line || !(*line = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((buff = ft_strnew(BUFF_SIZE)) &&
			(ret = read(temp->fd, buff, BUFF_SIZE)) > 0)
	{
		temp->stock = ft_strjoin(temp->stock, buff);
		temp->ptr = temp->stock;
		free(buff);
	}
	if (ret < 0)
		return (-1);
	if (ft_strlen(temp->ptr) > 0 || *(temp->ptr) == '\n')
	{
		fill_line(line, temp);
		temp->ptr = temp->ptr + 1;
		ret = 1;
	}
	return (ret);
}
