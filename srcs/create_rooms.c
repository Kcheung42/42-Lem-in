
#include "lem_in.h"

t_rooms		*lm_newroom(char *name, int x, int y)
{
	t_rooms		*new;
	char		*cp_name;

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

t_rooms		*lm_addroom(t_map **map, char *name, int x, int y, int *flag)
{
	t_rooms	*temp;
	t_rooms	*new_room;

	new_room = lm_newroom(name, x, y);
	temp = (*map)->start;
	if (*flag == -1)
		(*map)->end = new_room;
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
