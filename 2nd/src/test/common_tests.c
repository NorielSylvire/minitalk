/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:43:22 by fhongu            #+#    #+#             */
/*   Updated: 2024/02/19 23:06:08 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_test.h"

void	test_common(void)
{
	char	*test_result;

	printf(MAGENTA"\nTests for common functions\n"DEF_COLOR);
	test_result = make_test_result_string(test_chunk2bytes_empty_string());
	printf(TESTH, "chunk2bytes 1 Empty string ", test_result);
	test_result = make_test_result_string(test_chunk2bytes_one_char());
	printf(TESTH, "chunk2bytes 2 One char ", test_result);
	test_result = make_test_result_string(test_chunk2bytes_full_chunk());
	printf(TESTH, "chunk2bytes 2 Full chunk of four chars ", test_result);
}

int	test_chunk2bytes_empty_string(void)
{
	char	*empty_string;
	int		result;

	empty_string = "";
	result = chunk2bytes(empty_string);
	return (result == 0);
}

int	test_chunk2bytes_one_char(void)
{
	char	*one_char;
	int		result;

	one_char = "a";
	result = chunk2bytes(one_char);
	return (result == 'a');
}

int	test_chunk2bytes_full_chunk(void)
{
	char	*full_chunk;
	int		result;

	full_chunk = "abcd";
	result = chunk2bytes(full_chunk);
	return (result == (('d' << 24) + ('c' << 16) + ('b' << 8) + 'a'));
}
