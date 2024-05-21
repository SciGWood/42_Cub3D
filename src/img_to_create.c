/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:41:53 by gdetourn          #+#    #+#             */
/*   Updated: 2024/05/16 16:18:03 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_place_pixel(t_data *data, int ray, int y, int color)
{
	char	*distance;

	distance = data->img_s.address + \
			(y * data->img_s.size_line + ray * \
			(data->img_s.bits_per_pixel / 8));
	*(unsigned int *)distance = color;
}

void	ft_pixel(t_data *data, int color, int i, int j)
{
	int	pixel;

	if (color < 0)
		return ;
	pixel = (i * data->img_s.size_line) + (j * 4);
	data->img_s.address[pixel + 3] = 0 >> 24;
	data->img_s.address[pixel + 2] = color >> 16;
	data->img_s.address[pixel + 1] = color >> 8;
	data->img_s.address[pixel + 0] = color >> 0;
}

void	put_ceiling_and_floor(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			if (i < SCREEN_HEIGHT / 2)
				ft_pixel(data, data->ceiling_hex, i, j);
			else
				ft_pixel(data, data->floor_hex, i, j);
			j++;
		}
		i++;
	}
}

void	texture_init(t_data *data, char **argv)
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
}
