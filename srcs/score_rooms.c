/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:42:27 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/07 20:32:58 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lm_all_scored(t_rooms *room)
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
	int			done;

	done = 1;
	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit->points < pts)
		{
			done = 0;
			tmp_tun->exit->points = pts;
		}
		tmp_tun = tmp_tun->next;
	}
	if (done)
		return ;
	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit != prev)
			lm_calcpoints_r(room, tmp_tun->exit, pts - 1);
		tmp_tun = tmp_tun->next;
	}
}

void	lm_calcpoints(t_map *map)
{
	if (!map->begin)
		lm_error("ERROR", "No starting point", *map);
	map->end->points = map->all_count;
	lm_valid_path(map, map->end, map->end);
	if (!map->valid)
		lm_error("ERROR", "No Valid Path", *map);
	lm_calcpoints_r(map->end, map->end, map->all_count - 1);
}
