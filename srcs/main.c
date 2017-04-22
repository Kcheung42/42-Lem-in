/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:41:54 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/22 14:30:37 by kcheung          ###   ########.fr       */
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

int		main(int argc, char *argv[])
{
	t_ants	*antlist;
	t_map	*map;
	char	*line;

	if (argc > 2)
	{
		ft_putstr("Invalid number of inputs");
		return (2);
	}
	map = (t_map *)malloc(sizeof(t_map));
	init(&map);
	if (argc == 2 && !ft_strcmp("-v", argv[1]))
		map->visual = 1;
	antlist = NULL;
	if (!(antlist = lm_parse_map(&map, argv, antlist)))
		lm_error("ERROR", "No ants", *map);
	if (!map->start)
		lm_error("ERROR", "No rooms", *map);
	lm_calcpoints(map);
	ft_printf("%d\n", map->all_count);
	lm_printrooms(map);
	lm_printtunnels(map->tunnels);
	while (map->end->ant_count != map->all_count)
		lm_find_next_path(*map, antlist);
	return (0);
}
