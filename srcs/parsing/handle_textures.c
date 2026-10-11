/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:17:23 by tordner           #+#    #+#             */
/*   Updated: 2025/09/09 19:47:31 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

char	*trim_after_xpm(const char *str)
{
	int		i;
	char	*new;
	int		len;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] == 'x'
			&& str[i + 2] == 'p' && str[i + 3] == 'm')
		{
			len = i + 4;
			new = (char *)malloc(sizeof(char) * (len + 1));
			if (!new)
				return (NULL);
			strncpy(new, str, len);
			new[len] = '\0';
			return (new);
		}
		i++;
	}
	return (NULL);
}

int	validate_texture(t_data *data, char *path, const char *label)
{
	char	*trimmed;

	if (!path || path[0] == '\0')
		return (printf("Error\n%s path is empty\n", label), 0);
	trimmed = trim_after_xpm(path);
	if (!trimmed)
		return (printf("Error\n%s must be a .xpm file\n", label), 0);
	if (!is_valid_file(trimmed))
	{
		free(trimmed);
		return (printf("Error\n%s file cannot be opened\n", label), 0);
	}
	if (strcmp(label, "NO") == 0)
		data->conf.no = trimmed;
	else if (strcmp(label, "SO") == 0)
		data->conf.so = trimmed;
	else if (strcmp(label, "WE") == 0)
		data->conf.we = trimmed;
	else if (strcmp(label, "EA") == 0)
		data->conf.ea = trimmed;
	free(path);
	return (1);
}
