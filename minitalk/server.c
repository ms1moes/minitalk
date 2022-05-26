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

void	signal_handler(int signal, siginfo_t *info, void *null)
{
	static int		j = 1;
	static int		ascii = 0;
	static int		i = 0;
	static pid_t	client_pid = 0;

	(void)null;
	if (!client_pid)
		client_pid = info->si_pid;
	if (signal == SIGUSR2)
		ascii += j;
		j *= 2;
		i++;
	if (i == 8)
	{
		write(1, &ascii, 1);
		if (ascii == '\0')
		{
			kill(client_pid, SIGUSR1);
			client_pid = 0;
		}
		j = 1;
		ascii = 0;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr("PID: ");
	ft_putunbr(getpid());
	ft_putstr("\n");
	s_sigaction.sa_sigaction = signal_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
}
