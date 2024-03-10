/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_converter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:12:43 by fhongu            #+#    #+#             */
/*   Updated: 2024/02/21 22:52:55 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"
#include <libft.h>

int	chunk2bytes(char *chunk)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (chunk[i] && i < 4)
	{
		res += chunk[i] << 8 * i;
		i++;
	}
	return (res);
}

char	*bytes2chunk(int bytes)
{
	char	*res;
	int		i;

	res = ft_calloc(4, 1);
	i = 0;
	while (bytes > 0 && i < 4)
	{
		res[i] = bytes % 256;
		bytes = bytes >> 8;
		i++;
	}
	return (res);
}
