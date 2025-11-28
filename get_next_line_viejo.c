/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrekalde <mrekalde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:25:37 by mrekalde          #+#    #+#             */
/*   Updated: 2024/01/10 18:28:16 by mrekalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*append_buffer(char *basin_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(basin_buffer, read_buffer);
	free(basin_buffer);
	return (temp);
}

char	*read_from_file(char *basin_buffer, int fd)
{
	char	*cup_buffer;
	int		bytes_read;

	cup_buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!cup_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(cup_buffer), NULL);
		cup_buffer[bytes_read] = '\0';
		basin_buffer = append_buffer(basin_buffer, cup_buffer);
		if (ft_strchr(basin_buffer, '\n'))
			break ;
	}
	free (cup_buffer);
	return (basin_buffer);
}

char	*extract_line(char *basin_buffer)
{
	char	*newline_position;
	char	*newline_position2;
	char	*line;
	int		len;

	newline_position = ft_strchr(basin_buffer, '\n');
	newline_position2 = ft_strchr(basin_buffer, '\0');
	if (newline_position || newline_position2)
	{
		len = newline_position - basin_buffer;
		line = malloc(len + 1);
		ft_strlcpy(line, basin_buffer, len + 1);
	}
	else
	{
		len = ft_strlen(basin_buffer);
		line = malloc(len + 1);
		ft_strlcpy(line, basin_buffer, len + 1);
	}
	return (line);
}

char	*obtain_remaining(char *basin_buffer)
{
	char	*newline_position;
	char	*remaining;
	int		i;

	i = 0;
	newline_position = ft_strchr(basin_buffer, '\n');
	if (newline_position)
	{
		remaining = malloc(ft_strlen(newline_position));
		while (newline_position[i + 1] != '\0')
		{
			remaining[i] = newline_position[i + 1];
			i++;
		}
		remaining[ft_strlen(newline_position + 1)] = '\0';
		free(basin_buffer);
		return (remaining);
	}
	else
	{
		free(basin_buffer);
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	*basin_buffer;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!basin_buffer)
		basin_buffer = malloc(1 * sizeof (char));
	if (!basin_buffer)
		return (free(basin_buffer), NULL);
	if (!ft_strchr(basin_buffer, '\n'))
		basin_buffer = read_from_file(basin_buffer, fd);
	line = extract_line(basin_buffer);
	if (!line)
		return (NULL);
	basin_buffer = obtain_remaining(basin_buffer);
	return (line);
}
