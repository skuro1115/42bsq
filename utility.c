/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:27:08 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/01 22:36:41 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	if (map->dp)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->dp[i]);
			i++;
		}
		free(map->dp);
	}
}

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			write(1, &map->grid[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	print_error(void)
{
	write(2, "map error\n", 10);
}

int	is_valid_char(t_map *map, char c)
{
	return (c == map->empty || c == map->obstacle);
}
