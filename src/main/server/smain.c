/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:28:39 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/22 20:59:01 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/server.h"

siginfo_t	*g_info = NULL;

static void	listen_to_clients(void);

int	main(void)
{
	int					mypid;
	char				*mypid_str;
	struct sigaction	new_action;

	write(1, "pid: ", 5);
	mypid = getpid();
	mypid_str = ft_itoa(mypid);
	write(1, mypid_str, ft_strlen(mypid_str));
	write(1, "\n", 1);
	new_action.sa_flags = SA_SIGINFO;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_sigaction = pong;
	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);
	listen_to_clients();
	free(mypid_str);
	return (0);
}

static void	listen_to_clients(void)
{
	int					is_pong;
	int					cpid;

	is_pong = 1;
	while (1)
	{
		is_pong = g_info == NULL;
		pause();
		if (!is_pong && g_info->si_pid == cpid)
		{
			string_parser();
			usleep(50);
			kill(cpid, SIGUSR2);
		}
		else if (is_pong)
			cpid = g_info->si_pid;
	}
}
