/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:24:22 by tordner           #+#    #+#             */
/*   Updated: 2025/08/13 20:33:39 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_dir(char c, t_data *data)
{
	if (c == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
	}
	if (c == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
	}
	if (c == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
	}
	if (c == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
	}
	return ;
}

void	get_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map.dup_map[i])
	{
		j = 0;
		while (data->map.dup_map[i][j])
		{
			if (is_spawn(data->map.dup_map[i][j]))
			{
				data->player.pos_x = (double)j + 0.5;
				data->player.pos_y = (double)i + 0.5;
				get_player_dir(data->map.dup_map[i][j], data);
			}
			j++;
		}
		i++;
	}
	return ;
}

void	get_map_infos(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	while (data->map.dup_map[i])
	{
		len = 0;
		while (data->map.dup_map[i][len])
			len++;
		if (len > data->map.max_width)
			data->map.max_width = len;
		data->map.max_height++;
		i++;
	}
}
