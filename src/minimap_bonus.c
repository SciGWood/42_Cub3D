/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:13:16 by gdetourn          #+#    #+#             */
/*   Updated: 2024/05/16 15:59:57 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/* "if" condition with pow is to make a blue point, not a square pixel.
	color player = blue/violet) */
void	ft_put_player(t_data *data)
{
	int	x;
	int	y;

	y = data->mnmap->px_y - data->mnmap->radius;
	while (y <= data->mnmap->px_y + data->mnmap->radius)
	{
		x = data->mnmap->px_x - data->mnmap->radius;
		while (x <= data->mnmap->px_x + data->mnmap->radius)
		{
			if (pow(x - data->mnmap->px_x, 2) + pow(y - data->mnmap->px_y, 2)
				<= pow(data->mnmap->radius, 2))
				ft_pixel(data, 0x3c00ff, y, x);
			x++;
		}
		y++;
	}
}

void	ft_init_minimap_and_player(t_data *data)
{
	t_mnmap	*mnmap;

	mnmap = calloc(1, sizeof(t_mnmap));
	if (!mnmap)
		exit(1);
	data->mnmap = mnmap;
	data->mnmap->width = SCREEN_WIDTH / 30;
	data->mnmap->height = SCREEN_HEIGHT / 30;
	data->mnmap->minixo = SCREEN_WIDTH / 40 * 10;
	data->mnmap->miniyo = SCREEN_HEIGHT / 40 * 10;
	data->mnmap->mapsx = 18;
	data->mnmap->mapsy = data->mnmap->mapsx - 1;
	data->mnmap->radius = 4.5;
	data->mnmap->px_x = data->mnmap->minixo - ((data->mnmap->minixo - \
		data->mnmap->width + 3) / 2);
	data->mnmap->px_y = data->mnmap->miniyo - ((data->mnmap->miniyo - \
		data->mnmap->height + 5) / 2);
}

/* print the BG minimap, walls, spaces, doors and 
	put the player onto the start position.
	Color for background = Yellow */
void	ft_print_minimap(t_data *data)
{
	int	i;
	int	j;

	ft_init_minimap_and_player(data);
	i = data->mnmap->height;
	while (i < data->mnmap->miniyo)
	{
		j = data->mnmap->width;
		while (j < data->mnmap->minixo)
		{
			if (j % 2 == 0 && i % 2 == 0)
				ft_pixel(data, 0xffff00, i, j);
			j++;
		}
		i++;
	}
	ft_walls(data);
	ft_put_player(data);
	free(data->mnmap);
}
