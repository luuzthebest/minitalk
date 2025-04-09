/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounajar <hounajar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:25:38 by lvvz              #+#    #+#             */
/*   Updated: 2025/04/09 12:40:53 by hounajar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sign_it(int pid, int s)
{
	if (kill(pid, s) == -1)
	{
		write(1, "Singal Sending Failed !\n", 24);
		exit(1);
	}
}

void	sender(unsigned char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & 1)
			sign_it(pid, SIGUSR1);
		else
			sign_it(pid, SIGUSR2);
		c >>= 1;
		usleep(100);
		bit++;
	}
}

int	main(int ac, char *av[])
{
	int	pid;
	int	i;

	i = 0;
	arg_check(ac);
	pid = ft_atoi(av[1]);
	if (pid > 0)
	{
		while (av[2][i])
		{
			sender(av[2][i], pid);
			i++;
		}
		sender('\n', pid);
		sender('\0', pid);
	}
	else
	{
		write(1, "Invalid PID\n", 12);
		exit(1);
	}
	return (0);
}
