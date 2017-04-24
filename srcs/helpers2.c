/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 18:56:01 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/23 18:56:49 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*get_lnkname1(char *str, char **ptr)
{
	char	*name1;

	*ptr = ft_strchr(str, '-');
	name1 = ft_strsub(str, 0, *ptr - str);
	return (name1);
}

char	*get_lnkname2(char *str, char **ptr)
{
	char	*start;
	char	*name2;

	start = (*ptr) + 1;
	while (**ptr)
		(*ptr)++;
	name2 = ft_strsub(str, start - str, (*ptr) - start);
	return (name2);
}
