/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:37:53 by skatsuya          #+#    #+#             */
/*   Updated: 2025/04/02 22:47:46 by skatsuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_solution
{
	int				size;
	int				row;
	int				col;
}					t_solution;

typedef struct s_bitmap
{
	unsigned char	**data;
	int				rows;
	int				cols;
	int				bytes_per_row;
	char			empty;
	char			obstacle;
	char			full;
}					t_bitmap;

typedef struct s_buffer
{
	char			*data;
	int				size;
	int				capacity;
}					t_buffer;

typedef struct s_dp_context
{
	t_bitmap		*map;
	unsigned char	*prev_row;
	unsigned char	*curr_row;
	t_solution		*sol;
}					t_dp_context;

// bit_utils.c
void				set_bit(unsigned char **bitmap, int row, int col,
						int value);
int					get_bit(unsigned char **bitmap, int row, int col);
void				free_bitmap(t_bitmap *map);
void				print_error(void);
int					min3(int a, int b, int c);

// file_reader.c
int					read_file_content(int fd, char **buffer);
int					read_optimized_file(char *filename, t_bitmap *map);

// file_reader2.c
int					parse_rows_and_symbols(char *buffer, t_bitmap *map);
int					validate_symbols(t_bitmap *map);
int					count_columns(char *buffer, int start);
int					parse_map_info(char *buffer, t_bitmap *map, int *pos);

// file_reader3.c
char				*expand_buffer(char *data, int size, int *capacity);
int					append_to_buffer(char *data, int *size, char *chunk,
						int chunk_size);
char				*read_stdin_optimized(void);

// main.c
int					process_file_optimized(char *filename);
void				process_stdin_optimized(void);

// output.c
char				get_char_at_position(t_bitmap *map, t_solution sol, int i,
						int j);
void				print_map_row(t_bitmap *map, t_solution sol, int row);
void				print_solution(t_bitmap *map, t_solution sol);

// solver1.c
void				init_first_row(t_dp_context *ctx);
void				process_first_col(t_dp_context *ctx, int row);
void				process_rest_cols(t_dp_context *ctx, int row);

// solver2.c
void				process_current_row(t_dp_context *ctx, int row);
void				swap_and_clear_rows(t_dp_context *ctx);
t_dp_context		*init_dp_context(t_bitmap *map, t_solution *sol);
t_solution			solve_bitmap(t_bitmap *map);

// trance_bitmap.c
int					allocate_bitmap_memory(t_bitmap *map);
int					fill_bitmap_row(t_bitmap *map, char *buffer, int pos,
						int row);
int					fill_bitmap(t_bitmap *map, char *buffer, int pos);

#endif
