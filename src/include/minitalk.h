/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:23:06 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/02 10:00:28 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <libft.h>
# include <stdlib.h>
# include <signal.h>

int		chunk2bytes(char *str);
char	*bytes2chunk(int bytes);

#endif // !MINITALK_H
