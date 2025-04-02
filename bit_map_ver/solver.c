/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkuroda <shkuroda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:28:45 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 23:10:44 by shkuroda         ###   ########.fr       */
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

void	init_dp_first_row_col(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (i == 0 || j == 0)
			{
				if (map->grid[i][j] == map->empty)
					map->dp[i][j] = 1;
				else
					map->dp[i][j] = 0;
			}
			j++;
		}
		i++;
	}
}

void	process_dp_cell(t_map *map, int i, int j, t_square *solution)
{
	if (bit_get(map->grid[i], j) == 0)
		map->dp[i][j] = 0;
	else
	{
		map->dp[i][j] = min3(map->dp[i - 1][j], map->dp[i][j - 1], map->dp[i
				- 1][j - 1]) + 1;
		if (map->dp[i][j] > solution->size)
		{
			solution->size = map->dp[i][j];
			solution->row = i;
			solution->col = j;
		}
	}
}

#include "bsq.h"

t_square	solve_map(t_map *map)
{
	int			i;
	int			j;
	t_square	solution;

	solution.size = 0;
	solution.row = 0;
	solution.col = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (bit_get(map->grid[i], j) == 0)
				map->dp[i][j] = 0;
			else if (i == 0 || j == 0)
				map->dp[i][j] = 1;
			else
			{
				map->dp[i][j] = min3(
						map->dp[i - 1][j],
						map->dp[i][j - 1],
						map->dp[i - 1][j - 1]) + 1;
			}
			if (map->dp[i][j] > solution.size)
			{
				solution.size = map->dp[i][j];
				solution.row = i;
				solution.col = j;
			}
			j++;
		}
		i++;
	}
	return (solution);
}


void	fill_solution(t_map *map, t_square *solution)
{
	int	i;
	int	j;

	i = solution->row - solution->size + 1;
	while (i <= solution->row)
	{
		j = solution->col - solution->size + 1;
		while (j <= solution->col)
		{
			bit_set(map->grid[i], j, 1);
			j++;
		}
		i++;
	}
}
