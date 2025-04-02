/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:28:45 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 20:21:04 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

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

void	init_first_row(int *row, t_map *map, int row_idx)
{
	int	j;

	j = 0;
	while (j < map->cols)
	{
		if (map->grid[row_idx][j] == map->empty)
			row[j] = 1;
		else
			row[j] = 0;
		j++;
	}
}

void	process_cell(t_map *map, int i, int j, t_dp_context *ctx)
{
	if (map->grid[i][j] == map->empty)
	{
		ctx->curr_row[j] = min3(ctx->prev_row[j], ctx->curr_row[j - 1],
				ctx->prev_row[j - 1]) + 1;
		if (ctx->curr_row[j] > ctx->solution->size)
		{
			ctx->solution->size = ctx->curr_row[j];
			ctx->solution->row = i - ctx->solution->size + 1;
			ctx->solution->col = j - ctx->solution->size + 1;
		}
	}
	else
		ctx->curr_row[j] = 0;
}
