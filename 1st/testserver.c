/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testserver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:56:47 by fhongu            #+#    #+#             */
/*   Updated: 2024/01/20 14:05:37 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <libft.h>
#include <stdio.h>
#define MESSAGE_MAX_LOAD 0.75f
#define MESSAGE_RESIZE_FACTOR 2

pid_t	g_curr_client_pid = 0;

void	siga_handler(int signo, siginfo_t *info, void *uap);
void	parse_byte(int byte);
void	resize_message(char **message, int *buffer_size, int used_bytes);

int	main(void)
{
	struct sigaction	new_action;
	struct sigaction	old_action;

	printf("pid: %d\n", getpid());
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = SA_SIGINFO;
	new_action.sa_sigaction = siga_handler;
	sigaction(SIGUSR1, NULL, &old_action);
	if (old_action.sa_handler != SIG_IGN)
		sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, NULL, &old_action);
	if (old_action.sa_handler != SIG_IGN)
		sigaction(SIGUSR2, &new_action, NULL);
	while (1)
		continue ;
	return (0);
}

void	siga_handler(int signo, siginfo_t *info, void *uap)
{
	static int	byte;
	static int	numbits;

	//printf("client pid: %d\n", g_curr_client_pid);
	if (!g_curr_client_pid)
		g_curr_client_pid = info->si_pid;
	//printf("client pid: %d\n", g_curr_client_pid);
	if (g_curr_client_pid == info->si_pid && g_curr_client_pid != 0)
	{
		if (numbits <= 7)
		{
			byte *= 2;
			if (signo == SIGUSR2)
				byte++;
			numbits++;
			//printf("received bit: %d\n", signo == SIGUSR2);
		}
		if (numbits == 8)
		{
			numbits = 0;
			parse_byte(byte);
			byte = 0;
		}
		kill(g_curr_client_pid, SIGUSR2);
	}
	else if (g_curr_client_pid != 0)
	{
		kill(info->si_pid, SIGUSR1);
	}
}

void	parse_byte(int byte)
{
	static char	*message;
	static int	buffer_size;
	static int	used_bytes;

	//printf("byte: %d\n", byte);
	if (!message || *message == '\0')
	{
		buffer_size = 40;
		message = malloc(buffer_size * sizeof (char));
		if (!message)
			exit(1);
	}
	if (byte == 3)
	{
		message[used_bytes++] = '\0';
		write(1, message, used_bytes);
		printf("Message sent!\n");
		kill(g_curr_client_pid, SIGUSR2);
		used_bytes = 0;
		g_curr_client_pid = 0;
		ft_free((void **) &message);
	}
	else
		message[used_bytes++] = byte;
	if (used_bytes / buffer_size >= MESSAGE_MAX_LOAD)
		resize_message(&message, &buffer_size, used_bytes);
}

void	resize_message(char **message, int *buffer_size, int used_bytes)
{
	char	*new_ptr;
	char	*old_msg;

	new_ptr = malloc(*buffer_size * MESSAGE_RESIZE_FACTOR);
	if (!new_ptr)
	{
		ft_free((void **) message);
		exit(0);
	}
	old_msg = *message;
	*message = ft_memcpy((void *) new_ptr, *message, used_bytes);
	ft_free((void **) &old_msg);
	*buffer_size = *buffer_size * MESSAGE_RESIZE_FACTOR;
}
