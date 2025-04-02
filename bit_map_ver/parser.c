/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkuroda <shkuroda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:28:21 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 22:07:20 by shkuroda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	read_first_line(t_map *map, char *buffer, int *pos)
{
	int	i;
	int	rows;

	rows = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (buffer[i] >= '0' && buffer[i] <= '9')
			rows = rows * 10 + (buffer[i] - '0');
		else
			break ;
		i++;
	}
	if (i == 0 || rows == 0 || !buffer[i] || !buffer[i + 1] || !buffer[i + 2])
		return (0);
	map->empty = buffer[i];
	map->obstacle = buffer[i + 1];
	map->full = buffer[i + 2];
	if (map->empty == map->obstacle || map->empty == map->full
		|| map->obstacle == map->full)
		return (0);
	map->rows = rows;
	return (process_first_line_end(buffer, i, pos));
}

int	parse_map(t_map *map, char *buffer)
{
	int	pos;
	int	cols;

	if (!read_first_line(map, buffer, &pos))
		return (0);
	cols = count_columns(map, buffer, pos);
	if (cols == 0)
		return (0);
	map->cols = cols;
	if (!create_map_grid(map, map->rows, map->cols))
		return (0);
	return (fill_grid(map, buffer, pos));
}

int	fill_grid_row(t_map *map, char *buffer, int pos, int row)
{
	int	j;
	int	is_empty;

	j = 0;
	while (j < map->cols)
	{
		if (!is_valid_char(map, buffer[pos]))
			return (-1);
		is_empty = (buffer[pos] == map->empty);
		bit_set(map->grid[row], j, is_empty);
		pos++;
		j++;
	}
	if (buffer[pos] != '\n')
		return (-1);
	return (pos + 1);
}

int	fill_grid(t_map *map, char *buffer, int pos)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		pos = fill_grid_row(map, buffer, pos, i);
		if (pos == -1)
			return (0);
		i++;
	}
	return (buffer[pos] == '\0');
}
