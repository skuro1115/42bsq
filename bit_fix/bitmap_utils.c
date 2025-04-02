/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:11:43 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 23:11:51 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	allocate_bitmap_memory(t_bitmap *map)
{
	int				i;
	unsigned char	*all_rows;

	map->bytes_per_row = (map->cols + 7) / 8;
	map->data = (unsigned char **)malloc(sizeof(unsigned char *) * map->rows);
	if (!map->data)
		return (0);
	all_rows = (unsigned char *)malloc(map->rows * map->bytes_per_row);
	if (!all_rows)
	{
		free(map->data);
		return (0);
	}
	i = 0;
	while (i < map->rows)
	{
		map->data[i] = all_rows + (i * map->bytes_per_row);
		i++;
	}
	return (1);
}

void	free_bitmap(t_bitmap *map)
{
	if (map->data)
	{
		if (map->data[0])
			free(map->data[0]);
		free(map->data);
	}
}

int	min3(int a, int b, int c)
{
	int	min_val;

	min_val = a;
	if (b < min_val)
		min_val = b;
	if (c < min_val)
		min_val = c;
	return (min_val);
}

void	print_error(void)
{
	write(2, "map error\n", 10);
}

void	set_bit(unsigned char **data, int row, int col, int value)
{
	int	byte_index;
	int	bit_position;

	byte_index = col / 8;
	bit_position = 7 - (col % 8);
	if (value)
		data[row][byte_index] |= (1 << bit_position);
	else
		data[row][byte_index] &= ~(1 << bit_position);
}
