/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:58:24 by yurwang           #+#    #+#             */
/*   Updated: 2025/08/12 20:16:26 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_atan2(double y, double x)
{
	double	angle;

	angle = -atan2(y, x);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

double	to_rad(double degrees)
{
	return (degrees * PI / 180.0);
}

double	ft_tan(double ray_angle)
{
	double	t;

	t = tan(ray_angle);
	if (t > -TAN_EPS && t < TAN_EPS)
	{
		if (t >= 0)
			t = TAN_EPS;
		else
			t = -TAN_EPS;
	}
	return (t);
}

int	hit_horizontal_wall(t_data *data, double x, double y)
{
	int	tile_x;
	int	tile_y;

	if (data->ray.is_facing_down == 0)
		y -= EPS;
	else
		y += EPS;
	tile_x = (int)floor(x / (double)TILE_SIZE);
	tile_y = (int)floor(y / (double)TILE_SIZE);
	if (tile_x < 0 || tile_x >= data->map.max_width || \
		tile_y < 0 || tile_y >= data->map.max_height)
		return (1);
	return (data->map.dup_map[tile_y][tile_x] == '1');
}

int	hit_vertical_wall(t_data *data, double x, double y)
{
	int	tile_x;
	int	tile_y;

	if (data->ray.is_facing_right == 0)
		x -= EPS;
	else
		x += EPS;
	tile_x = (int)floor(x / (double)TILE_SIZE);
	tile_y = (int)floor(y / (double)TILE_SIZE);
	if (tile_x < 0 || tile_x >= data->map.max_width || \
		tile_y < 0 || tile_y >= data->map.max_height)
		return (1);
	return (data->map.dup_map[tile_y][tile_x] == '1');
}
