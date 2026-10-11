/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_fisheye.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:58:52 by yurwang           #+#    #+#             */
/*   Updated: 2025/08/12 20:16:51 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	fix_fisheye(t_data *data, double ray_angle, double player_facing_angle)
{
	double	real_dist;

	real_dist = data->ray.distance * cos(ray_angle - player_facing_angle);
	return (real_dist);
}
