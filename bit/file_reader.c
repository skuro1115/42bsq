/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:41:24 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 22:44:37 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <fcntl.h>

// バッファをリサイズする
static char	*resize_buffer(char *old_buf, int old_size, int new_capacity)
{
	char	*new_buf;
	int		i;

	new_buf = (char *)malloc(sizeof(char) * new_capacity);
	if (!new_buf)
	{
		free(old_buf);
		return (NULL);
	}
	i = 0;
	while (i < old_size)
	{
		new_buf[i] = old_buf[i];
		i++;
	}
	free(old_buf);
	return (new_buf);
}

// データをバッファに追加
static void	add_data_to_buffer(char *buf, char *data, int offset, int bytes)
{
	int	i;

	i = 0;
	while (i < bytes)
	{
		buf[offset + i] = data[i];
		i++;
	}
}

// 読み込みループを処理する
static int	read_chunks(int fd, char **buffer, char *temp_buf)
{
	char	temp[1024];
	int		capacity;
	int		size;
	int		read_bytes;

	capacity = 4096;
	size = 0;
	read_bytes = read(fd, temp, 1023);
	while (read_bytes > 0)
	{
		if (size + read_bytes >= capacity)
		{
			capacity *= 2;
			temp_buf = resize_buffer(temp_buf, size, capacity);
			if (!temp_buf)
				return (0);
		}
		add_data_to_buffer(temp_buf, temp, size, read_bytes);
		size += read_bytes;
		read_bytes = read(fd, temp, 1023);
	}
	temp_buf[size] = '\0';
	*buffer = temp_buf;
	return (1);
}

// メイン関数：ファイルの内容を読み込む
int	read_file_content(int fd, char **buffer)
{
	char	*temp_buf;

	temp_buf = (char *)malloc(sizeof(char) * 4096);
	if (!temp_buf)
		return (0);
	if (!read_chunks(fd, buffer, temp_buf))
		return (0);
	return (1);
}

int	read_optimized_file(char *filename, t_bitmap *map)
{
	int		fd;
	char	*buffer;
	int		pos;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!read_file_content(fd, &buffer))
		return (0);
	pos = 0;
	if (!parse_map_info(buffer, map, &pos) || !fill_bitmap(map, buffer, pos))
	{
		free(buffer);
		return (0);
	}
	free(buffer);
	return (1);
}
