/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:36:51 by msimoes-          #+#    #+#             */
/*   Updated: 2022/05/26 15:27:57 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	s_handler(int sig, siginfo_t *siginfo, void *unused)
{
	static unsigned char	c = 0;
	static int				i = 0;
	static pid_t			c_pid = 0;

	(void)unused;
	if (!c_pid)
		c_pid = siginfo->si_pid;
	c |= (sig == SIGUSR1);
	if (++i == 8)
	{
		i = 0;
		if (c == 0)
		{
			c_pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
		kill(c_pid, SIGUSR1);
	}
	else
	{
		c <<= 1;
		kill(c_pid, SIGUSR2);
	}
}

//Ao usar a flag SA_SIGINFO a função que recebe os sinais passa a ter 3 parametros em vez de 1. e em vez de usar sa_handler é necessario usar sa_sigaction
int main(void)
{
	struct sigaction	sa;

	write(1, "Server PID: ", 12);
	ft_putunbr(getpid());
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = s_handler;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
}