/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:59:47 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 21:59:53 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// バッファを拡張
char	*expand_buffer(char *data, int size, int *capacity)
{
	char	*new_buffer;
	int		i;
	int		new_capacity;

	new_capacity = *capacity * 2;
	new_buffer = (char *)malloc(sizeof(char) * new_capacity);
	if (!new_buffer)
	{
		free(data);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		new_buffer[i] = data[i];
		i++;
	}
	free(data);
	*capacity = new_capacity;
	return (new_buffer);
}

// バッファに新規データを追加
int	append_to_buffer(char *data, int *size, char *chunk, int chunk_size)
{
	int	i;

	i = 0;
	while (i < chunk_size)
	{
		data[*size] = chunk[i];
		(*size)++;
		i++;
	}
	return (1);
}

// 標準入力から読み込む
char	*read_stdin_optimized(void)
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
		tmp[read_bytes] = '\0';
		if (buf.size + read_bytes >= buf.capacity)
		{
			buf.data = expand_buffer(buf.data, buf.size, &buf.capacity);
			if (!buf.data)
				return (NULL);
		}
		append_to_buffer(buf.data, &buf.size, tmp, read_bytes);
		read_bytes = read(0, tmp, 1023);
	}
	buf.data[buf.size] = '\0';
	return (buf.data);
}
