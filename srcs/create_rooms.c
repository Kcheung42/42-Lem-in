/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:41:44 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/14 15:43:15 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*lm_newroom(char *name, int x, int y)
{
	t_rooms	*new;
	char	*cp_name;

	new = (t_rooms *)malloc(sizeof(t_rooms));
	cp_name = name;
	new->name = cp_name;
	new->occupied = 0;
	new->ant_count = 0;
	new->points = 0;
	new->x_coord = x;
	new->y_coord = y;
	new->marked = 0;
	new->tun_list = NULL;
	return (new);
}

void	lm_addroom(t_map **map, char *name, int *coord, int *flag)
{
	t_rooms	*temp;
	t_rooms	*new_room;

	new_room = lm_newroom(name, coord[0], coord[1]);
	temp = (*map)->start;
	if (*flag == -1)
		(*map)->end = new_room;
	if (*flag == 1)
		(*map)->begin = new_room;
	if (!(*map)->start)
		(*map)->start = new_room;
	else if (*flag == 1)
	{
		new_room->next = temp;
		(*map)->start = new_room;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_room;
	}
	*flag = 0;
}

void	lm_checkroom(t_map map, char *room)
{
	t_rooms	*temp;

	temp = map.start;
	while (temp)
	{
		if (!ft_strcmp(room, temp->name))
			lm_error("ERROR", "Duplicate room name", map);
		temp = temp->next;
	}
}

int		is_room(char *str, t_map **map, int *flag)
{
	char	*room;
	char	*ptr;
	char	*start;
	int		coord[2];

	ptr = ft_strchr(str, ' ');
	room = ft_strsub(str, 0, ptr - str);
	ptr++;
	start = ptr;
	if (!(ptr = ft_strchr(ptr, ' ')))
		lm_error("ERROR", "room format", **map);
	if ((!(coord[0] = ft_atoi(ft_strsub(str, start - str, ptr - start))) &&
				ft_strcmp(ft_strsub(str, start - str, ptr - start), "0")))
		lm_error("ERROR", "Coord format\n", **map);
	start = ptr + 1;
	while (*ptr)
		ptr++;
	if (!(coord[1] = ft_atoi(ft_strsub(str, start - str, ptr - start))) &&
		ft_strcmp(ft_strsub(str, start - str, ptr - start), "0"))
		lm_error("ERROR", "Coord format\n", **map);
	lm_checkroom(**map, room);
	lm_addroom(map, room, coord, flag);
	return (1);
}
