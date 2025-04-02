/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:43:19 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/01 23:01:26 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* parser_utils.c */
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

	map->grid = (char **)malloc(sizeof(char *) * rows);
	map->dp = (int **)malloc(sizeof(int *) * rows);
	if (!map->grid || !map->dp)
		return (0);
	i = 0;
	while (i < rows)
	{
		map->grid[i] = (char *)malloc(sizeof(char) * cols);
		map->dp[i] = (int *)malloc(sizeof(int) * cols);
		if (!map->grid[i] || !map->dp[i])
			return (0);
		i++;
	}
	return (1);
}

int	read_file(char *filename, char **buffer)
{
	int		fd;
	int		file_size;
	int		read_size;
	char	c;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	file_size = 0;
	while (read(fd, &c, 1) > 0)
		file_size++;
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	*buffer = (char *)malloc(sizeof(char) * (file_size + 1));
	if (!*buffer)
	{
		close(fd);
		return (0);
	}
	read_size = read(fd, *buffer, file_size);
	(*buffer)[read_size] = '\0';
	close(fd);
	return (1);
}
