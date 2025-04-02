/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:39:25 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 22:03:20 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	process_file_optimized(char *filename)
{
	t_bitmap	map;
	t_solution	solution;

	if (!read_optimized_file(filename, &map))
	{
		print_error();
		return (0);
	}
	solution = solve_bitmap(&map);
	print_solution(&map, solution);
	free_bitmap(&map);
	return (1);
}

void	process_stdin_optimized(void)
{
	t_bitmap	map;
	t_solution	solution;
	char		*buffer;
	int			pos;

	buffer = read_stdin_optimized();
	if (!buffer)
	{
		print_error();
		return ;
	}
	pos = 0;
	if (!parse_map_info(buffer, &map, &pos) || !fill_bitmap(&map, buffer, pos))
	{
		free(buffer);
		print_error();
		return ;
	}
	free(buffer);
	solution = solve_bitmap(&map);
	print_solution(&map, solution);
	free_bitmap(&map);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
	{
		process_stdin_optimized();
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			process_file_optimized(argv[i]);
			if (i < argc - 1)
				write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}
