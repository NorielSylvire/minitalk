/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preppend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:57:57 by fhongu            #+#    #+#             */
/*   Updated: 2023/10/27 22:12:49 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_preppend(const char *str, const char *pre, int fr_s, int fr_p)
{
	size_t		strlen;
	char		*result;
	char		*rescopy;
	const char	*strcopy;
	const char	*precopy;

	strcopy = str;
	precopy = pre;
	strlen = ft_strlen(str) + ft_strlen(pre);
	result = ft_calloc(strlen + 1, sizeof (char));
	if (!result)
		return (NULL);
	rescopy = result;
	while (*precopy)
		*rescopy++ = *precopy++;
	while (*strcopy)
		*rescopy++ = *strcopy++;
	if (fr_s)
		ft_free((void **) &str);
	if (fr_p)
		ft_free((void **) &pre);
	return (result);
}
