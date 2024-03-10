/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:01:26 by fhongu            #+#    #+#             */
/*   Updated: 2023/11/25 20:31:31 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	*nbr;
	int		ret;

	nbr = ft_itoa(n);
	if (!nbr)
		return (0);
	ret = ft_putstr_fd(nbr, fd);
	ft_free((void **)&nbr);
	return (ret);
}
