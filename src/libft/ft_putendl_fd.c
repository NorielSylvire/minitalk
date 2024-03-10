/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:56:40 by fhongu            #+#    #+#             */
/*   Updated: 2023/11/11 18:50:14 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(const char *s, int fd)
{
	char	*s_endl;
	int		ret;

	s_endl = ft_append(s, "\n", 0, 0);
	ret = ft_putstr_fd(s_endl, fd);
	ft_free((void **) &s_endl);
	return (ret);
}
