/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_test.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:54:46 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/02 08:32:39 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_TEST_H
# define MINITALK_TEST_H
# include "client.h"
# include <libtest42.h>
# define TESTH "\nTest %-60s [%s]"
# define TRUE 1
# define FALSE 0

char	*make_test_result_string(int res);
void	test_common(void);
void	test_client(void);
int		test_chunk2bytes_empty_string(void);
int		test_chunk2bytes_one_char(void);
int		test_chunk2bytes_full_chunk(char *full_chunk);
int		test_bytes2chunk_one_char(void);
int		test_bytes2chunk_abcd(void);
int		test_bytes2chunk_symbols(void);
int		test_send_bit_0(void);
int		test_send_bit_1(void);
int		test_send_byte_zero(void);
int		test_send_byte_max(void);
int		test_send_byte_nbr(void);
int		test_send_byte_char_t(void);
int		test_send_string_cool(void);
int		test_send_string_lorem_ipsum(void);

#endif // !MINITALK_TEST_H
