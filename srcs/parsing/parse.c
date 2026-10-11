/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:07:33 by tordner           #+#    #+#             */
/*   Updated: 2025/09/09 19:54:12 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_input(t_data *data, char *file)
{
	int		fd;
	char	buf[2049];
	ssize_t	size;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\ninvalid file, cannot be opened\n"), 1);
	size = read(fd, buf, 2048);
	if (size < 0)
		return (printf("Error\nfailed to read file\n"), 1);
	buf[size] = '\0';
	close(fd);
	data->input = ft_split(buf, '\n');
	return (0);
}

int	check_identifiers(t_data *data)
{
	if (data->c_elem.c_no != 1 || \
		data->c_elem.c_so != 1 || \
		data->c_elem.c_ea != 1 || \
		data->c_elem.c_we != 1 || \
		data->c_elem.c_ceiling != 1 || \
		data->c_elem.c_floor != 1)
	{
		printf("Error\nDuplicate or missing identifier detected.\n");
		return (0);
	}
	if (!validate_texture(data, data->conf.no, "NO") || \
		!validate_texture(data, data->conf.so, "SO") || \
		!validate_texture(data, data->conf.ea, "EA") || \
		!validate_texture(data, data->conf.we, "WE"))
		return (0);
	return (1);
}

int	parse_identifiers(t_data *data)
{
	int	i;

	i = 0;
	if (!handle_map(data))
		return (1);
	while (!is_map_line(data->input[i]))
	{
		if (is_line_empty(data->input[i]))
		{
			i++;
			continue ;
		}
		if (!is_identifier_line(data->input[i]))
		{
			printf("Error\ninvalid line found in input.\n");
			return (1);
		}
		if (!get_identifiers(data, data->input[i]))
			return (1);
		i++;
	}
	if (!check_identifiers(data))
		return (1);
	return (0);
}

int	check_rectangular_map(t_data *data)
{
	int	i;
	int	first_row_length;
	int	current_row_length;

	first_row_length = 0;
	while (data->map.map[0][first_row_length] != '\n'
		&& data->map.map[0][first_row_length] != '\0')
		first_row_length++;
	i = 1;
	while (data->map.map[i])
	{
		current_row_length = 0;
		while (data->map.map[i][current_row_length] != '\n'
			&& data->map.map[i][current_row_length] != '\0')
			current_row_length++;
		if (current_row_length != first_row_length)
			return (printf("Error\nMap is not rectangular\n"), 1);
		i++;
	}
	return (0);
}

int	handle_input(t_data *data, char **av)
{
	if (get_input(data, av[1]))
		return (1);
	if (parse_identifiers(data))
		return (1);
	if (init_flood_fill(data))
		return (1);
	pad_map_with_walls(data->map.dup_map);
	pad_map_with_walls(data->map.map);
	if (check_rectangular_map(data))
		return (1);
	get_player(data);
	get_map_infos(data);
	return (0);
}
