/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_door_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:43:13 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 15:59:23 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	get_door_x(t_data *data)
{
	if (data->ray.flag == 1)
		data->text_x = fmodf(data->h_x, SQUARE_SIZE);
	else
		data->text_x = fmodf(data->v_y, SQUARE_SIZE);
}

void	draw_door(t_data *data, int ray, int t_pix, int b_pix)
{
	double	step;
	double	text_pos_y;

	step = SQUARE_SIZE / data->wall_h;
	text_pos_y = (t_pix - SCREEN_HEIGHT / 2 + data->wall_h / 2) * step;
	get_door_x(data);
	while (t_pix < b_pix)
	{
		data->text_y = text_pos_y;
		data->color = data->door[0][SQUARE_SIZE * data->text_y + data->text_x];
		text_pos_y += step;
		if (data->ray.flag == 0)
			data->color = (data->color >> 1) & 8355711;
		ft_place_pixel(data, ray, t_pix, data->color);
		t_pix++;
	}
}

void	render_door(t_data *data, int ray)
{
	double	b_pix;
	double	t_pix;

	data->ray.distance *= cos(nor_angle(data->ray.ray_ngl
				- data->player.angle));
	data->wall_h = (SQUARE_SIZE / data->ray.distance)
		* ((SCREEN_WIDTH / 2) / tan(data->player.fov_rd / 2));
	b_pix = (SCREEN_HEIGHT / 2) + (data->wall_h / 2);
	t_pix = (SCREEN_HEIGHT / 2) - (data->wall_h / 2);
	if (b_pix > SCREEN_HEIGHT)
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	draw_door(data, ray, t_pix, b_pix);
}

void	ft_open_door(t_data *data)
{
	int	x;
	int	y;

	x = floor(data->player.px_x / SQUARE_SIZE);
	y = floor(data->player.px_y / SQUARE_SIZE);
	if (data->scene[y - 1][x] == 'D')
		data->scene[y - 1][x] = 'O';
	else if (data->scene[y + 1][x] == 'D')
		data->scene[y + 1][x] = 'O';
	else if (data->scene[y][x - 1] == 'D')
		data->scene[y][x - 1] = 'O';
	else if (data->scene[y][x + 1] == 'D')
		data->scene[y][x + 1] = 'O';
}

void	init_door(t_data *data)
{
	int		y;
	int		x;
	t_door	*newdoor;

	y = 0;
	newdoor = NULL;
	while (data->scene[y])
	{
		x = 0;
		while (data->scene[y][x])
		{
			if (data->scene[y][x] == 'D')
			{
				newdoor = new_door(x * SQUARE_SIZE, y * SQUARE_SIZE);
				add_door(&data->doorlist, newdoor);
			}
			x++;
		}
		y++;
	}
}
