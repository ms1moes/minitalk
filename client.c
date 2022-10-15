/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:08:07 by msimoes-          #+#    #+#             */
/*   Updated: 2022/05/25 20:06:14 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	end_prog(pid_t s_pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		usleep(50);
		kill(s_pid, SIGUSR2);
	}
	write(1, "\nfinished successfully\n", 22);
	exit(0);
}

void	send_bit(pid_t pid, char *s)
{
	static int				i = 8;
	static char				c;
	static char				*str;
	static pid_t			s_pid;

	if (s)
	{
		str = s;
		s_pid = pid;
		c = *str;
	}
	if (!i)
	{
		i = 8;
		c = *(++str);
		if (!c)
			end_prog(s_pid);
	}
	if (c && c >> --i & 1)
		kill(s_pid, SIGUSR1);
	else if (c)
		kill(s_pid, SIGUSR2);
}

void	c_handler(int sig, siginfo_t *siginfo, void *unused)
{
	static int	bytes = 0;

	(void)siginfo;
	(void)unused;
	if (sig == SIGUSR1)
	{
		write(1, "\rnumber of bytes:  ", 19);
		ft_putunbr(++bytes);
	}
	send_bit(0, NULL);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	sigset_t 			mask;

	if (ft_verify_input(ac, av))
	{
		write(1, "Error: invalid input\n", 21);
		return (1);
	}
	sigemptyset(&mask);
	sa.sa_mask = mask;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = c_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (!ft_strlen(av[2]))
		exit(0);
	send_bit(ft_atoi(av[1]), av[2]);
	while (1)
		pause();
}
