#include "lem_in.h"

t_ants	*lm_parse_map(t_map **map, char *argv[])
{
	int		ant_count;
	char	*line;
	t_ants	*ant_list;
	t_rooms	*r_head;
	int		i;
	int		h_flag;
	int		end_flag;

	i = 0;
	ant_list = NULL;
	(*map)->start = NULL;
	while (get_next_line(0, &line ) > 0)
	{
		if (!(ant_list) && (ant_count = ft_atoi(line)))
			ant_list = (t_ants *)malloc(sizeof(t_ants) * ant_count);
		else if (!ft_strcmp(line, "##start"))
		{
			if (h_flag != 0)
			{
				printf("ERROR:End Input not a room\n");
				exit(-1);
			}
			h_flag = 1;
			printf("Start Rooom\n");
		}
		else if (!ft_strcmp(line, "##end"))
		{
			if ((*map)->end || h_flag != 0)
			{
				printf("Error:Duplicate End || Start input not room\n");
				exit(-1);
			}
			h_flag = -1;
			printf("End Rooom\n");
		}
		else if (line[0] != '#' && ft_strchr(line, ' '))
			is_room(line, map, &h_flag);
		else if (line[0] != '#' && ft_strchr(line, '-'))
			is_link(line, map);
		else if (line[0] == '#')
			printf("Unkown Command Ignored\n");
		else
		{
			printf("ERROR:?\n");
			exit(-1);
		}
	}
			while (i < ant_count)
			{
				ant_list[i].num = i + 1;
				ant_list[i].score = 0;
				ant_list[i].room = (*map)->start;
				i++;
			}
	(*map)->all_count = ant_count;
	return(ant_list);
}
