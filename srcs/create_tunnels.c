
#include "lem_in.h"

/* Creating Tunnels */
/* check to make sure tunnels do not already exist */
t_tunnels	*lm_newtun(t_rooms *room)
{
	t_tunnels	*new;

	new = (t_tunnels *)malloc(sizeof(t_tunnels));
	new->next = NULL;
	new->exit = room;
	return (new);
}

t_tunnels	*lm_addtun(t_rooms *room1, t_rooms *room2)
{
	t_tunnels	*temp;
	t_tunnels	*new_tun;
	
	new_tun = lm_newtun(room2);
	temp = room1->tun_list;
	if (!temp)
		room1->tun_list = new_tun;
	else
	{
		while (temp->next != NULL && temp->exit != room2)
			temp = temp->next;
		if (temp->exit == room2)
			return (NULL);
		else
			temp->next = new_tun;
	}
	new_tun = lm_newtun(room1);
	temp = room2->tun_list;
	if (!temp)
		room2->tun_list = new_tun;
	else
	{
		while (temp->next != NULL && temp->exit != room1)
			temp = temp->next;
		if (temp->exit == room1)
			return (NULL);
		else
			temp->next = new_tun;
	}
}
