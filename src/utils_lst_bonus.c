/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:03:49 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 16:00:19 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_door	*new_door(double x, double y)
{
	t_door	*newdoor;

	newdoor = (t_door *)malloc(sizeof(*newdoor));
	if (!newdoor)
		return (NULL);
	newdoor->x = x;
	newdoor->y = y;
	newdoor->next = NULL;
	return (newdoor);
}

void	add_door(t_door **doorlist, t_door *newdoor)
{
	if (!newdoor)
		return ;
	newdoor->next = *doorlist;
	*doorlist = newdoor;
}

void	clear_list(t_door *doorlist)
{
	t_door	*current;
	t_door	*futur;

	current = doorlist;
	if (!doorlist)
		return ;
	while (current)
	{
		futur = current->next;
		free(current);
		current = futur;
	}
	doorlist = NULL;
}
