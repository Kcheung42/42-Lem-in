/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:42:09 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/07 21:10:55 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	handle_comment(t_map **map, int *flag, char *str)
{
	if (!ft_strcmp(str, "##start"))
	{
		if (*flag != 0)
			lm_error("ERROR", "End Input not a room", **map);
		if ((*map)->begin)
			lm_error("ERROR", "Duplicate Start", **map);
		*flag = 1;
	}
	else if (!ft_strcmp(str, "##end"))
	{
		if (*flag != 0)
			lm_error("ERROR", "End input not room", **map);
		if ((*map)->end)
			lm_error("ERROR", "Duplicate End Command", **map);
		*flag = -1;
	}
}

void	lm_init_ants(t_map **map, int count, t_ants *list)
{
	int i;

	i = 0;
	while (i < count)
	{
		list[i].num = i + 1;
		list[i].score = 0;
		list[i].room = (*map)->start;
		i++;
	}
}

void	lm_error(char *str, char *detail, t_map map)
{
	if (!map.visual)
	{
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		ft_putstr_fd(str, 2);
		ft_putchar(':');
		ft_putstr_fd(detail, 2);
		ft_putchar('\n');
	}
	exit(-1);
}

t_ants	*lm_parse_map(t_map **map, t_ants *list)
{
	char	*line;
	int		comment_flag;

	comment_flag = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (!(list) && ((*map)->all_count = ft_atoi(line)) && !comment_flag)
			list = (t_ants *)malloc(sizeof(t_ants) * (*map)->all_count);
		else if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			handle_comment(map, &comment_flag, line);
		else if (line[0] != '#' && line[0] != 'L' && ft_strchr(line, ' ') &&
				!ft_strchr(line, '-'))
			is_room(line, map, &comment_flag);
		else if (line[0] != '#' && line[0] != 'L' && ft_strchr(line, '-') &&
				!ft_strchr(line, ' '))
			is_link(line, map);
		else if (line[0] == '#')
			;
		else
			lm_error("ERROR", "Non Complient Line", **map);
		free(line);
	}
	lm_init_ants(map, (*map)->all_count, list);
	return (list);
}
