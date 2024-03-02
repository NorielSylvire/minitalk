/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:25:50 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/02 09:48:10 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_test.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

unsigned long	g_received = 0;

static void	signal_repeater(int signo, siginfo_t *info, void *uctx);
static void	signal_parser(int signo, siginfo_t *info, void *uctx);
static void	string_parser(int signo, siginfo_t *info, void *uctx);
static void	make_string(int ch, int i);

void	test_client(void)
{
	char	*test_result;

	printf(MAGENTA"\n\n\nTests for client functions\n"DEF_COLOR);
	test_result = make_test_result_string(test_send_bit_0());
	printf(TESTH, "send_bit 1 Bit 0 ", test_result);
	test_result = make_test_result_string(test_send_bit_1());
	printf(TESTH, "send_bit 2 Bit 1 ", test_result);
	test_result = make_test_result_string(test_send_byte_zero());
	printf(TESTH, "send_byte 1 Byte 0 ", test_result);
	test_result = make_test_result_string(test_send_byte_max());
	printf(TESTH, "send_byte 2 Byte 255 ", test_result);
	test_result = make_test_result_string(test_send_byte_nbr());
	printf(TESTH, "send_byte 3 Byte 42 ", test_result);
	test_result = make_test_result_string(test_send_byte_char_t());
	printf(TESTH, "send_byte 4 Byte char 'T' ", test_result);
	test_result = make_test_result_string(test_send_string_cool());
	printf(TESTH, "send_string 1 String \"cool\" ", test_result);
	test_result = make_test_result_string(test_send_string_lorem_ipsum());
	printf(TESTH, "send_string 1 String \"Lorem ipsum d0lor sit amet.\" ", test_result);
}

int	test_send_bit_0(void)
{
	struct sigaction	new_action;

	new_action.sa_flags = SA_SIGINFO;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_sigaction = signal_repeater;
	sigaction(SIGUSR1, &new_action, NULL);
	send_bit(0, getpid());
	return (g_received == 0);
}

int	test_send_bit_1(void)
{
	struct sigaction	new_action;

	new_action.sa_flags = SA_SIGINFO;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_sigaction = signal_repeater;
	sigaction(SIGUSR2, &new_action, NULL);
	send_bit(1, getpid());
	return (g_received == 1);
}

int	test_send_byte_zero(void)
{
	struct sigaction	new_action;

	new_action.sa_flags = SA_SIGINFO;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_sigaction = signal_parser;
	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);
	send_byte(0, getpid(), 0);
	return (g_received == 0);
}

int	test_send_byte_max(void)
{
	struct sigaction	new_action;

	new_action.sa_flags = SA_SIGINFO;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_sigaction = signal_parser;
	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);
	send_byte(255, getpid(), 0);
	return (g_received == 255);
}

int	test_send_byte_nbr(void)
{
	struct sigaction	new_action;

	new_action.sa_flags = SA_SIGINFO;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_sigaction = signal_parser;
	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);
	send_byte(42, getpid(), 0);
	return (g_received == 42);
}

int	test_send_byte_char_t(void)
{
	struct sigaction	new_action;

	new_action.sa_flags = SA_SIGINFO;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_sigaction = signal_parser;
	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);
	send_byte('T', getpid(), 0);
	return (g_received == 'T');
}

int	test_send_string_cool(void)
{
	struct sigaction	new_action;
	int					result;

	new_action.sa_flags = SA_SIGINFO;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_sigaction = string_parser;
	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);
	send_string("cool", getpid());
	result = ft_strncmp((char *) g_received, "cool", 4);
	ft_free((void **) &g_received);
	return (result == 0);
}

int	test_send_string_lorem_ipsum(void)
{
	struct sigaction	new_action;

	new_action.sa_flags = SA_SIGINFO;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_sigaction = string_parser;
	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);
	send_string("Lorem ipsum d0lor sit amet.", getpid());
	return (ft_strncmp((char *) g_received, "Lorem ipsum d0lor sit amet.", 30) == 0);
}

static void	signal_repeater(int signo, siginfo_t *info, void *uctx)
{
	if (signo == SIGUSR2)
		g_received = 1;
	else
		g_received = 0;
	info->si_pid = getpid();
	uctx = NULL;
}

static void	signal_parser(int signo, siginfo_t *info, void *uctx)
{
	static int	nbits;
	static int	byte;

	if (nbits <= 7)
	{
		byte *= 2;
		if (signo == SIGUSR2)
			byte++;
		nbits++;
	}
	if (nbits == 8)
	{
		g_received = byte;
		nbits = 0;
		byte = 0;
	}
	info->si_pid = getpid();
	uctx = NULL;
}

static void	string_parser(int signo, siginfo_t *info, void *uctx)
{
	static int	nbits;
	static int	byte;
	static int	i;

	if (nbits <= 7)
	{
		byte *= 2;
		if (signo == SIGUSR2)
			byte++;
		nbits++;
	}
	if (nbits == 8)
	{
		make_string(byte, i);
		if (byte != '\0')
			i++;
		else
			i = 0;
		nbits = 0;
		byte = 0;
	}
	info->si_pid = getpid();
	uctx = NULL;
}

static void	make_string(int ch, int i)
{
	static char	*str;

	if (!str)
		str = ft_calloc(30, sizeof (char));
	str[i] = ch;
	g_received = (unsigned long) str;
}
