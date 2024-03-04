/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:18:03 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/04 20:22:18 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include "minitalk.h"

void	send_bit(int bit, int pid);
void	send_byte(int byte, int pid, int i);
void	send_string(char *str, int pid);
void	ping(char *str, int pid);

extern int	g_server_response;

#endif // !CLIENT_H
