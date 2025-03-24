/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:36:50 by barnaud           #+#    #+#             */
/*   Updated: 2025/03/24 13:44:33 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	save_map(char *map, t_vars *game)
{
	char	*line;
	int		file;
	int		linecount;

	linecount = 0;
	file = open(map, O_RDWR);
	if (file == -1)
	{
		write(1, "Error\nMap does not exist\n", 25);
		return (1);
	}
	if (ft_strnstr(map, ".ber", ft_strlen(map)) == NULL)
	{
		write(1, "Error\nmap has to be .ber\n", 25);
		return (1);
	}
	line = get_next_line(file);
	if (line == NULL)
		exit(EXIT_FAILURE);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		linecount++;
	}
	close(file);
	free(line);
	return (0);
}
