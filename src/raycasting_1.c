/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:11:17 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 11:04:11 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	wall_hit(t_data *data, float x, float y)
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
	}
	return (0);
}

double	dist_ray(t_data *data, float x, float y)
{
	double	dif_x;
	double	dif_y;

	dif_x = x - data->player.px_x;
	dif_y = y - data->player.px_y;
	return (sqrt(pow(dif_x, 2) + pow(dif_y, 2)));
}

double	get_dist_h_inter(t_data *data, float angle)
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
	while (!wall_hit(data, h_x, h_y - pixel))
	{
		h_x += x_step;
		h_y += y_step;
	}
	data->h_x = h_x;
	return (dist_ray(data, h_x, h_y));
}

double	get_dist_v_inter(t_data *data, float angle)
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
	while (!wall_hit(data, v_x - pixel, v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	data->v_y = v_y;
	return (dist_ray(data, v_x, v_y));
}

void	raycasting(t_data *data)
{
	double	dist_h_inter;
	double	dist_v_inter;
	int		ray;

	ray = -1;
	data->ray.ray_ngl = data->player.angle - (data->player.fov_rd / 2);
	while (ray++ < SCREEN_WIDTH)
	{
		dist_h_inter = get_dist_h_inter(data, data->ray.ray_ngl);
		dist_v_inter = get_dist_v_inter(data, data->ray.ray_ngl);
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
		if (!data->ray.is_door)
			render_wall(data, ray);
		data->ray.is_door = 0;
		data->ray.ray_ngl += (data->player.fov_rd / SCREEN_WIDTH);
	}
}
