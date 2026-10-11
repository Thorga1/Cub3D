/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:37:39 by tordner           #+#    #+#             */
/*   Updated: 2025/09/09 19:41:33 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_memset(data, 0, sizeof(t_data));
	init_data(data);
	if (errors(ac, av))
		ft_exit(data, 1);
	if (handle_input(data, av))
		ft_exit(data, 1);
	init_mlx(data);
	mlx_loop_hook(data->mlx.ptr, draw_game, data);
	mlx_hook(data->mlx.win_ptr, 2, (1L << 0), ft_key, data);
	mlx_hook(data->mlx.win_ptr, 17, 0, ft_end, data);
	mlx_loop(data->mlx.ptr);
	ft_exit(data, 0);
	return (0);
}
