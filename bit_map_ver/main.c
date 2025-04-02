/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:28:05 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/01 22:28:10 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */
#include "bsq.h"

int	process_file(char *filename)
{
	t_map		map;
	t_square	solution;
	char		*buffer;

	buffer = NULL;
	if (!read_file(filename, &buffer))
	{
		print_error();
		return (0);
	}
	if (!parse_map(&map, buffer))
	{
		free(buffer);
		print_error();
		return (0);
	}
	free(buffer);
	solution = solve_map(&map);
	fill_solution(&map, solution);
	print_map(&map);
	free_map(&map);
	return (1);
}

void	process_stdin(void)
{
	t_map		map;
	t_square	solution;
	char		*buffer;

	buffer = read_stdin();
	if (!buffer || !parse_map(&map, buffer))
	{
		if (buffer)
			free(buffer);
		print_error();
		return ;
	}
	free(buffer);
	solution = solve_map(&map);
	fill_solution(&map, solution);
	print_map(&map);
	free_map(&map);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
	{
		process_stdin();
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			process_file(argv[i]);
			if (i < argc - 1)
				write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}
