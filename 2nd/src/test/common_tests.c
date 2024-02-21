/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:43:22 by fhongu            #+#    #+#             */
/*   Updated: 2024/02/22 00:49:54 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_test.h"
#include <libft.h>

void	test_common(void)
{
	char	*test_result;

	printf(MAGENTA"\nTests for common functions\n"DEF_COLOR);
	test_result = make_test_result_string(test_chunk2bytes_empty_string());
	printf(TESTH, "chunk2bytes 1 Empty string ", test_result);
	test_result = make_test_result_string(test_chunk2bytes_one_char());
	printf(TESTH, "chunk2bytes 2 One char ", test_result);
	test_result = make_test_result_string(test_chunk2bytes_full_chunk("abcd"));
	printf(TESTH, "chunk2bytes 2 Full chunk \"abcd\" ", test_result);
	test_result = make_test_result_string(test_chunk2bytes_full_chunk("*\t4%"));
	printf(TESTH, "chunk2bytes 3 Full chunk \"*\\t4%\" ", test_result);
	test_result = make_test_result_string(test_bytes2chunk_one_char());
	printf(TESTH, "bytes2chunk 1 One char 'a' ", test_result);
	test_result = make_test_result_string(test_bytes2chunk_abcd());
	printf(TESTH, "bytes2chunk 1 String \"abcd\" ", test_result);
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

int	test_chunk2bytes_full_chunk(char *full_chunk)
{
	int		result;
	int		expected_result;

	expected_result = (full_chunk[0] + (full_chunk[1] << 8)+ (full_chunk[2] << 16) + (full_chunk[3] << 24));
	result = chunk2bytes(full_chunk);
	return (result == expected_result);
}

int	test_bytes2chunk_one_char(void)
{
	char	one_char;
	char	*str;
	int		result;

	one_char = 'a';
	str = bytes2chunk(one_char);
	result = *str == one_char;
	ft_free((void **) &str);
	return (result);
}

int	test_bytes2chunk_abcd(void)
{
	char	*str;
	int		abcd;
	int		result;

	abcd = ('a' + ('b' << 8) + ('c' << 16) + ('d' << 24));
	str = bytes2chunk(abcd);
	result = ft_strncmp(str, "abcd", 4);
	ft_free((void **) &str);
	return (result == 0);
}
