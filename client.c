/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfertah <alfertah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 21:55:13 by alfertah          #+#    #+#             */
/*   Updated: 2022/02/19 23:17:56 by alfertah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
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
		ft_putstr("ta chkaddir!");
		exit(1);
	}
	ppid = ft_atoi(argv[1]);
	if (ppid == -1)
		exit(1);
	send_msg(argv[2], ppid);
}
