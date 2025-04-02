/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trance_bitmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:44:11 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 22:44:40 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// ビットマップメモリを確保
int	allocate_bitmap_memory(t_bitmap *map)
{
	int	i;

	map->bytes_per_row = (map->cols + 7) / 8;
	map->data = (unsigned char **)malloc(sizeof(unsigned char *) * map->rows);
	if (!map->data)
		return (0);
	i = 0;
	while (i < map->rows)
	{
		map->data[i] = (unsigned char *)calloc(map->bytes_per_row,
				sizeof(unsigned char));
		if (!map->data[i])
			return (0);
		i++;
	}
	return (1);
}

// 文字マップをビットマップに変換（1行）
int	fill_bitmap_row(t_bitmap *map, char *buffer, int pos, int row)
{
	int	j;

	j = 0;
	while (j < map->cols)
	{
		if (buffer[pos] != map->empty && buffer[pos] != map->obstacle)
			return (-1);
		set_bit(map->data, row, j, buffer[pos] == map->empty);
		pos++;
		j++;
	}
	if (buffer[pos] != '\n')
		return (-1);
	return (pos + 1);
}

// 文字マップをビットマップに変換（全体）
int	fill_bitmap(t_bitmap *map, char *buffer, int pos)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		pos = fill_bitmap_row(map, buffer, pos, i);
		if (pos == -1)
			return (0);
		i++;
	}
	return (1);
}
