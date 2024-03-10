/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsubstr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:37:44 by fhongu            #+#    #+#             */
/*   Updated: 2023/10/15 21:21:11 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putsubstr_fd(const char *str, size_t start, size_t end, int fd)
{
	char	*sub;
	int		ret;

	if (!str)
		return (0);
	sub = ft_substr(str, start, end - start + 1);
	if (!sub)
		return (0);
	ft_putstr_fd(sub, fd);
	ret = (int) ft_strlen(sub);
	ft_free((void **) &sub);
	return (ret);
}
