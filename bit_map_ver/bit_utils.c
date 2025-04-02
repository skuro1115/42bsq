/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkuroda <shkuroda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:35:02 by shkuroda          #+#    #+#             */
/*   Updated: 2025/04/02 22:41:26 by shkuroda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	bit_get(char *line, int index)
{
	int	byte_index;
	int	bit_index;

	byte_index = index / 8;
	bit_index = 7 - (index % 8);
	return ((line[byte_index] >> bit_index) & 1);
}

void	bit_set(char *line, int index, int value)
{
	int	byte_index;
	int	bit_index;

	byte_index = index / 8;
	bit_index = 7 - (index % 8);
	if (value)
		line[byte_index] |= (1 << bit_index);
	else
		line[byte_index] &= ~(1 << bit_index);
}
