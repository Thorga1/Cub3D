/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_strip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:09:43 by yurwang           #+#    #+#             */
/*   Updated: 2025/08/13 20:21:42 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_color(t_img *img, int texture_x, int texture_y)
{
	char	*pixel;

	if (texture_x < 0)
		texture_x = 0;
	else if (texture_x >= img->width)
		texture_x = img->width - 1;
	if (texture_y < 0)
		texture_y = 0;
	else if (texture_y >= img->height)
		texture_y = img->height - 1;
	pixel = img->addr + (texture_y * img->ll) + (texture_x * img->bpp / 8);
	return (*(unsigned int *)pixel);
}

void	add_color_to_pixel_via_mlx(t_img *img, int row, \
			int col, unsigned int color)
{
	char	*dst;

	if (row < 0 || row >= H || col < 0 || col >= W)
		return ;
	dst = img->addr + row * img->ll + col * (img->bpp / 8);
	*(unsigned int *) dst = color;
}

void	draw_pixel(t_data *data, t_img *img, int row, int col)
{
	int	color;

	color = get_pixel_color(img, data->ray.texture_x, data->ray.texture_y);
	add_color_to_pixel_via_mlx(&data->img, row, col, color);
}

void	draw_texture(t_data *data, int row, int col)
{
	float	distancefromtop;
	t_img	*tex;

	if (data->wall.height <= 0)
		return ;
	distancefromtop = (float)row + (data->wall.height / 2.0f) - (H / 2.0f);
	tex = NULL;
	if (!data->ray.wallhit_side && data->ray.is_facing_down)
		tex = &data->textures[0];
	else if (!data->ray.wallhit_side && !data->ray.is_facing_down)
		tex = &data->textures[1];
	else if (data->ray.wallhit_side && data->ray.is_facing_right)
		tex = &data->textures[2];
	else if (data->ray.wallhit_side && !data->ray.is_facing_right)
		tex = &data->textures[3];
	if (!tex || tex->height <= 0)
		return ;
	data->ray.texture_y = (int)(distancefromtop * \
		((float)tex->height / (float)data->wall.height));
	if (data->ray.texture_y < 0)
		data->ray.texture_y = 0;
	else if (data->ray.texture_y >= tex->height)
		data->ray.texture_y = tex->height - 1;
	draw_pixel(data, tex, row, col);
}

void	draw_strip(t_data *data, int col)
{
	int	row;

	row = 0;
	while (row < H)
	{
		if (row >= (int)(data->wall.top + 0.5) && \
			row < (int)(data->wall.bottom))
			draw_texture(data, row, col);
		row++;
	}
}
