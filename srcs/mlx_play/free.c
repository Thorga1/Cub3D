/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:57:53 by yurwang           #+#    #+#             */
/*   Updated: 2025/08/31 16:57:57 by yurwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_input(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

void	ft_free_all(t_data *data)
{
	ft_free_texutre(data);
	if (data->conf.no)
		free(data->conf.no);
	if (data->conf.so)
		free(data->conf.so);
	if (data->conf.ea)
		free(data->conf.ea);
	if (data->conf.we)
		free(data->conf.we);
	free_input(data->input);
	free_input(data->map.map);
	free_input(data->map.dup_map);
	free(data);
}

int	ft_exit(t_data *data, int end)
{
	ft_free_all(data);
	exit(end);
}

int	ft_end(t_data *data)
{
	ft_exit(data, 0);
	return (0);
}

void	ft_free_texutre(t_data *d)
{
	if (d->textures[0].ptr)
		mlx_destroy_image(d->mlx.ptr, d->textures[0].ptr);
	if (d->textures[1].ptr)
		mlx_destroy_image(d->mlx.ptr, d->textures[1].ptr);
	if (d->textures[2].ptr)
		mlx_destroy_image(d->mlx.ptr, d->textures[2].ptr);
	if (d->textures[3].ptr)
		mlx_destroy_image(d->mlx.ptr, d->textures[3].ptr);
	if (d->img.ptr)
		mlx_destroy_image(d->mlx.ptr, d->img.ptr);
	if (d->mlx.win_ptr)
		mlx_destroy_window(d->mlx.ptr, d->mlx.win_ptr);
	if (d->mlx.ptr)
	{
		mlx_destroy_display(d->mlx.ptr);
		free(d->mlx.ptr);
	}
}
