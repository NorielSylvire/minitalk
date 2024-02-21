/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:05:23 by fhongu            #+#    #+#             */
/*   Updated: 2024/02/17 23:14:05 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_test.h"

int	main(void)
{
	printf(YELLOW"Tests for minitalk\n"DEF_COLOR);
	test_common();
	printf(YELLOW"\n\nFinished testing minitalk!\n"DEF_COLOR);
	return (0);
}

char	*make_test_result_string(int res)
{
	if (res)
		return (GREEN"PASSED"DEF_COLOR);
	return (RED"FAILED"DEF_COLOR);
}
