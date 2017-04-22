/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tunnels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:41:50 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/22 14:13:34 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms		*get_room(t_map **map, char *name)
{
	t_rooms	*temp;

	temp = (*map)->start;
	while (temp && ft_strcmp(temp->name, name))
		temp = temp->next;
	return (temp);
}

t_tunnels	*lm_newtun(t_rooms *ent, t_rooms *ext)
{
	t_tunnels	*new;

	new = (t_tunnels *)malloc(sizeof(t_tunnels));
	new->next = NULL;
	new->entrance = ent;
	new->exit = ext;
	return (new);
}

t_tunnels	*lm_addtun(t_rooms *entrance, t_rooms *exit)
{
	t_tunnels	*temp;
	t_tunnels	*new_tun;

	new_tun = lm_newtun(entrance, exit);
	temp = entrance->tun_list;
	if (!temp)
	{
		entrance->tun_list = new_tun;
		return (new_tun);
	}
	else
	{
		while (temp->next != NULL && temp->exit != exit)
			temp = temp->next;
		if (temp->exit == exit)
			return (NULL);
		else
		{
			temp->next = new_tun;
			return (new_tun);
		}
	}
}

void		store_link(t_map **map, t_rooms *room1, t_rooms *room2)
{
	t_tunnels	*tmp;
	t_tunnels	*new_tun;

	tmp = (*map)->tunnels;
	new_tun = lm_newtun(room1, room2);
	if (!tmp)
		(*map)->tunnels = new_tun;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_tun;
	}
}

int			is_link(char *str, t_map **map)
{
	t_rooms	*room1;
	t_rooms	*room2;
	char	*ptr;
	char	*start;

	ptr = ft_strchr(str, '-');
	if (!(room1 = get_room(map, ft_strsub(str, 0, ptr - str))))
		lm_error("ERROR", "Room does not exist", **map);
	start = ptr + 1;
	while (*ptr)
		ptr++;
	if (!(room2 = get_room(map, ft_strsub(str, start - str, ptr - start))))
		lm_error("ERROR", "Room does not exist", **map);
	if (!ft_strcmp(ft_strsub(str, 0, ptr - str),
				ft_strsub(str, start - str, ptr - start)))
		return (0);
	if (ft_strcmp(room1->name, room2->name))
	{
		if (lm_addtun(room1, room2) && lm_addtun(room2, room1))
			store_link(map, room1, room2);
	}
	return (0);
}
