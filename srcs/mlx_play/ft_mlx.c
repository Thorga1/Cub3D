/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:10:33 by tordner           #+#    #+#             */
/*   Updated: 2025/08/13 20:17:25 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key(int key, t_data *data)
{
	if (key == XK_w)
		move_front(data);
	else if (key == XK_s)
		move_back(data);
	else if (key == XK_a)
		move_left(data);
	else if (key == XK_d)
		move_right(data);
	else if (key == XK_Escape)
		ft_exit(data, 0);
	else if (key == XK_Right)
		rotate_right(data);
	else if (key == XK_Left)
		rotate_left(data);
	return (1);
}

void	init_mlx2(t_data *data)
{
	init_texture(data, &data->textures[0], data->conf.no);
	init_texture(data, &data->textures[1], data->conf.so);
	init_texture(data, &data->textures[2], data->conf.ea);
	init_texture(data, &data->textures[3], data->conf.we);
}

void	rotate_right(t_data *data)
{
	double	distance;
	double	theta;
	double	x;
	double	y;

	theta = PI / TURN_ANGLE;
	x = data->player.dir_x;
	y = data->player.dir_y;
	data->player.dir_x = x * cos(theta) - y * sin(theta);
	data->player.dir_y = x * sin(theta) + y * cos(theta);
	distance = hypot(data->player.dir_x, data->player.dir_y);
	data->player.dir_y /= distance;
	data->player.dir_x /= distance;
}

void	rotate_left(t_data *data)
{
	double	distance;
	double	theta;
	double	x;
	double	y;

	theta = PI / TURN_ANGLE;
	x = data->player.dir_x;
	y = data->player.dir_y;
	data->player.dir_x = x * cos(-theta) - y * sin(-theta);
	data->player.dir_y = x * sin(-theta) + y * cos(-theta);
	distance = hypot(data->player.dir_x, data->player.dir_y);
	data->player.dir_y /= distance;
	data->player.dir_x /= distance;
}

void	init_mlx(t_data *data)
{
	data->mlx.ptr = mlx_init();
	if (!data->mlx.ptr)
		ft_exit(data, 1);
	data->mlx.win_ptr = mlx_new_window(data->mlx.ptr, W, H, "cub3d");
	if (!data->mlx.win_ptr)
		ft_exit(data, 1);
	data->img.ptr = mlx_new_image(data->mlx.ptr, W, H);
	if (!data->img.ptr)
		ft_exit(data, 1);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp, \
	&data->img.ll, &data->img.endian);
	if (!data->img.addr)
		ft_exit(data, 1);
	init_mlx2(data);
}
