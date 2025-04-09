/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hounajar <hounajar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:22:58 by lvvz              #+#    #+#             */
/*   Updated: 2025/04/09 12:38:22 by hounajar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static int	i;
	static char	c;
	static int	c_pid;

	(void)ucontext;
	if (info->si_pid != c_pid)
	{
		i = 0;
		c = 0;
	}
	if (info->si_pid)
		c_pid = info->si_pid;
	(void)c_pid;
	if (sig == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(write(1, "Singal Error!!", 14));
	write(1, "PID: ", 5);
	ft_putnbr(getpid());
	write(1, "\nwaiting for signals..\n", 23);
	while (1337)
	{
		pause();
	}
	return (0);
}
