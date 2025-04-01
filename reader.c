/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:36:53 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/01 22:51:05 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

char	*expand_buffer(char *buffer, int size, int capacity)
{
	char	*new_buffer;
	int		i;
	int		new_capacity;

	new_capacity = capacity * 2;
	new_buffer = (char *)malloc(sizeof(char) * new_capacity);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}

char	*copy_tmp_to_buffer(char *buffer, char *tmp, int *size)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		buffer[*size] = tmp[i];
		(*size)++;
		i++;
	}
	return (buffer);
}

int	process_read_chunk(t_buffer *buf, char *tmp, int read_bytes)
{
	tmp[read_bytes] = '\0';
	if (buf->size + read_bytes >= buf->capacity)
	{
		buf->capacity *= 2;
		buf->data = expand_buffer(buf->data, buf->size, buf->capacity / 2);
		if (!buf->data)
			return (0);
	}
	buf->data = copy_tmp_to_buffer(buf->data, tmp, &buf->size);
	return (1);
}

char	*read_stdin(void)
{
	t_buffer	buf;
	int			read_bytes;
	char		tmp[1024];

	buf.size = 0;
	buf.capacity = 1024;
	buf.data = (char *)malloc(sizeof(char) * buf.capacity);
	if (!buf.data)
		return (NULL);
	read_bytes = read(0, tmp, 1023);
	while (read_bytes > 0)
	{
		if (!process_read_chunk(&buf, tmp, read_bytes))
			return (NULL);
		read_bytes = read(0, tmp, 1023);
	}
	buf.data[buf.size] = '\0';
	return (buf.data);
}
