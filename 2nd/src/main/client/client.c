/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:30:12 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/02 11:06:09 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/client.h"

//TODO ping method, wait for server response between bits!

void	send_bit(int bit, int pid)
{
	int	signal;

	if (!bit)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	kill(pid, signal);
}

void	send_byte(int byte, int pid, int i)
{
	byte = byte % 256;
	if (i < 7)
		send_byte(byte / 2, pid, i + 1);
	send_bit(byte % 2, pid);
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
