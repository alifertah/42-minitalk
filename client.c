/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfertah <alfertah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 21:55:13 by alfertah          #+#    #+#             */
/*   Updated: 2022/03/23 19:36:23 by alfertah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	red(void)
{
	ft_putstr("\033[1;31m");
}

void	send_msg(char *msg, int pid)
{
	int	i;
	int	shift;

	i = -1;
	while (++i < ft_strlen(msg))
	{
		shift = -1;
		while (++shift < 8)
		{
			if (msg[i] & (128 >> shift))
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(1);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(1);
			}
			usleep(800);
		}
	}
}

int	main(int argc, char **argv)
{
	int		ppid;

	if (argc != 3)
	{	
		red();
		ft_putstr(">>>>failure<<<<");
		exit(1);
	}
	ppid = ft_atoi(argv[1]);
	if (ppid == -1)
		exit(1);
	send_msg(argv[2], ppid);
}
