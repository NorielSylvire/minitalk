/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:01:47 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/02 10:11:29 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "minitalk.h"
# define MESSAGE_INI_SIZE 40
# define MESSAGE_MAX_LOAD 0.75f
# define MESSAGE_RESIZE_FACTOR 2

void	string_parser(int signo, siginfo_t *info, void *uctx);

#endif // !SERVER_H
