/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:10:56 by thorgal           #+#    #+#             */
/*   Updated: 2025/09/09 19:46:55 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	parse_single_rgb_value(const char **str_ptr, int *value)
{
	const char	*str;

	str = *str_ptr;
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	if (!ft_isdigit((unsigned char)*str))
		return (1);
	*value = ft_atoi(str);
	if (*value < 0 || *value > 255)
		return (1);
	while (*str && ft_isdigit((unsigned char)*str))
		str++;
	*str_ptr = str;
	return (0);
}

int	parse_rgb(const char *str, int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (parse_single_rgb_value(&str, &rgb[i]))
			return (1);
		if (i < 2)
		{
			while (*str && ft_isspace((unsigned char)*str))
				str++;
			if (*str != ',')
				return (1);
			str++;
		}
		i++;
	}
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	if (*str != '\0')
		return (1);
	return (0);
}

int	get_floor(t_data *data, const char *str)
{
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	if (parse_rgb(str, data->conf.floor_rgb))
	{
		printf("Error\nInvalid floor color.\n");
		return (0);
	}
	return (1);
}

int	get_ceiling(t_data *data, const char *str)
{
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	if (parse_rgb(str, data->conf.ceiling_rgb))
	{
		printf("Error\nInvalid ceiling color.\n");
		return (0);
	}
	return (1);
}
