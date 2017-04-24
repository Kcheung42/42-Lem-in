/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 18:40:07 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/23 18:56:47 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*get_rmname(char *str, char **ptr)
{
	char	*name1;

	*ptr = ft_strchr(str, ' ');
	name1 = ft_strsub(str, 0, *ptr - str);
	return (name1);
}

char	*get_xcoord(char *str, char **ptr, t_map **map)
{
	char	*start;
	char	*xcoord;

	(*ptr)++;
	start = (*ptr);
	if (!((*ptr) = ft_strchr((*ptr), ' ')))
		lm_error("ERROR", "room format", **map);
	xcoord = ft_strsub(str, start - str, (*ptr) - start);
	return (xcoord);
}

char	*get_ycoord(char *str, char **ptr)
{
	char	*start;
	char	*ycoord;

	start = (*ptr) + 1;
	while (**ptr)
		(*ptr)++;
	ycoord = ft_strsub(str, start - str, (*ptr) - start);
	return (ycoord);
}
