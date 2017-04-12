
#include "lem_in.h"

void	lm_printtunnels(t_tunnels *head)
{
	t_tunnels	*temp;

	temp = head;
	while (temp)
	{
		ft_printf("exits to:%s\n",temp->exit->name);
		temp = temp->next;
	}
}

void	lm_printrooms(t_rooms *head)
{
	t_rooms	*temp;

	temp = head;
	while (temp)
	{
		ft_printf("Room Name:%s\n", temp->name);
		ft_printf("points:%d\n",temp->points);
		ft_printf("Coord:(%d,%d)\n", temp->x_coord, temp->y_coord);
		lm_printtunnels(temp->tun_list);
		ft_printf("==============================\n");
		temp = temp->next;
	}
}

void	lm_printants(t_ants *list, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_printf("========ANTS ANTS ANTS==========\n");
		ft_printf("Ant#%d\n",list[i].num);
		ft_printf("score:%d\n",list[i].score);
		ft_printf("current room:%s\n",list[i].room->name);
		i++;
	}
}
