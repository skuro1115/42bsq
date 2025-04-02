/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:57:30 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 22:13:50 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// 現在行の処理（完全版）
void	process_current_row(t_dp_context *ctx, int row)
{
	process_first_col(ctx, row);
	process_rest_cols(ctx, row);
}

// 行を交換してクリア
void	swap_and_clear_rows(t_dp_context *ctx)
{
	unsigned char	*temp;
	int				j;

	temp = ctx->prev_row;
	ctx->prev_row = ctx->curr_row;
	ctx->curr_row = temp;
	j = 0;
	while (j < ctx->map->cols)
	{
		ctx->curr_row[j] = 0;
		j++;
	}
}

// DPコンテキストを初期化
t_dp_context	*init_dp_context(t_bitmap *map, t_solution *sol)
{
	t_dp_context	*ctx;

	ctx = (t_dp_context *)malloc(sizeof(t_dp_context));
	if (!ctx)
		return (NULL);
	ctx->map = map;
	ctx->sol = sol;
	ctx->prev_row = (unsigned char *)calloc(map->cols, sizeof(unsigned char));
	ctx->curr_row = (unsigned char *)calloc(map->cols, sizeof(unsigned char));
	if (!ctx->prev_row || !ctx->curr_row)
	{
		if (ctx->prev_row)
			free(ctx->prev_row);
		if (ctx->curr_row)
			free(ctx->curr_row);
		free(ctx);
		return (NULL);
	}
	return (ctx);
}

// ビットマップを解析して最大正方形を見つける
t_solution	solve_bitmap(t_bitmap *map)
{
	t_solution		sol;
	t_dp_context	*ctx;
	int				i;

	sol.size = 0;
	sol.row = 0;
	sol.col = 0;
	ctx = init_dp_context(map, &sol);
	if (!ctx)
		return (sol);
	init_first_row(ctx);
	i = 1;
	while (i < map->rows)
	{
		process_current_row(ctx, i);
		swap_and_clear_rows(ctx);
		i++;
	}
	free(ctx->prev_row);
	free(ctx->curr_row);
	free(ctx);
	return (sol);
}
