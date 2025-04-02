/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:34:02 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 20:36:14 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	copy_chunk_to_buffer(char **buffer, char *chunk, int *total_size,
		int read_size)
{
	char	*temp;
	int		i;

	if (*total_size + read_size >= 4096)
	{
		temp = malloc(sizeof(char) * (*total_size + read_size + 1));
		if (!temp)
			return (0);
		i = 0;
		while (i < *total_size)
		{
			temp[i] = (*buffer)[i];
			i++;
		}
		free(*buffer);
		*buffer = temp;
	}
	i = 0;
	while (i < read_size)
	{
		(*buffer)[*total_size] = chunk[i];
		(*total_size)++;
		i++;
	}
	return (1);
}

int	cleanup_and_return(char **buffer, int fd)
{
	free(*buffer);
	close(fd);
	return (0);
}

int	read_file(char *filename, char **buffer)
{
	int		fd;
	int		read_size;
	int		total_size;
	char	chunk[4096];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	*buffer = malloc(sizeof(char) * 4096);
	if (!*buffer)
		return (0);
	total_size = 0;
	read_size = read(fd, chunk, 4096);
	while (read_size > 0)
	{
		if (!copy_chunk_to_buffer(buffer, chunk, &total_size, read_size))
			return (cleanup_and_return(buffer, fd));
		read_size = read(fd, chunk, 4096);
	}
	(*buffer)[total_size] = '\0';
	close(fd);
	return (1);
}
