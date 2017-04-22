/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:42:34 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/22 10:27:46 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lm_move_ants(t_map map, t_ants *ants, int i, t_rooms *to_move)
{
	ants[i].room->occupied = 0;
	ants[i].room = to_move;
	ants[i].score += ants[i].room->points;
	ants[i].room->occupied = (ants[i].room == map.end) ? 0 : 1;
	map.end->ant_count += (ants[i].room == map.end) ? 1 : 0;
	ft_printf("L%d-%s ", ants[i].num, ants[i].room->name);
}

void	move(t_tunnels *tmp_tun, int *max_score, t_ants ant, t_rooms **to_move)
{
	if (tmp_tun->exit->occupied == 0 &&
		tmp_tun->exit->points >= *max_score &&
		tmp_tun->exit->points > ant.room->points)
	{
		*max_score = tmp_tun->exit->points;
		*to_move = tmp_tun->exit;
	}
}

void	lm_find_next_path(t_map map, t_ants *ants)
{
	int			i;
	t_tunnels	*tmp_tun;
	int			max_score;
	t_rooms		*to_move;

	i = 0;
	while (i < map.all_count)
	{
		tmp_tun = ants[i].room->tun_list;
		max_score = tmp_tun->exit->points;
		to_move = NULL;
		while (tmp_tun)
		{
			move(tmp_tun, &max_score, ants[i], &to_move);
			tmp_tun = tmp_tun->next;
		}
		if (to_move)
			lm_move_ants(map, ants, i, to_move);
		i++;
	}
	ft_printf("\n");
}
