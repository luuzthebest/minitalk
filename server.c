/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvvz <lvvz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:22:58 by lvvz              #+#    #+#             */
/*   Updated: 2025/04/08 22:01:44 by lvvz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
void ft_putchar(char c)
{
    write(1, &c, 1);
}
void	ft_putnbr(int n)
{
	long int	nb;

	nb = n;
	if (nb < 10)
		ft_putchar(nb + '0');
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}
void handler(int sig, siginfo_t *info, void *ucontext)
{
	static int	i;
	static char	c;
	static int	c_pid;

	(void)ucontext;
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
int main()
{
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(write(1, "Singal Error!!", 14));
    write(1, "PID: ", 5);
    ft_putnbr(getpid());
    write(1, "\nwaiting for signals..\n", 23);
    while (1337)
    {
		pause();
    }
    return 0;
}