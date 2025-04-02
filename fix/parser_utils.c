/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:43:19 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 20:33:22 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	process_first_line_end(char *buffer, int i, int *pos)
{
	*pos = i + 3;
	while (buffer[*pos] && buffer[*pos] != '\n')
		(*pos)++;
	if (buffer[*pos] == '\n')
		*pos = *pos + 1;
	else
		*pos = 0;
	return (*pos != 0);
}

int	count_columns(t_map *map, char *buffer, int pos)
{
	int	i;
	int	line_len;

	i = pos;
	line_len = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (!is_valid_char(map, buffer[i]))
			return (0);
		line_len++;
		i++;
	}
	if (line_len == 0 || buffer[i] != '\n')
		return (0);
	return (line_len);
}

int	create_map_grid(t_map *map, int rows, int cols)
{
	int	i;

	map->grid = malloc(sizeof(char *) * rows);
	if (!map->grid)
		return (0);
	i = 0;
	while (i < rows)
	{
		map->grid[i] = (char *)malloc(sizeof(char) * cols);
		if (!map->grid[i])
			return (0);
		i++;
	}
	return (1);
}
