#include "lem_in.h"

int main(int argc, char *argv[])
{
	t_ants	*antlist;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map->start = NULL;
	map->end = NULL;
	map->all_count = 0;
	antlist = NULL;
	/* if(!(antlist = lm_parse_map(&map, argv))) */
	if(!(antlist = lm_parse_map(&map, argv, antlist)))
		lm_error("EROOR:No ants\n");
	/* lm_printrooms(map->start); */
	if (!map->start)
		lm_error("ERROR:No rooms\n");
	lm_calcpoints(map);
	/* lm_printrooms(map->start); */
	while (map->end->ant_count != map->all_count)
		lm_find_next_path(*map, antlist);
	/* lm_printants(antlist, map->all_count); */
	return 0;
}
