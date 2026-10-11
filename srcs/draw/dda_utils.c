/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:17:49 by yurwang           #+#    #+#             */
/*   Updated: 2025/08/31 14:17:51 by yurwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	protect(double a)
{
	if (a > 1000000)
		a = 1000000;
	if (a < -1000000)
		a = -1000000;
}

double	correct_xstep_sign(t_data *d, double xstep)
{
	if ((!d->ray.is_facing_right && xstep > 0) || \
		(d->ray.is_facing_right && xstep < 0))
		xstep *= -1;
	return (xstep);
}

double	correct_ystep_sign(t_data *d, double ystep)
{
	if ((!d->ray.is_facing_down && ystep > 0) || \
		(d->ray.is_facing_down && ystep < 0))
		ystep *= -1;
	protect(ystep);
	return (ystep);
}

void	calculate_wall(double perp, t_data *data)
{
	int		line_height;
	double	dist_proj_plane;

	dist_proj_plane = (W / 2.0) / tan(to_rad(FOV_ANGLE) / 2.0);
	line_height = (int)((TILE_SIZE / perp) * dist_proj_plane + 0.5);
	data->wall.height = line_height;
	data->wall.top = (H - line_height) / 2;
	data->wall.bottom = data->wall.top + line_height;
}

void	cast_hits(t_data *data, double ray_angle)
{
	double	temp_hor_x;
	double	temp_hor_y;

	horizontal_hit(data, ray_angle, 0.0, 0.0);
	temp_hor_x = data->ray.intercept_x;
	temp_hor_y = data->ray.intercept_y;
	vertical_hit(data, ray_angle, 0.0, 0.0);
	choose_nearest_hit_dist(data, temp_hor_x, temp_hor_y);
}
