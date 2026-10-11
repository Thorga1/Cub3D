/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:26:33 by tordner           #+#    #+#             */
/*   Updated: 2025/08/12 21:26:50 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_position(t_data *data, double x, double y)
{
	double	buffer;
	int		map_x;
	int		map_y;

	buffer = 0.1;
	map_x = (int)x;
	map_y = (int)y;
	if (x - buffer < 0 || x + buffer >= data->map.max_width || \
		y - buffer < 0 || y + buffer >= data->map.max_height)
		return (0);
	if (data->map.dup_map[(int)(y - buffer)][(int)(x - buffer)] == '1' || \
		data->map.dup_map[(int)(y - buffer)][(int)(x + buffer)] == '1' || \
		data->map.dup_map[(int)(y + buffer)][(int)(x - buffer)] == '1' || \
		data->map.dup_map[(int)(y + buffer)][(int)(x + buffer)] == '1')
		return (0);
	return (1);
}

void	move_front(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * SPEED;
	new_y = data->player.pos_y + data->player.dir_y * SPEED;
	if (is_valid_position(data, new_x, new_y))
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
}

void	move_back(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * SPEED;
	new_y = data->player.pos_y - data->player.dir_y * SPEED;
	if (is_valid_position(data, new_x, new_y))
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_y * SPEED;
	new_y = data->player.pos_y - data->player.dir_x * SPEED;
	if (is_valid_position(data, new_x, new_y))
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_y * SPEED;
	new_y = data->player.pos_y + data->player.dir_x * SPEED;
	if (is_valid_position(data, new_x, new_y))
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
}
