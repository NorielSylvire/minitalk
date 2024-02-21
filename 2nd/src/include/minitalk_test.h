/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_test.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:54:46 by fhongu            #+#    #+#             */
/*   Updated: 2024/02/19 23:06:55 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_TEST_H
# define MINITALK_TEST_H
# include "client.h"
# include <libtest42.h>
# define TESTH "\nTest %-60s [%s]"

char	*make_test_result_string(int res);
void	test_common(void);
int		test_chunk2bytes_empty_string(void);
int		test_chunk2bytes_one_char(void);
int		test_chunk2bytes_full_chunk(void);

#endif // !MINITALK_TEST_H
