#include "lem_in.h"

int main(int argc, char *argv[])
{
	t_ants	*array;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map->start = NULL;
	map->end = NULL;
	map->all_count = 0;
	array = lm_parse_map(&map, argv);
	/* lm_printrooms(map->start); */
	if (!map->start)
	{
		printf("ERROR:No rooms\n");
		exit(-1);
	}
	lm_calcpoints(map);
	/* lm_printrooms(map->start); */
	while (map->end->ant_count != map->all_count)
		lm_find_next_path(*map, array);
	/* lm_printants(array, map->all_count); */
	ft_printf("End\n");
	return 0;
}
