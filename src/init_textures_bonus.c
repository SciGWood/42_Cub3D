/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:48:54 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 16:16:56 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	fill_door_array(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->text_door[0].height)
	{
		x = 0;
		while (x < data->text_door[0].width)
		{
			data->door[0][data->text_door[0].height * y + x] = \
				(data->text_door[0].address[data->text_door[0].height * y + x]);
			x++;
		}
		y++;
	}	
}

void	get_text_door_addr(t_data *data)
{
	data->text_door[0].pt_img = mlx_xpm_file_to_image(data->mlx, \
						D1_PATH, &(data->text_door[0].width), \
						&(data->text_door[0].height));
	if (!data->text_door[0].pt_img)
		print_error("Fail to load texture 0", data);
	data->text_door[0].address = \
		(int *)mlx_get_data_addr(data->text_door[0].pt_img, \
		&data->text_door[0].bits_per_pixel, &data->text_door[0].size_line, \
		&data->text_door[0].endian);
	if (!data->text_door[0].address)
		print_error("Fail to load texture addr", data);
	fill_door_array(data);
	mlx_destroy_image(data->mlx, data->text_door[0].pt_img);
}

void	texture_init_door(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->img_t[i].width = SQUARE_SIZE;
		data->img_t[i].height = SQUARE_SIZE;
		i++;
	}
	extract_textures(data, argv[1]);
	data->text_door[0].width = SQUARE_SIZE;
	data->text_door[0].height = SQUARE_SIZE;
	get_text_door_addr(data);
}
