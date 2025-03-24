/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:38:11 by barnaud           #+#    #+#             */
/*   Updated: 2025/01/15 11:21:28 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_replace(char *buffer)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	tmp = ft_calloc(sizeof(char), ft_strlen(buffer) - i);
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		tmp[j++] = buffer[i++];
	free(buffer);
	return (tmp);
}

char	*ft_extract(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_buffer(int fd, char *buffer)
{
	char	*tmp;
	int		bytes;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		tmp = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!tmp)
			return (NULL);
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(tmp), NULL);
		buffer = ft_strjoin(buffer, tmp);
		if (!buffer)
			return (NULL);
		free(tmp);
		if (bytes == 0 || ft_newline(buffer))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_extract(buffer);
	buffer = ft_replace(buffer);
	return (line);
}

// int    main(void)
// {
//     int        fd;
//     char    *string;

//     fd = open ("test.txt", O_RDONLY);
//     string = get_next_line(fd);
//     while (string != NULL)
//     {
//         printf("%s", string);
//         free(string);
//         string = get_next_line(fd);
//     }
//     close(fd);
//     return (0);
// }