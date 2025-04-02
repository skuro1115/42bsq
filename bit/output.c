/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:56:47 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 22:12:17 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// 指定された位置にある文字を判定（解の内部かどうか）
char	get_char_at_position(t_bitmap *map, t_solution sol, int i, int j)
{
	int	in_solution;

	in_solution = 0;
	if (i >= sol.row && i < sol.row + sol.size)
	{
		if (j >= sol.col && j < sol.col + sol.size)
			in_solution = 1;
	}
	if (in_solution)
		return (map->full);
	if (get_bit(map->data, i, j))
		return (map->empty);
	else
		return (map->obstacle);
}

// 1行分のマップを表示
void	print_map_row(t_bitmap *map, t_solution sol, int row)
{
	int		j;
	char	c;

	j = 0;
	while (j < map->cols)
	{
		c = get_char_at_position(map, sol, row, j);
		write(1, &c, 1);
		j++;
	}
	write(1, "\n", 1);
}

// 見つかった最大正方形を表示する
void	print_solution(t_bitmap *map, t_solution sol)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		print_map_row(map, sol, i);
		i++;
	}
}
