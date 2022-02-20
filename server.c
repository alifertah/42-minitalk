/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfertah <alfertah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 21:55:00 by alfertah          #+#    #+#             */
/*   Updated: 2022/02/19 22:36:46 by alfertah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

int	g_pid = 0;

void	reset(int *a, char *b, int ppid)
{
	*a = 0;
	*b = 0xff;
	g_pid = ppid;
}

void	handler(int sig, siginfo_t *info, void *empty)
{
	static int		shiffre;
	static char		c = 0xff;

	(void)empty;
	if (g_pid != info->si_pid)
		reset(&shiffre, &c, info->si_pid);
	if (sig == SIGUSR1)
		c = c | 128 >> shiffre;
	else if (sig == SIGUSR2)
		c = c ^ 128 >> shiffre;
	shiffre++;
	if (shiffre == 8)
	{
		write(1, &c, 1);
		c = 0xff;
		shiffre = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
