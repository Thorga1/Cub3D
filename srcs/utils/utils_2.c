/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:58:33 by yurwang           #+#    #+#             */
/*   Updated: 2025/08/12 21:07:51 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choose_nearest_hit_dist(t_data *data, double hor_x, double hor_y)
{
	if (data->ray.wallhit_hor_dist <= data->ray.wallhit_ver_dist)
	{
		data->ray.distance = data->ray.wallhit_hor_dist;
		data->ray.wallhit_side = 0;
		data->ray.wallhit_x = hor_x;
		data->ray.wallhit_y = hor_y;
	}
	else
	{
		data->ray.distance = data->ray.wallhit_ver_dist;
		data->ray.wallhit_side = 1;
	}
}

void	texture_hit_x(t_data *data)
{
	if (!data->ray.wallhit_side)
		data->ray.texture_x = (int)data->ray.wallhit_x % TILE_SIZE;
	else
		data->ray.texture_x = (int)data->ray.wallhit_y % TILE_SIZE;
	if (!data->ray.wallhit_side && !data->ray.is_facing_down)
		data->ray.texture_x = TILE_SIZE - data->ray.texture_x - 1;
	if (data->ray.wallhit_side && !data->ray.is_facing_right)
		data->ray.texture_x = TILE_SIZE - data->ray.texture_x - 1;
	if (data->ray.texture_x < 0)
		data->ray.texture_x = 0;
	else if (data->ray.texture_x >= TILE_SIZE)
		data->ray.texture_x = TILE_SIZE - 1;
}

unsigned int	rgb_to_color(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	init_texture(t_data *data, t_img *tex, char *path)
{
	tex->ptr = mlx_xpm_file_to_image(data->mlx.ptr, path, \
		&tex->width, &tex->height);
	if (!tex->ptr)
		ft_exit(data, 1);
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, \
		&tex->ll, &tex->endian);
	if (!tex->addr)
		ft_exit(data, 1);
}
