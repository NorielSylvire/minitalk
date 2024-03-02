/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:30:16 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/02 11:07:06 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/server.h"
#include <stdio.h>

static void	make_string(int ch, int i);
static void	add_char(char **str, int ch, int i, int *curr_size);
static void	print_string(char *str, int i);

//TODO receive ping and respond to it. Respond bit by bit!

void	string_parser(int signo, siginfo_t *info, void *uctx)
{
	static int	nbits;
	static int	byte;
	static int	i;

	printf("bit received: %d\n", signo == SIGUSR2);
	if (nbits <= 7)
	{
		byte *= 2;
		if (signo == SIGUSR2)
			byte++;
		nbits++;
	}
	if (nbits == 8)
	{
		printf("byte detected: %d\n", byte);
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
	static int	curr_size;

	if (!str)
	{
		str = ft_calloc(MESSAGE_INI_SIZE, sizeof (char));
		curr_size = MESSAGE_INI_SIZE;
	}
	add_char(&str, ch, i, &curr_size);
	if (ch == '\0')
		print_string(str, i);
}

static void	add_char(char **str, int ch, int i, int *curr_size)
{
	char	*new_str;

	*str[i] = ch;
	if (i >= *curr_size * MESSAGE_MAX_LOAD)
	{
		*curr_size *= MESSAGE_RESIZE_FACTOR;
		new_str = ft_calloc(*curr_size, sizeof (char));
		ft_strlcpy(new_str, *str, *curr_size);
		ft_free((void **) str);
		*str = new_str;
	}
}

static void	print_string(char *str, int i)
{
	str[i] = '\n';
	write(1, str, i);
}
