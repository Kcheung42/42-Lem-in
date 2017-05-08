/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:48:04 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/07 20:29:06 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_ants
{
	int				num;
	int				score;
	struct s_rooms	*room;
}				t_ants;

typedef	struct	s_tunnels
{
	struct s_rooms		*entrance;
	struct s_rooms		*exit;
	struct s_tunnels	*next;
}				t_tunnels;

typedef struct	s_rooms
{
	char				*name;
	int					occupied;
	int					ant_count;
	int					points;
	int					x_coord;
	int					y_coord;
	int					marked;
	struct s_rooms		*next;
	struct s_tunnels	*tun_list;
}				t_rooms;

typedef	struct	s_map
{
	struct s_rooms		*end;
	struct s_rooms		*start;
	struct s_rooms		*begin;
	struct s_tunnels	*tunnels;
	int					all_count;
	int					valid;
	int					visual;
}				t_map;

t_rooms			*lm_newroom(char *name, int x, int y);
void			lm_addroom(t_map **map, char *name, int *coord, int *flag);
int				is_room(char *str, t_map **map, int *flag);

t_tunnels		*lm_newtun(t_rooms *ent, t_rooms *ext);
t_tunnels		*lm_addtun(t_rooms *entrance, t_rooms *exit);
int				is_link(char *str, t_map **map);

t_ants			*lm_parse_map(t_map **map, t_ants *list);

void			lm_printtunnels(t_tunnels *head);
void			lm_printrooms(t_map *map);
void			lm_printants(t_ants *list, int count);

int				lm_all_scored(t_rooms *room);
void			lm_calcpoints_r(t_rooms *prev, t_rooms *room, int pts);
void			lm_calcpoints(t_map *map);
void			lm_move_ants(t_map map, t_ants *ants, int i, t_rooms *to_move);
void			lm_find_next_path(t_map map, t_ants *ants);
int				lm_all_crawled(t_rooms *room);
void			lm_valid_path(t_map *maps, t_rooms *prev, t_rooms *room);
void			lm_error(char *str, char *detail, t_map map);
char			*get_lnkname1(char *str, char **ptr);
char			*get_lnkname2(char *str, char **ptr);
char			*get_rmname(char *str, char **ptr);
char			*get_xcoord(char *str, char **ptr, t_map **map);
char			*get_ycoord(char *str, char **ptr);
void			print_map(t_map *map);
#endif
