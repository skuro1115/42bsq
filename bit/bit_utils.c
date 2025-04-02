/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:40:26 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 22:02:49 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// 指定位置のビットを設定（1=空白, 0=障害物）
void	set_bit(unsigned char **bitmap, int row, int col, int value)
{
	int	byte_index;
	int	bit_position;

	byte_index = col / 8;
	bit_position = 7 - (col % 8);
	if (value)
		bitmap[row][byte_index] |= (1 << bit_position);
	else
		bitmap[row][byte_index] &= ~(1 << bit_position);
}

// 指定位置のビットを取得
int	get_bit(unsigned char **bitmap, int row, int col)
{
	int	byte_index;
	int	bit_position;

	byte_index = col / 8;
	bit_position = 7 - (col % 8);
	return ((bitmap[row][byte_index] & (1 << bit_position)) != 0);
}

// メモリ開放
void	free_bitmap(t_bitmap *map)
{
	int	i;

	if (map->data)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->data[i]);
			i++;
		}
		free(map->data);
	}
}

// エラーメッセージ表示
void	print_error(void)
{
	write(2, "map error\n", 10);
}

// 3つの数値の最小値を返す
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
