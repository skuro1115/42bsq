/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:27:45 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 20:46:55 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int			rows;
	int			cols;
	char		**grid;
	char		empty;
	char		obstacle;
	char		full;
}				t_map;

typedef struct s_square
{
	int			size;
	int			row;
	int			col;
}				t_square;

typedef struct s_buffer
{
	char		*data;
	int			size;
	int			capacity;
}				t_buffer;

typedef struct s_dp_context
{
	int			*prev_row;
	int			*curr_row;
	t_square	*solution;
}				t_dp_context;

// files_utils.c
int				copy_chunk_to_buffer(char **buffer, char *chunk,
					int *total_size, int read_size);
int				cleanup_and_return(char **buffer, int fd);
int				read_file(char *filename, char **buffer);

// main.c
int				process_file(char *filename);
void			process_stdin(void);

// parser_utils.c
int				process_first_line_end(char *buffer, int i, int *pos);
int				count_columns(t_map *map, char *buffer, int pos);
int				create_map_grid(t_map *map, int rows, int cols);

// parser.c
int				read_first_line(t_map *map, char *buffer, int *pos);
int				parse_map(t_map *map, char *buffer);
int				fill_grid_row(t_map *map, char *buffer, int pos, int row);
int				fill_grid(t_map *map, char *buffer, int pos);

// reader.c
char			*expand_buffer(char *buffer, int size, int capacity);
char			*copy_tmp_to_buffer(char *buffer, char *tmp, int *size);
int				process_read_chunk(t_buffer *buf, char *tmp, int read_bytes);
char			*read_stdin(void);

// solver.c
int				min3(int a, int b, int c);
void			init_first_row(int *row, t_map *map, int row_idx);
void			process_cell(t_map *map, int i, int j, t_dp_context *ctx);

// solver2.c
void			swap_rows(int **prev, int **curr);
void			process_row(t_map *map, int i, t_dp_context *ctx);
t_square		solve_map(t_map *map);
void			fill_solution(t_map *map, t_square solution);

// utility.c
void			free_map(t_map *map);
void			print_map(t_map *map);
void			print_error(void);
int				is_valid_char(t_map *map, char c);

#endif
