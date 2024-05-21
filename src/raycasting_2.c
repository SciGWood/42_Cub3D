/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:11:02 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 10:58:51 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	dir_step_first(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += SQUARE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > (M_PI / 2) && angle < (3 * M_PI / 2)))
		{
			*inter += SQUARE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	dir_step_second(float angle, int is_horizon)
{
	if (is_horizon)
	{
		if ((angle > (M_PI / 2) && angle < (3 * M_PI / 2)))
			return (1);
	}
	else
	{
		if ((angle > 0 && angle < M_PI))
			return (1);
	}
	return (0);
}
