/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:30:12 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/22 20:59:06 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/client.h"

int	g_server_response = 0;

void	send_bit(int bit, int pid)
{
	int	signal;

	if (!bit)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	usleep(100);
	kill(pid, signal);
}

void	send_byte(int byte, int pid, int i)
{
	byte = byte % 256;
	if (i < 7)
		send_byte(byte / 2, pid, i + 1);
	send_bit(byte % 2, pid);
	pause();
}

void	send_string(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		send_byte(str[i], pid, 0);
		i++;
	}
	send_byte('\0', pid, 0);
}

void	ping(int pid)
{
	int	i;

	i = 0;
	while (i++ < 10 && !g_server_response)
	{
		kill(pid, SIGUSR2);
		usleep(50);
		if (g_server_response)
			break ;
	}
}
