/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:29:08 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 20:22:01 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	swap_rows(int **prev, int **curr)
{
	int	*temp;

	temp = *prev;
	*prev = *curr;
	*curr = temp;
}

void	process_row(t_map *map, int i, t_dp_context *ctx)
{
	int	j;

	j = 0;
	if (map->grid[i][0] == map->empty)
		ctx->curr_row[0] = 1;
	else
		ctx->curr_row[0] = 0;
	j = 1;
	while (j < map->cols)
	{
		process_cell(map, i, j, ctx);
		j++;
	}
}

t_square	solve_map(t_map *map)
{
	t_square		solution;
	t_dp_context	ctx;
	int				i;

	solution.size = 0;
	solution.row = 0;
	solution.col = 0;
	ctx.prev_row = malloc(sizeof(int) * map->cols);
	ctx.curr_row = malloc(sizeof(int) * map->cols);
	ctx.solution = &solution;
	if (!ctx.prev_row || !ctx.curr_row)
		return (solution);
	init_first_row(ctx.prev_row, map, 0);
	i = 1;
	while (i < map->rows)
	{
		process_row(map, i, &ctx);
		swap_rows(&ctx.prev_row, &ctx.curr_row);
		i++;
	}
	free(ctx.prev_row);
	free(ctx.curr_row);
	return (solution);
}

void	fill_solution(t_map *map, t_square solution)
{
	int	i;
	int	j;

	i = solution.row;
	while (i < solution.row + solution.size)
	{
		j = solution.col;
		while (j < solution.col + solution.size)
		{
			map->grid[i][j] = map->full;
			j++;
		}
		i++;
	}
}
