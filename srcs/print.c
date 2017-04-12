
#include "lem_in.h"

void	lm_printtunnels(t_tunnels *head)
{
	t_tunnels	*temp;

	temp = head;
	while (temp)
	{
		printf("exits to:%s\n",temp->exit->name);
		temp = temp->next;
	}
}

void	lm_printrooms(t_rooms *head)
{
	t_rooms	*temp;

	temp = head;
	while (temp)
	{
		printf("Room Name:%s\n", temp->name);
		printf("points:%d\n",temp->points);
		printf("Coord:(%d,%d)\n", temp->x_coord, temp->y_coord);
		lm_printtunnels(temp->tun_list);
		printf("==============================\n");
		temp = temp->next;
	}
}

void	lm_printants(t_ants *list, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("========ANTS ANTS ANTS==========\n");
		printf("Ant#%d\n",list[i].num);
		printf("score:%d\n",list[i].score);
		printf("current room:%s\n",list[i].room->name);
		i++;
	}
}
