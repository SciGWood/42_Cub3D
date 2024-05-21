/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:08:38 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 10:47:20 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free_if_null(t_data *data)
{
	if (data->no == 0)
		data->text_tab[0] = ft_strdup("Free");
	if (data->so == 0)
		data->text_tab[1] = ft_strdup("Free");
	if (data->we == 0)
		data->text_tab[2] = ft_strdup("Free");
	if (data->ea == 0)
		data->text_tab[3] = ft_strdup("Free");
}

int	first_last_line(t_data *data, size_t cur_line)
{
	int	i;

	i = 0;
	if (data->scene[cur_line][0] == '0')
		return (1);
	while (data->scene[cur_line][i])
	{
		if (data->scene[cur_line][i] != '1'
			&& data->scene[cur_line][i] != ' '
			&& data->scene[cur_line][i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	other_line_2(t_data *data, size_t line, int i)
{
	if ((!data->scene[line - 1][i - 1] || data->scene[line - 1][i - 1] == ' ')
	|| (!data->scene[line - 1][i + 1] || data->scene[line - 1][i + 1] == ' ')
	|| (!data->scene[line + 1][i - 1] || data->scene[line + 1][i - 1] == ' ')
	|| (!data->scene[line + 1][i + 1] || data->scene[line + 1][i + 1] == ' '))
		return (1);
	return (0);
}

int	other_line(t_data *data, size_t line)
{
	int	i;

	i = 0;
	if (ft_strchr("0NSEWD", data->scene[line][0]))
		return (1);
	while (data->scene[line][i])
	{
		if (ft_strchr("0NSEWD", data->scene[line][i]))
		{
			if ((!data->scene[line][i + 1] || data->scene[line][i + 1] == ' ')
			|| (!data->scene[line][i - 1] || data->scene[line][i - 1] == ' ')
			|| (!data->scene[line - 1][i] || data->scene[line - 1][i] == ' ')
			|| (!data->scene[line + 1][i] || data->scene[line + 1][i] == ' '))
				return (1);
			if (other_line_2(data, line, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_walls(t_data *data)
{
	size_t	cur_line;

	cur_line = 0;
	while (data->scene[cur_line])
	{
		if (cur_line == 0 || cur_line == (count_line_tab(data->scene) - 1))
		{
			if (first_last_line(data, cur_line))
				return (1);
		}
		else
		{
			if (other_line(data, cur_line))
				return (1);
		}
		cur_line++;
	}
	return (0);
}
