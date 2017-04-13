/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:41:54 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/12 19:18:30 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(int argc, char *argv[])
{
	t_ants	*antlist;
	t_map	*map;
	char	*line;

	map = (t_map *)malloc(sizeof(t_map));
	map->start = NULL;
	map->end = NULL;
	map->tunnels = NULL;
	map->all_count = 0;
	antlist = NULL;
	if (!(antlist = lm_parse_map(&map, argv, antlist)))
		lm_error("ERROR:No ants\n");
	if (!map->start)
		lm_error("ERROR:No rooms\n");
	lm_calcpoints(map);
	ft_printf("%d\n", map->all_count);
	lm_printrooms(map);
	lm_printtunnels(map->tunnels);
	while (map->end->ant_count != map->all_count)
		lm_find_next_path(*map, antlist);
	return (0);
}
