/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:52:58 by yurwang           #+#    #+#             */
/*   Updated: 2025/08/12 21:02:03 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_horizontal_hit(t_data *d, double xstep, double ystep)
{
	while (d->ray.intercept_x >= 0 && \
		d->ray.intercept_x < d->map.max_width * TILE_SIZE && \
		d->ray.intercept_y >= 0 && \
		d->ray.intercept_y < d->map.max_height * TILE_SIZE)
	{
		if (hit_horizontal_wall(d, d->ray.intercept_x, d->ray.intercept_y))
		{
			d->ray.wallhit_x = d->ray.intercept_x;
			d->ray.wallhit_y = d->ray.intercept_y;
			d->ray.wallhit_side = 0;
			d->ray.wallhit_hor_dist = hypot(d->ray.wallhit_x - \
					d->player.pos_x * (double)TILE_SIZE,
					d->ray.wallhit_y - d->player.pos_y * (double)TILE_SIZE);
			return ;
		}
		d->ray.intercept_x += xstep;
		d->ray.intercept_y += ystep;
	}
	d->ray.wallhit_x = d->player.pos_x * TILE_SIZE;
	d->ray.wallhit_y = d->player.pos_y * TILE_SIZE;
	d->ray.wallhit_hor_dist = INF_DIST;
}

void	find_vertical_hit(t_data *data, double xstep, double ystep)
{
	while (data->ray.intercept_x >= 0 && \
		data->ray.intercept_x < data->map.max_width * TILE_SIZE && \
		data->ray.intercept_y >= 0 && \
		data->ray.intercept_y < data->map.max_height * TILE_SIZE)
	{
		if (hit_vertical_wall(data, data->ray.intercept_x, \
				data->ray.intercept_y))
		{
			data->ray.wallhit_x = data->ray.intercept_x;
			data->ray.wallhit_y = data->ray.intercept_y;
			data->ray.wallhit_side = 1;
			data->ray.wallhit_ver_dist = hypot(data->ray.wallhit_x - \
				data->player.pos_x * (double)TILE_SIZE,
					data->ray.wallhit_y - data->player.pos_y
					* (double)TILE_SIZE);
			return ;
		}
		data->ray.intercept_x += xstep;
		data->ray.intercept_y += ystep;
	}
	data->ray.wallhit_x = data->player.pos_x * (double)TILE_SIZE;
	data->ray.wallhit_y = data->player.pos_y * (double)TILE_SIZE;
	data->ray.wallhit_ver_dist = INF_DIST;
}

void	horizontal_hit(t_data *d, double ray_angle, double xstep, double ystep)
{
	double	cot_angle;

	if (fabs(cos(ray_angle)) > 0.99999)
	{
		d->ray.wallhit_x = d->player.pos_x * (double)TILE_SIZE;
		d->ray.wallhit_y = d->player.pos_y * (double)TILE_SIZE;
		d->ray.wallhit_hor_dist = INF_DIST;
		return ;
	}
	cot_angle = 1.0 / ft_tan(ray_angle);
	protect(cot_angle);
	if (d->ray.is_facing_down)
		d->ray.intercept_y = floor(d->player.pos_y) * TILE_SIZE + TILE_SIZE;
	else
		d->ray.intercept_y = floor(d->player.pos_y) * TILE_SIZE - 0.0001;
	d->ray.intercept_x = d->player.pos_x * TILE_SIZE + \
		(d->ray.intercept_y - d->player.pos_y * TILE_SIZE) * cot_angle;
	ystep = TILE_SIZE;
	if (!d->ray.is_facing_down)
		ystep = -TILE_SIZE;
	xstep = TILE_SIZE * cot_angle;
	xstep = correct_xstep_sign(d, xstep);
	protect(xstep);
	find_horizontal_hit(d, xstep, ystep);
}

void	set_vertical_default_values(t_data *d)
{
	d->ray.wallhit_x = d->player.pos_x * (double)TILE_SIZE;
	d->ray.wallhit_y = d->player.pos_y * (double)TILE_SIZE;
	d->ray.wallhit_ver_dist = INF_DIST;
	d->ray.intercept_x = d->player.pos_x * TILE_SIZE;
	d->ray.intercept_y = d->player.pos_y * TILE_SIZE;
}

void	vertical_hit(t_data *d, double ray_angle, double xstep, double ystep)
{
	double	tan_angle;

	if (fabs(sin(ray_angle)) > 0.99999)
	{
		set_vertical_default_values(d);
		return ;
	}
	tan_angle = ft_tan(ray_angle);
	protect(tan_angle);
	if (d->ray.is_facing_right)
		d->ray.intercept_x = floor(d->player.pos_x) * TILE_SIZE + TILE_SIZE;
	else
		d->ray.intercept_x = floor(d->player.pos_x) * TILE_SIZE - 0.0001;
	d->ray.intercept_y = d->player.pos_y * TILE_SIZE + \
		(d->ray.intercept_x - d->player.pos_x * TILE_SIZE) * tan_angle;
	xstep = TILE_SIZE;
	if (!d->ray.is_facing_right)
		xstep = -TILE_SIZE;
	ystep = TILE_SIZE * tan_angle;
	ystep = correct_ystep_sign(d, ystep);
	find_vertical_hit(d, xstep, ystep);
}
