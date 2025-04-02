/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:00:28 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 22:47:28 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// 行数と記号を解析
int	parse_rows_and_symbols(char *buffer, t_bitmap *map)
{
	int	i;
	int	rows;

	rows = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (buffer[i] >= '0' && buffer[i] <= '9')
			rows = rows * 10 + (buffer[i] - '0');
		else
			break ;
		i++;
	}
	if (i == 0 || rows == 0 || !buffer[i] || !buffer[i + 1] || !buffer[i + 2])
		return (0);
	map->empty = buffer[i];
	map->obstacle = buffer[i + 1];
	map->full = buffer[i + 2];
	map->rows = rows;
	return (i);
}

// 記号の検証
int	validate_symbols(t_bitmap *map)
{
	if (map->empty == map->obstacle || map->empty == map->full
		|| map->obstacle == map->full)
		return (0);
	return (1);
}

// 列数をカウント
int	count_columns(char *buffer, int start)
{
	int	cols;

	cols = 0;
	while (buffer[start + cols] && buffer[start + cols] != '\n')
		cols++;
	return (cols);
}

// マップ情報（行数と記号）を解析
int	parse_map_info(char *buffer, t_bitmap *map, int *pos)
{
	int	i;
	int	cols;

	i = parse_rows_and_symbols(buffer, map);
	if (i == 0 || !validate_symbols(map))
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		*pos = i + 1;
	else
		return (0);
	cols = count_columns(buffer, *pos);
	if (cols == 0)
		return (0);
	map->cols = cols;
	return (allocate_bitmap_memory(map));
}
