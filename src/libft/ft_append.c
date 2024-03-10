/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:18:19 by fhongu            #+#    #+#             */
/*   Updated: 2023/10/27 22:12:39 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append(const char *str, const char *apd, int fr_s, int fr_a)
{
	size_t		strlen;
	char		*result;
	char		*rescopy;
	const char	*strcopy;
	const char	*apdcopy;

	strcopy = str;
	apdcopy = apd;
	strlen = ft_strlen(str) + ft_strlen(apd);
	result = ft_calloc(strlen + 1, sizeof (char));
	if (!result)
		return (NULL);
	rescopy = result;
	while (*strcopy)
		*rescopy++ = *strcopy++;
	while (*apdcopy)
		*rescopy++ = *apdcopy++;
	if (fr_s)
		ft_free((void **) &str);
	if (fr_a)
		ft_free((void **) &apd);
	return (result);
}
