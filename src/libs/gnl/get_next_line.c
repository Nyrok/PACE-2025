/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:29:47 by hkonte            #+#    #+#             */
/*   Updated: 2025/01/17 12:42:53 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

static char	*parse_buffer_line(char *buffer)
{
	size_t	i;
	char	*str;

	i = 0;
	if (buffer[0] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*parse_buffer_memory(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_memory;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0' || (buffer[i] == '\n' && buffer[i + 1] == '\0'))
	{
		free(buffer);
		return (NULL);
	}
	new_memory = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!new_memory)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_memory[j++] = buffer[i++];
	new_memory[j] = '\0';
	free(buffer);
	return (new_memory);
}

static char	*update_memory(int fd, char *memory)
{
	char	*temp;
	int		size;

	size = 1;
	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (!ft_strchr(memory, '\n') && size != 0)
	{
		size = read(fd, temp, BUFFER_SIZE);
		if (size == -1)
		{
			free(temp);
			free(memory);
			return (NULL);
		}
		temp[size] = '\0';
		memory = ft_strjoin(memory, temp);
	}
	free(temp);
	return (memory);
}

char	*get_next_line(int fd)
{
	static char	*memory[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	memory[fd] = update_memory(fd, memory[fd]);
	if (!memory[fd])
		return (NULL);
	line = parse_buffer_line(memory[fd]);
	memory[fd] = parse_buffer_memory(memory[fd]);
	return (line);
}