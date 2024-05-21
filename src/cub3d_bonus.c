/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:51:17 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 15:59:03 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*should return an int but exit(0) is required to quit the program properly*/
int	on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	clear_tab(data->scene);
	clear_tab(data->text_tab);
	clear_list(data->doorlist);
	free(data->mlx);
	exit(0);
	return (0);
}

int	on_keyrelease(int keysym, t_data *data)
{
	if (keysym == LEFT)
		data->key.left = 0;
	else if (keysym == RIGHT)
		data->key.right = 0;
	else if (keysym == A)
		data->key.a = 0;
	else if (keysym == D)
		data->key.d = 0;
	else if (keysym == S)
		data->key.s = 0;
	else if (keysym == W)
		data->key.w = 0;
	else if (keysym == SPACE)
		data->key.space = 0;
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == ESC)
	{
		printf("Don't want to play anymore?\n");
		on_destroy(data);
	}
	else if (keysym == LEFT)
		data->key.left = 1;
	else if (keysym == RIGHT)
		data->key.right = 1;
	else if (keysym == A)
		data->key.a = 1;
	else if (keysym == D)
		data->key.d = 1;
	else if (keysym == S)
		data->key.s = 1;
	else if (keysym == W)
		data->key.w = 1;
	else if (keysym == SPACE)
		data->key.space = 1;
	return (0);
}

int	game(t_data *data)
{
	data->img_s.pt_img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->img_s.address = mlx_get_data_addr(data->img_s.pt_img, \
						&data->img_s.bits_per_pixel, &data->img_s.size_line, \
						&data->img_s.endian);
	put_ceiling_and_floor(data);
	raycasting(data);
	raycasting_door(data);
	ft_print_minimap(data);
	ft_movements(data);
	floor_is_open_door(data);
	ft_close_door(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_s.pt_img, 0, 0);
	mlx_destroy_image(data->mlx, data->img_s.pt_img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_error_file(argc, argv))
		exit(1);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data_init(&data, argv);
	check_error_map(&data);
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!data.win)
		return (free(data.mlx), 1);
	mlx_loop_hook(data.mlx, game, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &on_keypress, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &on_keyrelease, &data);
	mlx_hook(data.win, 17, 0, &on_destroy, &data);
	mlx_loop(data.mlx);
	return (0);
}
