/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:30:16 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/09 22:41:46 by fhongu           ###   ########.fr       */
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

void	string_parser(void)
{
	static int			nbits;
	static int			byte;
	static int			i;

	if (nbits <= 7)
	{
		byte *= 2;
		if (g_info->si_signo == SIGUSR2)
			byte++;
		nbits++;
	}
	if (nbits == 8)
	{
		//printf("parsed byte %c\n", byte);
		make_string(byte, i);
		if (byte != '\0')
			i++;
		else
			i = 0;
		nbits = 0;
		byte = 0;
	}
	if (byte == '\0' && i == 0 && nbits == 0)
		g_info = NULL;
}

static void	make_string(int ch, int i)
{
	static char	*str;
	static int	curr_size;

	if (!str)
	{
		//printf("making initial string of size %d\n", MESSAGE_INI_SIZE);
		str = ft_calloc(MESSAGE_INI_SIZE, sizeof (char));
		curr_size = MESSAGE_INI_SIZE;
	}
	add_char(&str, ch, i, &curr_size);
	//printf("current string looks like \"%s\"\n", str);
	if (ch == '\0')
		print_string(str, i + 1);
}

static void	add_char(char **str, int ch, int i, int *curr_size)
{
	char	*new_str;

	//printf("adding char \'%c\' to string \"%s\"\n", ch, *str);
	(*str)[i] = ch;
	if (i >= *curr_size * MESSAGE_MAX_LOAD)
	{
		//printf("resizing string!\n");
		*curr_size *= MESSAGE_RESIZE_FACTOR;
		new_str = ft_calloc(*curr_size, sizeof (char));
		ft_strlcpy(new_str, *str, *curr_size);
		ft_free((void **) str);
		*str = new_str;
	}
}

static void	print_string(char *str, int i)
{
	//printf("string fully parsed, printing:\n");
	str[i] = '\n';
	write(1, str, i + 1);
}

void	pong(int signo, siginfo_t *info, void *uctx)
{
	int	spid;

	spid = getpid();
	//printf("signal %d received from %d\n", signo == SIGUSR2, info->si_pid);
	//printf("global's pid is %d\n", (g_info != NULL) ? g_info->si_pid : 0);
	if (g_info == NULL && info->si_pid != spid && info->si_pid != 0)
	{
		printf("pong\n");
		kill(info->si_pid, SIGUSR2);
	}
	if (info->si_pid != spid && info->si_pid != 0)
		g_info = info;
	uctx = NULL;
	signo = SIGUSR2;
}
