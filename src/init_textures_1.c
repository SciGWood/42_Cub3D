/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:38:25 by gdetourn          #+#    #+#             */
/*   Updated: 2024/05/16 16:38:48 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
//erreur color >256
void	convert_colors(t_data *data, char **color_tab, char c)
{
	unsigned long	tmp;
	int				red;
	int				green;
	int				blue;

	red = 0;
	green = 0;
	blue = 0;
	red = ft_atoi(color_tab[0]);
	green = ft_atoi(color_tab[1]);
	blue = ft_atoi(color_tab[2]);
	if (c == 'F')
	{
		tmp = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
		data->floor_hex = tmp;
	}
	if (c == 'C')
	{
		tmp = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
		data->ceiling_hex = tmp;
	}
}

int	valid_colors(t_data *data, char *line)
{
	char	**color_tab;
	int		i;

	if (line[1] == ' ')
	{
		color_tab = ft_split(ft_strchr(line, line[2]), ',');
		if (!color_tab)
			return (1);
		i = 0;
		while (color_tab[i])
		{
			if (ft_atoi(color_tab[i]) < 0 || 255 < ft_atoi(color_tab[i]))
				return (clear_tab(color_tab), 1);
			i++;
		}
		if (line[0] == 'F')
			data->f++;
		else if (line[0] == 'C')
			data->c++;
		convert_colors(data, color_tab, line[0]);
		clear_tab(color_tab);
	}
	return (0);
}

int	valid_texture_we(t_data *data, char *line, char *dup)
{
	if (line[0] == 'S' && line[1] == 'O')
	{
		if (data->so != 1)
			data->text_tab[1] = ft_strtrim(dup, "\n");
		data->so++;
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if (data->we != 1)
			data->text_tab[2] = ft_strtrim(dup, "\n");
		data->we++;
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (data->ea != 1)
			data->text_tab[3] = ft_strtrim(dup, "\n");
		data->ea++;
	}
	free(dup);
	return (0);
}

int	valid_texture_ns(t_data *data, char *line)
{
	char	**path_tab;
	char	*dup;

	if (line[0] != '\n' && line[2] == ' ' && line[3] == '.'
		&& ((line[0] == 'N' && line[1] == 'O')
			|| (line[0] == 'S' && line[1] == 'O')
			|| (line[0] == 'W' && line[1] == 'E')
			|| (line[0] == 'E' && line[1] == 'A')))
	{
		path_tab = ft_split(line, ' ');
		dup = ft_strdup(path_tab[1]);
		if (line[0] == 'N' && line[1] == 'O')
		{
			if (data->no != 1)
				data->text_tab[0] = ft_strtrim(dup, "\n");
			return (data->no++, free(dup), clear_tab(path_tab), 0);
		}
		else if ((line[0] == 'S' && line[1] == 'O')
			|| (line[0] == 'W' && line[1] == 'E')
			|| (line[0] == 'E' && line[1] == 'A'))
			return (clear_tab(path_tab), valid_texture_we(data, line, dup));
	}
	else if (line[0] == 'F' || line[0] == 'C' || line[0] == '\n')
		return (valid_colors(data, line));
	return (1);
}

int	check_scene_infos(t_data *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = NULL;
	data->text_tab = ft_calloc(5, sizeof(char *));
	if (!data->text_tab)
		return (1);
	while (data->no != 1 || data->so != 1 || data->we != 1 || data->ea != 1
		|| data->f != 1 || data->c != 1)
	{
		line = get_next_line(fd);
		if (valid_texture_ns(data, line) == 1)
		{
			free(line);
			get_next_line(42);
			return (1);
		}
		free(line);
	}
	close(fd);
	get_next_line(42);
	if (ft_tab_size(data->text_tab) != 4 || data->f != 1 || data->c != 1)
		return (1);
	return (0);
}
