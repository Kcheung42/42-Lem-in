/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:42:13 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/23 18:26:10 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lm_printtunnels(t_tunnels *head)
{
	t_tunnels	*temp;

	temp = head;
	while (temp)
	{
		ft_printf("%s-%s\n", temp->entrance->name, temp->exit->name);
		temp = temp->next;
	}
}

void	lm_printrooms(t_map *map)
{
	t_rooms	*temp;

	temp = map->start;
	while (temp)
	{
		if (temp == map->begin)
			ft_printf("##start\n");
		else if (temp == map->end)
			ft_printf("##end\n");
		ft_printf("%s %d %d\n", temp->name, temp->x_coord, temp->y_coord);
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
		ft_printf("Ant#%d\n", list[i].num);
		ft_printf("score:%d\n", list[i].score);
		ft_printf("current room:%s\n", list[i].room->name);
		i++;
	}
}
