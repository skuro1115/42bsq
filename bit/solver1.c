/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:58:40 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 21:58:56 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// 最初の行を初期化
void	init_first_row(t_dp_context *ctx)
{
	int			j;
	t_bitmap	*map;

	map = ctx->map;
	j = 0;
	while (j < map->cols)
	{
		ctx->prev_row[j] = get_bit(map->data, 0, j);
		if (ctx->prev_row[j] > ctx->sol->size)
		{
			ctx->sol->size = 1;
			ctx->sol->row = 0;
			ctx->sol->col = j;
		}
		j++;
	}
}

// 現在行の処理（1列目）
void	process_first_col(t_dp_context *ctx, int row)
{
	ctx->curr_row[0] = get_bit(ctx->map->data, row, 0);
	if (ctx->curr_row[0] > ctx->sol->size)
	{
		ctx->sol->size = 1;
		ctx->sol->row = row;
		ctx->sol->col = 0;
	}
}

// 現在行の処理（2列目以降）
void	process_rest_cols(t_dp_context *ctx, int row)
{
	int			j;
	t_bitmap	*map;

	map = ctx->map;
	j = 1;
	while (j < map->cols)
	{
		if (get_bit(map->data, row, j))
		{
			ctx->curr_row[j] = min3(ctx->prev_row[j], ctx->prev_row[j - 1],
					ctx->curr_row[j - 1]) + 1;
			if (ctx->curr_row[j] > ctx->sol->size)
			{
				ctx->sol->size = ctx->curr_row[j];
				ctx->sol->row = row - ctx->sol->size + 1;
				ctx->sol->col = j - ctx->sol->size + 1;
			}
		}
		else
		{
			ctx->curr_row[j] = 0;
		}
		j++;
	}
}
