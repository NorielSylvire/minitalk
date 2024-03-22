/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:30:16 by fhongu            #+#    #+#             */
/*   Updated: 2024/03/22 20:58:55 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/server.h"

static void	make_string(int ch, int i);
static void	add_char(char **str, int ch, int i, int *curr_size);

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
		str = ft_calloc(MESSAGE_INI_SIZE, sizeof (char));
		curr_size = MESSAGE_INI_SIZE;
	}
	add_char(&str, ch, i, &curr_size);
	if (ch == '\0')
	{
		write(1, str, i + 1);
		ft_free((void **) &str);
	}
}

static void	add_char(char **str, int ch, int i, int *curr_size)
{
	char	*new_str;

	if (ch != '\0')
		(*str)[i] = ch;
	else
		(*str)[i] = '\n';
	if (i >= *curr_size * MESSAGE_MAX_LOAD)
	{
		*curr_size *= MESSAGE_RESIZE_FACTOR;
		new_str = ft_calloc(*curr_size, sizeof (char));
		ft_strlcpy(new_str, *str, *curr_size);
		ft_free((void **) str);
		*str = new_str;
	}
}

void	pong(int signo, siginfo_t *info, void *uctx)
{
	int	spid;

	spid = getpid();
	if (g_info == NULL && info->si_pid != spid && info->si_pid != 0)
		kill(info->si_pid, SIGUSR2);
	if (info->si_pid != spid && info->si_pid != 0)
		g_info = info;
	uctx = NULL;
	signo = SIGUSR2;
}
