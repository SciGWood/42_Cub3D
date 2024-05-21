/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:10:38 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 16:17:11 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	init_angle(t_data *data, char dir)
{
	if (dir == 'S')
		data->player.angle = M_PI / 2;
	else if (dir == 'N')
		data->player.angle = 3 * M_PI / 2;
	else if (dir == 'W')
		data->player.angle = M_PI;
	else if (dir == 'E')
		data->player.angle = 0;
}

void	init_player(t_data *data)
{
	int		y;
	int		x;

	y = 0;
	while (data->scene[y])
	{
		x = 0;
		while (data->scene[y][x])
		{
			if (ft_strchr("NSEW", data->scene[y][x]))
			{
				data->player.map_x = x;
				data->player.map_y = y;
				data->player.px_x = x * SQUARE_SIZE + SQUARE_SIZE / 2;
				data->player.px_y = y * SQUARE_SIZE + SQUARE_SIZE / 2;
				data->player.fov_rd = (FOV * M_PI) / 180;
				init_angle(data, data->scene[y][x]);
			}
			x++;
		}
		y++;
	}
}

void	ft_fill_wall_array(t_data *data, int i)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->img_t[i].height)
	{
		x = 0;
		while (x < data->img_t[i].width)
		{
			data->wall[i][data->img_t[i].height * y + x] = \
				(data->img_t[i].address[data->img_t[i].height * y + x]);
			x++;
		}
		y++;
	}
}

void	extract_textures(t_data *data, char *file)
{
	int		i;

	i = 0;
	if (check_scene_infos(data, file))
	{
		ft_free_if_null(data);
		print_error("Scene details are not correct", data);
	}
	while (i < 4)
	{
		data->img_t[i].pt_img = mlx_xpm_file_to_image(data->mlx, \
						data->text_tab[i], &(data->img_t[i].width), \
						&(data->img_t[i].height));
		if (!data->img_t[i].pt_img)
			print_error("Fail to load texture", data);
		data->img_t[i].address = (int *)mlx_get_data_addr(
				data->img_t[i].pt_img, \
				&data->img_t[i].bits_per_pixel, &data->img_t[i].size_line, \
				&data->img_t[i].endian);
		if (!data->img_t[i].address)
			print_error("Fail to load texture", data);
		ft_fill_wall_array(data, i);
		mlx_destroy_image(data->mlx, data->img_t[i].pt_img);
		i++;
	}
}

void	data_init(t_data *data, char **argv)
{
	ft_init_keys(data);
	data->lgst_line = 0;
	data->line_nb = 0;
	data->text_tab = NULL;
	data->no = 0;
	data->so = 0;
	data->we = 0;
	data->ea = 0;
	data->f = 0;
	data->c = 0;
	data->doorlist = NULL;
	if (!extract_map(data, argv[1]))
	{
		init_player(data);
		init_door(data);
	}
	texture_init_door(data, argv);
	data->ray.ray_ngl = 0.0000;
	data->ray.distance = 0.0000;
	data->ray.flag = 0;
	data->ray.is_door = 0;
	data->pass_door = 0;
}
