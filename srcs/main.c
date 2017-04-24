/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:41:54 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/23 19:01:13 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init(t_map **map)
{
	(*map)->start = NULL;
	(*map)->begin = NULL;
	(*map)->end = NULL;
	(*map)->tunnels = NULL;
	(*map)->all_count = 0;
	(*map)->visual = 0;
}

void	free_map(t_map **map, t_ants **antlist)
{
	t_rooms		*cur_rm;
	t_tunnels	*cur_tn;

	while ((cur_rm = (*map)->start))
	{
		while ((cur_tn = cur_rm->tun_list))
		{
			free(cur_tn);
			cur_rm->tun_list = cur_rm->tun_list->next;
		}
		free(cur_rm->name);
		free(cur_rm);
		(*map)->start = (*map)->start->next;
	}
	while ((cur_tn = (*map)->tunnels))
	{
		free(cur_tn);
		(*map)->tunnels = (*map)->tunnels->next;
	}
	free((*map)->start);
	free(*antlist);
	free(*map);
}

int		main(int argc, char *argv[])
{
	t_ants	*antlist;
	t_map	*map;

	if (argc > 2)
	{
		ft_putstr_fd("ERROR\n", 2);
		return (2);
	}
	map = (t_map *)malloc(sizeof(t_map));
	init(&map);
	map->visual = (argc == 2 && !ft_strcmp("-v", argv[1])) ? 1 : 0;
	antlist = NULL;
	if (!(antlist = lm_parse_map(&map, antlist)))
		lm_error("ERROR", "No ants", *map);
	if (!map->start)
		lm_error("ERROR", "No rooms", *map);
	lm_calcpoints(map);
	ft_printf("%d\n", map->all_count);
	lm_printrooms(map);
	lm_printtunnels(map->tunnels);
	while (map->end->ant_count != map->all_count)
		lm_find_next_path(*map, antlist);
	free_map(&map, &antlist);
	(void)argv;
	return (0);
}
