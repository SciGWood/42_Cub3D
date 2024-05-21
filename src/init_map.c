/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:10:28 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 15:07:09 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_map(char *line)
{
	if (ft_isalpha(line[0]) && ft_isalpha(line[1]))
		return (0);
	else if (ft_isalpha(line[0]) && line[1] == ' ')
		return (0);
	else if (line[0] == '\n')
		return (0);
	return (1);
}

int	count_line_map(t_data *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (is_map(line))
			data->line_nb++;
		free(line);
	}
	close(fd);
	if (data->line_nb == 0)
		data->scene = (char **)ft_calloc(1, sizeof(char *));
	else
		data->scene = (char **)malloc((data->line_nb + 1) * sizeof(char *));
	return (data->line_nb);
}

void	find_lgst_line(t_data *data, char *file)
{
	int		fd;
	char	*line;
	size_t	len_cur_line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (!is_map(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (1)
	{
		if (line == NULL)
			break ;
		len_cur_line = ft_strlen(line);
		if (data->lgst_line < len_cur_line)
			data->lgst_line = len_cur_line;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	fill_in_map(t_data *data, int fd, char *cur_line)
{
	int		i;
	size_t	j;
	char	*line;

	i = 0;
	line = ft_strdup(cur_line);
	while (i < data->line_nb)
	{
		if (line == NULL)
			break ;
		data->scene[i] = ft_calloc(data->lgst_line + 1, sizeof(char));
		j = 0;
		while (j < ft_strlen(line))
		{
			data->scene[i][j] = line[j];
			if (data->scene[i][j] == '\n')
				data->scene[i][j] = '\0';
			j++;
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	data->scene[i] = NULL;
}

int	extract_map(t_data *data, char *file)
{
	int		fd;
	char	*line;

	if (!count_line_map(data, file))
		print_error("Map missing or file empty", data);
	else
	{
		find_lgst_line(data, file);
		fd = open(file, O_RDONLY);
		line = get_next_line(fd);
		while (!is_map(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		fill_in_map(data, fd, line);
		free(line);
		get_next_line(42);
		close(fd);
	}
	return (0);
}
