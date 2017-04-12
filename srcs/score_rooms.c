
#include "lem_in.h"

/* Score all Rooms according proximity to End */
int	lm_all_scored(t_rooms *room)
{
	t_tunnels	*tmp_tun;
	
	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit->points == 0)
			return (0);
		tmp_tun = tmp_tun->next;
	}
	return (1);
}
void	lm_calcpoints_r(t_rooms *prev, t_rooms *room, int pts)
{
	t_tunnels	*tmp_tun;

	/* printf("===========Entering room==========:%s\n",room->name); */
	/* printf("prev room:%s\n",prev->name); */
	if (lm_all_scored(room))
	{
		/* printf("allmarked\n"); */
		return ;
	}
	tmp_tun = room->tun_list;
	/* lm_printtunnels(tmp_tun); */
	while (tmp_tun)
	{
		if (tmp_tun->exit->points == 0)
		{
			/* printf("setting:%s ->%d\n", tmp_tun->exit->name, pts); */
			tmp_tun->exit->points = pts;
		}
		tmp_tun = tmp_tun->next;
	}
	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit != prev)
			lm_calcpoints_r(room, tmp_tun->exit, pts + 1);
		tmp_tun = tmp_tun->next;
	}
}

void	lm_calcpoints(t_map *map)
{
	t_rooms		*temp;
	t_tunnels	*tmp_tun;

	temp = map->start;
	tmp_tun = map->start->tun_list;
	map->start->points = 101;
	map->end->points = 1;
	map->end->marked = 1;
	while (tmp_tun)
	{
		tmp_tun->exit->points = 100;
		tmp_tun = tmp_tun->next;
	}
	lm_valid_path(map, map->end, map->end);
	if (!map->valid)
	{
		printf("ERROR:No Valid Path\n");
		exit(-1);
	}
	lm_calcpoints_r(map->end,map->end,2);
}
