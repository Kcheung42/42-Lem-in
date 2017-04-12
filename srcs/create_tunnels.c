
#include "lem_in.h"

t_tunnels	*lm_newtun(t_rooms *room)
{
	t_tunnels	*new;

	new = (t_tunnels *)malloc(sizeof(t_tunnels));
	new->next = NULL;
	new->exit = room;
	return (new);
}

t_tunnels	*lm_addtun(t_rooms *entrance, t_rooms *exit)
{
	t_tunnels	*temp;
	t_tunnels	*new_tun;
	
	new_tun = lm_newtun(exit);
	temp = entrance->tun_list;
	if (!temp)
		entrance->tun_list = new_tun;
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
