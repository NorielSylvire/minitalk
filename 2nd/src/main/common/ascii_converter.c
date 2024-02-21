/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_converter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:12:43 by fhongu            #+#    #+#             */
/*   Updated: 2024/02/19 23:04:56 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

int	chunk2bytes(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i] && i < 4)
	{
		res += str[i];
		res = res << 8 * i;
		i++;
	}
	return (res);
}
