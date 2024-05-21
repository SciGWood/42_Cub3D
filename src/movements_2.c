/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:30:28 by gdetourn          #+#    #+#             */
/*   Updated: 2024/05/16 10:57:01 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_rotate_left(t_data *data)
{
	data->player.angle -= 0.04;
	if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
}

void	ft_rotate_right(t_data *data)
{
	data->player.angle += 0.04;
	if (data->player.angle > 2 * M_PI)
		data->player.angle -= 2 * M_PI;
}

void	ft_init_keys(t_data *data)
{
	data->key.left = 0;
	data->key.right = 0;
	data->key.a = 0;
	data->key.d = 0;
	data->key.s = 0;
	data->key.w = 0;
	data->key.space = 0;
}

void	floor_is_open_door(t_data *data)
{
	int	x;
	int	y;

	x = floor(data->player.px_x / SQUARE_SIZE);
	y = floor(data->player.px_y / SQUARE_SIZE);
	if (data->scene[y][x] == 'O')
		data->pass_door = 1;
}

void	ft_close_door(t_data *data)
{
	int	x;
	int	y;

	x = floor(data->player.px_x / SQUARE_SIZE);
	y = floor(data->player.px_y / SQUARE_SIZE);
	if (data->scene[y - 1][x] == 'O' && data->pass_door)
	{
		data->scene[y - 1][x] = 'D';
		data->pass_door = 0;
	}
	else if (data->scene[y + 1][x] == 'O' && data->pass_door)
	{
		data->scene[y + 1][x] = 'D';
		data->pass_door = 0;
	}
	else if (data->scene[y][x - 1] == 'O' && data->pass_door)
	{
		data->scene[y][x - 1] = 'D';
		data->pass_door = 0;
	}
	else if (data->scene[y][x + 1] == 'O' && data->pass_door)
	{
		data->scene[y][x + 1] = 'D';
		data->pass_door = 0;
	}
}
