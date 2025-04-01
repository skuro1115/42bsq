/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:27:45 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/01 23:01:50 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* bsq.h */
#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**grid;
	int		**dp;
}			t_map;

typedef struct s_square
{
	int		size;
	int		row;
	int		col;
}			t_square;

typedef struct s_buffer
{
	char	*data;
	int		size;
	int		capacity;
}			t_buffer;

/* main.c functions */
int			process_file(char *filename);
void		process_stdin(void);

/* parser.c functions */
int			parse_map(t_map *map, char *buffer);
int			read_first_line(t_map *map, char *buffer, int *pos);
int			fill_grid(t_map *map, char *buffer, int pos);
int			fill_grid_row(t_map *map, char *buffer, int pos, int row);

/* parser_utils.c functions */
int			process_first_line_end(char *buffer, int i, int *pos);
int			count_columns(t_map *map, char *buffer, int pos);
int			create_map_grid(t_map *map, int rows, int cols);
int			read_file(char *filename, char **buffer);

/* solver.c functions */
t_square	solve_map(t_map *map);
void		fill_solution(t_map *map, t_square solution);
int			min3(int a, int b, int c);
void		init_dp_first_row_col(t_map *map);
void		process_dp_cell(t_map *map, int i, int j, t_square *solution);

/* utility.c functions */
void		free_map(t_map *map);
void		print_map(t_map *map);
void		print_error(void);
int			is_valid_char(t_map *map, char c);

/* reader.c functions */
char		*read_stdin(void);
char		*expand_buffer(char *buffer, int size, int capacity);
char		*copy_tmp_to_buffer(char *buffer, char *tmp, int *size);
int			process_read_chunk(t_buffer *buf, char *tmp, int read_bytes);

#endif
