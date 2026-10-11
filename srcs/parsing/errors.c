/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:30:29 by tordner           #+#    #+#             */
/*   Updated: 2025/09/09 19:55:04 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cubfile(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' \
		|| str[i - 4] != '.' || !ft_is_alpha(str[i - 5]))
		return (0);
	return (1);
}

int	errors(int ac, char **av)
{
	if (ac != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	if (!is_cubfile(av[1]))
		return (printf("Error\nFile should have .cub extension\n"), 1);
	return (0);
}
