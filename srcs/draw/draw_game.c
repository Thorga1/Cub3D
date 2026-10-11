/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:12:35 by yurwang           #+#    #+#             */
/*   Updated: 2025/08/13 20:26:37 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling_and_floor(t_data *data)
{
	unsigned int	ceiling;
	unsigned int	floor;
	int				row;
	int				col;

	row = 0;
	ceiling = rgb_to_color(data->conf.ceiling_rgb[0], \
					data->conf.ceiling_rgb[1], data->conf.ceiling_rgb[2]);
	floor = rgb_to_color(data->conf.floor_rgb[0], \
					data->conf.floor_rgb[1], data->conf.floor_rgb[2]);
	while (row < H)
	{
		col = 0;
		while (col < W)
		{
			if (row < H / 2)
				add_color_to_pixel_via_mlx(&data->img, row, col++, ceiling);
			else
				add_color_to_pixel_via_mlx(&data->img, row, col++, floor);
		}
		row++;
	}
}

void	ray_direction(t_data *data)
{
	if (data->ray.dir_x > 0)
		data->ray.is_facing_right = 1;
	else
		data->ray.is_facing_right = 0;
	if (data->ray.dir_y > 0)
		data->ray.is_facing_down = 1;
	else
		data->ray.is_facing_down = 0;
}

void	rotate_ray(t_data *data)
{
	double	distance;

	data->ray.dir_x = data->ray.dir_x * cos(-to_rad(FOV_ANGLE) / W) - \
		data->ray.dir_y * sin(-to_rad(FOV_ANGLE) / W);
	data->ray.dir_y = data->ray.dir_x * sin(-to_rad(FOV_ANGLE) / W) + \
		data->ray.dir_y * cos(-to_rad(FOV_ANGLE) / W);
	distance = hypot(data->ray.dir_x, data->ray.dir_y);
	data->ray.dir_x /= distance;
	data->ray.dir_y /= distance;
}

static void	render_column(t_data *data, int col, t_ctx *ctx)
{
	double	ray_angle;
	double	perp;
	int		line_height;

	ray_angle = ctx->fov_start + (col * ctx->delta);
	data->ray.dir_x = cos(ray_angle);
	data->ray.dir_y = sin(ray_angle);
	ray_direction(data);
	cast_hits(data, ray_angle);
	perp = fix_fisheye(data, ray_angle, ctx->player_facing_angle);
	if (perp < MIN_PERP)
		perp = MIN_PERP;
	line_height = (int)((TILE_SIZE / perp) * ctx->dist_proj_plane + 0.5);
	data->wall.height = line_height;
	data->wall.top = (H - line_height) / 2;
	data->wall.bottom = data->wall.top + line_height;
	texture_hit_x(data);
	draw_strip(data, col);
}

int	draw_game(t_data *data)
{
	int		col;
	t_ctx	ctx;

	init_ray(data);
	draw_ceiling_and_floor(data);
	ctx.dist_proj_plane = (W / 2.0) / tan(to_rad(FOV_ANGLE) / 2.0);
	ctx.player_facing_angle = ft_atan2(-data->player.dir_y, data->player.dir_x);
	ctx.fov_start = ctx.player_facing_angle - (to_rad(FOV_ANGLE) / 2.0);
	ctx.delta = to_rad(FOV_ANGLE) / (double)W;
	col = 0;
	while (col < W)
	{
		render_column(data, col, &ctx);
		col++;
	}
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win_ptr,
		data->img.ptr, 0, 0);
	return (0);
}
