/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testkillerclient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 21:29:55 by fhongu            #+#    #+#             */
/*   Updated: 2024/02/02 19:10:18 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <libft.h>
#include <stdio.h>

void	send_message(pid_t pid, char *message);
int		chars_to_int(char *str, int idx);
int		send(pid_t pid, int chunk, int ndigits);
void	sig_handler(int signo);
void	ping_server(pid_t pid);

int	g_go_ahead = 0;

int	main(int argc, char **argv)
{
	if (signal(SIGUSR2, sig_handler) == SIG_ERR)
		printf("error");
	if (argc == 3)
	{
		send_message(ft_atoi(argv[1]), argv[2]);
	}
	return (0);
}

void	send_message(pid_t pid, char *message)
{
	int		chunk;
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(message);
	while (i < len)
	{
		chunk = chars_to_int(message, i);
		i += 4;
		send(pid, chunk, 0);
	}
	send(pid, 10, 0);
	send(pid, 3, 0);
}

int	chars_to_int(char *str, int idx)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[idx + i] && i < 4)
	{
		res += ((int) str[idx + i]) << (8 * (3 - i));
		i++;
	}
	return (res);
}

int	send(pid_t pid, int chunk, int ndigits)
{
	int	res;

	res = 0;
	if (chunk > 0)
		res = send(pid, chunk / 2, ndigits + 1);
	res *= 2;
	if (chunk % 2)
	{
		res++;
		kill(pid, SIGUSR2);
	}
	else
		kill(pid, SIGUSR1);
	pause();
	while (chunk == 0 && ndigits % 8 != 7)
	{
		kill(pid, SIGUSR1);
		pause();
		ndigits++;
	}
	return (res);
}

void	sig_handler(int signo)
{
	g_go_ahead = signo == SIGUSR2;
}

void	ping_server(pid_t pid)
{
	while (!g_go_ahead)
	{
		kill(pid, SIGUSR1);
		pause();
		usleep(100);
	}
}
