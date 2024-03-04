/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:30:12 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/04 22:50:00 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/client.h"
#include <stdio.h>

void	send_bit(int bit, int pid)
{
	int	signal;

	printf("%d", bit);
	if (!bit)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	kill(pid, signal);
	usleep(100);
	printf("unpaused!\n");
}

void	send_byte(int byte, int pid, int i)
{
	if (i == 0 && byte != 0)
		printf("\nsending byte %c\n", byte);
	else if (byte == 0 && i == 0)
		printf("\nsending null terminator. Should see 8 0s being sent!\n");
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
	printf("string sent, sending null terminator!\n");
	send_byte('\0', pid, 0);
}

void	ping(char *str, int pid)
{
	int	i;

	i = 0;
	while (i++ < 10 && !g_server_response)
	{
		printf("ping\n");
		kill(pid, SIGUSR2);
		usleep(100);
		if (g_server_response)
		{
			printf("got the go ahead!\n");
			break ;
		}
		printf("no response, pinging again!\n");
	}
	if (g_server_response)
		send_string(str, pid);
}
