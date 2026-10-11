/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:43:22 by tordner           #+#    #+#             */
/*   Updated: 2025/09/09 19:47:10 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_map_start(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (is_map_line(input[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	count_map_lines(char **input, int start)
{
	int	count;

	count = 0;
	while (input[start + count] && is_map_line(input[start + count]))
		count++;
	return (count);
}

char	**extract_map(char **input, int start)
{
	int		map_lines;
	char	**map;
	int		i;

	map_lines = count_map_lines(input, start);
	map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < map_lines)
	{
		map[i] = ft_strdup(input[start + i]);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	handle_map(t_data *data)
{
	int	map_start;

	map_start = find_map_start(data->input);
	if (map_start == -1)
	{
		printf("Error\nPlease provide a map in your .cub file.\n");
		return (0);
	}
	data->map.map = extract_map(data->input, map_start);
	if (!data->map.map)
		return (0);
	data->map.dup_map = extract_map(data->input, map_start);
	if (!data->map.dup_map)
		return (0);
	return (1);
}
