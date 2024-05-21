/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_door_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:39:02 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 16:00:13 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	find_door(t_data *data)
{
	t_door	*cur;

	cur = data->doorlist;
	while (cur)
	{
		if (data->ray.flag == 1
			&& (data->h_x >= cur->x && data->h_x <= cur->x + SQUARE_SIZE)
			&& (data->h_y >= cur->y && data->h_y <= cur->y + SQUARE_SIZE))
			return (1);
		else if (data->ray.flag == 0
			&& (data->v_x >= cur->x && data->v_x <= cur->x + SQUARE_SIZE)
			&& (data->v_y >= cur->y && data->v_y <= cur->y + SQUARE_SIZE))
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	door_hit(t_data *data, float x, float y)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (1);
	x_m = floor(x / SQUARE_SIZE);
	y_m = floor(y / SQUARE_SIZE);
	if (y_m >= data->line_nb || x_m >= (int)ft_strlen(data->scene[y_m]))
		return (1);
	if (data->scene[y_m] && x_m <= (int)ft_strlen(data->scene[y_m]))
	{
		if (data->scene[y_m][x_m] == '1')
			return (1);
		else if (data->scene[y_m][x_m] == 'D')
		{
			data->ray.is_door = 1;
			return (1);
		}
	}
	return (0);
}

double	get_dist_h_inter_door(t_data *data, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = SQUARE_SIZE;
	x_step = SQUARE_SIZE / tan(angle);
	h_y = floor(data->player.px_y / SQUARE_SIZE) * SQUARE_SIZE;
	pixel = dir_step_first(angle, &h_y, &y_step, 1);
	h_x = data->player.px_x + (h_y - data->player.px_y) / tan(angle);
	if ((dir_step_second(angle, 1) && x_step > 0)
		|| (!dir_step_second(angle, 1) && x_step < 0))
		x_step *= -1;
	while (!door_hit(data, h_x, h_y - pixel))
	{
		h_x += x_step;
		h_y += y_step;
	}
	data->h_x = h_x;
	data->h_y = h_y;
	return (dist_ray(data, h_x, h_y));
}

double	get_dist_v_inter_door(t_data *data, float angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = SQUARE_SIZE;
	y_step = SQUARE_SIZE * tan(angle);
	v_x = floor(data->player.px_x / SQUARE_SIZE) * SQUARE_SIZE;
	pixel = dir_step_first(angle, &v_x, &x_step, 0);
	v_y = data->player.px_y + (v_x - data->player.px_x) * tan(angle);
	if ((dir_step_second(angle, 0) && y_step < 0)
		|| (!dir_step_second(angle, 0) && y_step > 0))
		y_step *= -1;
	while (!door_hit(data, v_x - pixel, v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	data->v_x = v_x;
	data->v_y = v_y;
	return (dist_ray(data, v_x, v_y));
}

void	raycasting_door(t_data *data)
{
	double	dist_h_inter;
	double	dist_v_inter;
	int		ray;

	ray = -1;
	data->ray.ray_ngl = data->player.angle - (data->player.fov_rd / 2);
	while (ray++ < SCREEN_WIDTH)
	{
		dist_h_inter = get_dist_h_inter_door(data, data->ray.ray_ngl);
		dist_v_inter = get_dist_v_inter_door(data, data->ray.ray_ngl);
		if (dist_h_inter <= dist_v_inter)
		{
			data->ray.distance = dist_h_inter;
			data->ray.flag = 1;
		}
		else
		{
			data->ray.distance = dist_v_inter;
			data->ray.flag = 0;
		}
		if (data->ray.is_door && find_door(data))
			render_door(data, ray);
		data->ray.is_door = 0;
		data->ray.ray_ngl += (data->player.fov_rd / SCREEN_WIDTH);
	}
}
