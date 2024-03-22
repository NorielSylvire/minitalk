/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 09:56:26 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/10 08:25:06 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/client.h"

void	sig_handler(int sig)
{
	g_server_response = sig == SIGUSR2;
}

int	main(int argc, char **argv)
{
	int	spid;

	signal(SIGUSR2, sig_handler);
	signal(SIGUSR1, sig_handler);
	if (argc == 3)
	{
		spid = ft_atoi(argv[1]);
		ping(spid);
	}
	else
		write(1, "Wrong arguments. Usage: client [pid] [message string]", 53);
	if (g_server_response)
		send_string(argv[2], spid);
}
