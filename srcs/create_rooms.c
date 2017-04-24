/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:41:44 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/23 18:55:44 by kcheung          ###   ########.fr       */
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
	int		coord[2];
	char	*x;
	char	*y;

	room = get_rmname(str, &ptr);
	x = get_xcoord(str, &ptr, map);
	if ((!(coord[0] = ft_atoi(x)) &&
				ft_strcmp(x, "0")))
		lm_error("ERROR", "Coord format\n", **map);
	y = get_ycoord(str, &ptr);
	if (!(coord[1] = ft_atoi(y)) &&
		ft_strcmp(y, "0"))
		lm_error("ERROR", "Coord format\n", **map);
	lm_checkroom(**map, room);
	lm_addroom(map, room, coord, flag);
	free(x);
	free(y);
	return (1);
}
