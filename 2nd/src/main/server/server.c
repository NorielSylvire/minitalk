/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:30:16 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/04 22:51:53 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/server.h"
#include <signal.h>
#include <stdio.h>

static void	make_string(int ch, int i);
static void	add_char(char **str, int ch, int i, int *curr_size);
static void	print_string(char *str, int i);

//TODO remove everything you can from the signal handler.
//Instead the global should be a pointer to siginfo, and the string parser
//and pong should be called withing an infinite loop that reads the info
//then checks if the sender is the same as the previous sender, and if so
//parses the bit, otherwise it doesn't do anything.

void	string_parser(int signo, siginfo_t *info, void *uctx)
{
	static int			nbits;
	static int			byte;
	static int			i;
	struct sigaction	new_action;

	printf("bit %d received from %d\n", signo == SIGUSR2, g_client_pid);
	if (nbits <= 7 && info->si_pid == g_client_pid)
	{
		byte *= 2;
		if (signo == SIGUSR2)
			byte++;
		nbits++;
		printf("byte now %d\n", byte);
	}
	if (nbits == 8 && info->si_pid == g_client_pid)
	{
		printf("byte %c parsed\n", byte);
		make_string(byte, i);
		if (byte != '\0')
			i++;
		else
			i = 0;
		nbits = 0;
		byte = 0;
	}
	printf("all the above done, killing %d\n", g_client_pid);
	kill(g_client_pid, SIGUSR2);
	uctx = NULL;
	if (byte == '\0' && i == 0 && nbits == 0)
	{
		printf("global restarted\n");
		g_client_pid = 0;
		new_action.sa_flags = SA_SIGINFO;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_sigaction = pong;
		sigaction(SIGUSR1, &new_action, NULL);
		sigaction(SIGUSR2, &new_action, NULL);
	}
}

static void	make_string(int ch, int i)
{
	static char	*str;
	static int	curr_size;

	if (!str)
	{
		printf("making initial string of size %d\n", MESSAGE_INI_SIZE);
		str = ft_calloc(MESSAGE_INI_SIZE, sizeof (char));
		curr_size = MESSAGE_INI_SIZE;
	}
	add_char(&str, ch, i, &curr_size);
	printf("current string looks like \"%s\"\n", str);
	if (ch == '\0')
		print_string(str, i);
}

static void	add_char(char **str, int ch, int i, int *curr_size)
{
	char	*new_str;

	printf("adding char \'%c\' to string \"%s\"\n", ch, *str);
	(*str)[i] = ch;
	if (i >= *curr_size * MESSAGE_MAX_LOAD)
	{
		printf("resizing string!\n");
		*curr_size *= MESSAGE_RESIZE_FACTOR;
		new_str = ft_calloc(*curr_size, sizeof (char));
		ft_strlcpy(new_str, *str, *curr_size);
		ft_free((void **) str);
		*str = new_str;
	}
}

static void	print_string(char *str, int i)
{
	printf("string fully parsed, printing:\n");
	str[i] = '\n';
	write(1, str, i);
}

void	pong(int signo, siginfo_t *info, void *uctx)
{
	struct sigaction	new_action;

	printf("signal %d received from %d\n", signo == SIGUSR2, info->si_pid);
	printf("current client pid is %d\n", g_client_pid);
	if (g_client_pid == 0 && info->si_pid != getpid())
	{
		printf("pong\n");
		g_client_pid = info->si_pid;
		kill(g_client_pid, SIGUSR2);
		new_action.sa_flags = SA_SIGINFO;
		sigemptyset(&new_action.sa_mask);
		new_action.sa_sigaction = string_parser;
		sigaction(SIGUSR1, &new_action, NULL);
		sigaction(SIGUSR2, &new_action, NULL);
	}
	uctx = NULL;
}
