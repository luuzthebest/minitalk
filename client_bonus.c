/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvvz <lvvz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:25:38 by lvvz              #+#    #+#             */
/*   Updated: 2025/04/08 20:56:30 by lvvz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

long int	ft_atoi(const char *nptr)
{
	long int	result;
	int			sign;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	if (*nptr < '0' || *nptr > '9') 
		return (-1);
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr != '\0')
		return (-1); 
	return (result * sign);
}
void	sign_it(int pid, int s)
{
	if (kill(pid, s) == -1)
	{
		write(1, "Singal Sending Failed !\n", 24);
		exit(1);
	}
}
void sender(unsigned char c , int pid)
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
void s_handler(int sig)
{
	if (sig == SIGUSR2)
		write(1, "client has recieved the message\n", 33);
	
}
int main(int ac, char *av[])
{
	int		pid;
	int 	i;

	i = 0;
	if (ac != 3)
	{
		write(1, "Invalid ARGS\n", 13);
		exit(1);
	}
	pid = ft_atoi(av[1]);
	signal(SIGUSR2, s_handler);
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
	return 0;
	
	
}