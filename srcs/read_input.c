
#include "lem_in.h"

t_rooms		*get_room(t_map **map, char *name)
{
	t_rooms	*temp;

	temp = (*map)->start;
	while (temp && ft_strcmp(temp->name, name))
		temp = temp->next;
	return (temp);
}

int	is_room(char *str, t_map **map, int *flag)
{
	char	*room;
	char	*ptr;
	char	*start;
	char	*ch_xcoord;
	char	*ch_ycoord;
	int		x_coord;
	int		y_coord;

	ptr = ft_strchr(str, ' ');
	room = ft_strsub(str, 0, ptr - str);
	ptr++;
	start = ptr;
	if (!(ptr = ft_strchr(ptr, ' ')))
		lm_error("ERROR:room format\n");
	ch_xcoord = ft_strsub(str, start - str, ptr - start);
	ptr++;
	start = ptr;
	while (*ptr)
		ptr++;
	ch_ycoord = ft_strsub(str, start - str, ptr - start);
	if(!(x_coord = ft_atoi(ch_xcoord)) && ft_strcmp(ch_xcoord, "0") || 
			(!(y_coord = ft_atoi(ch_ycoord)) && ft_strcmp(ch_ycoord, "0")))
			lm_error("ERROR:Coord format\n");
	lm_addroom(map, room, x_coord, y_coord, flag);
	free(ch_xcoord);
	free(ch_ycoord);
	return (1);
}

int	is_link(char *str, t_map **map)
{
	char	*name1;
	char	*name2;
	t_rooms	*room1;
	t_rooms	*room2;
	char	*ptr;
	char	*start;

	ptr = ft_strchr(str, '-');
	name1 = ft_strsub(str, 0, ptr - str);
	if (!(room1 = get_room(map, name1)))
		lm_error("ERROR:Room does not exist\n");
	start = ptr + 1;
	while (*ptr)
		ptr++;
	name2 = ft_strsub(str, start-str, ptr-start);
	if (!(room2 = get_room(map, name2)))
		lm_error("ERROR:Room does not exist\n");
	if (!ft_strcmp(name1, name2))
		return (0);
	if(!lm_addtun(room1, room2) || !lm_addtun(room2, room1))
		lm_error("ERROR:Duplicate Link\n");
	free(name1);
	free(name2);
	return (0);
}
