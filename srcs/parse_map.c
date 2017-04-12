#include "lem_in.h"


void	handle_comment(t_map **map, int *flag, char *str)
{
	if (!ft_strcmp(str, "##start"))
	{
		if (*flag != 0)
			lm_error("ERROR:End Input not a room\n");
		*flag = 1;
		printf("Start Rooom\n");
	}
	else if (!ft_strcmp(str, "##end"))
	{
		if ((*map)->end || *flag != 0)
			lm_error("ERROR:Duplicate End || Start input not room\n");
		*flag = -1;
		printf("End Rooom\n");
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

void	lm_error(char *str)
{
	ft_printf(str);
	exit(-1);
}

t_ants	*lm_parse_map(t_map **map, char *argv[], t_ants *list)
{
	char	*line;
	int		comment_flag;

	comment_flag = 0;
	while (get_next_line(0, &line ) > 0)
	{
		if (!(list) && ((*map)->all_count = ft_atoi(line)))
			list = (t_ants *)malloc(sizeof(t_ants) * (*map)->all_count);
		else if (!ft_strcmp(line, "##start"))
			handle_comment(map, &comment_flag, "##start");
		else if (!ft_strcmp(line, "##end"))
			handle_comment(map, &comment_flag, "##end");
		else if (line[0] != '#' && ft_strchr(line, ' '))
			is_room(line, map, &comment_flag);
		else if (line[0] != '#' && ft_strchr(line, '-'))
			is_link(line, map);
		else if (line[0] == '#' || line[0] == 'L')
			printf("Unkown Command Ignored\n");
		else
			lm_error("ERROR:?\n");
	}
	lm_init_ants(map, (*map)->all_count, list);
	return(list);
}
